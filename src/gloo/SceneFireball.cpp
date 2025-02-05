#include "SceneFireball.h"
#include "AppMath.h"
#include "LightFlashlight.h"
#include "ModelFireball.h"
#include "TransformationAnimationBezierCurve.h"

// glfw
#include <GLFW/glfw3.h>

// --- public ------------------------------------------------------------------
SceneFireball::SceneFireball(const std::string& t_name, Camera* t_camera)
	: Scene(t_name, t_camera) {
	this->m_title = Config::WINDOW_TITLE
		+ Config::WINDOW_TITLE_HELP
		+ Config::WINDOW_TITLE_HELP_MOVE
		+ Config::WINDOW_TITLE_HELP_FLASHLIGHT
		+ Config::WINDOW_TITLE_HELP_FIREBALL;
}

SceneFireball::SceneFireball(Camera* t_camera)
	: SceneFireball("@!#?@!", t_camera) { }

void SceneFireball::callbackKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) {
	Scene::callbackKey(t_window, t_key, t_scancode, t_action, t_mods);

	//printf("[scene fireball] callback key : key %d, scancode %d, action %d, mods %d\n", t_key, t_scancode, t_action, t_mods);

	// 'F' key to toggle flashlight
	if (t_key == GLFW_KEY_F && t_action == GLFW_PRESS) {
		LightFlashlight* flashlight = static_cast<LightFlashlight*>(this->getLight("flashlight"));
		if (flashlight)
			flashlight->toggle();
	}

	// 'SPACE' key to throw fireball
	if (t_key == GLFW_KEY_1 && t_action == GLFW_PRESS)
		this->chargeFireball(ModelFireball::fireballTypeE::FIREBALL_FIERY);
	if (t_key == GLFW_KEY_2 && t_action == GLFW_PRESS)
		this->chargeFireball(ModelFireball::fireballTypeE::FIREBALL_ICY);
	if (t_key == GLFW_KEY_3 && t_action == GLFW_PRESS)
		this->chargeFireball(ModelFireball::fireballTypeE::FIREBALL_NECROMANTIC);
	if (t_key == GLFW_KEY_4 && t_action == GLFW_PRESS)
		this->chargeFireball(ModelFireball::fireballTypeE::FIREBALL_ELDRITCH);

	if (t_action == GLFW_RELEASE                                                                      // key released...
		&& (t_key == GLFW_KEY_1 || t_key == GLFW_KEY_2 || t_key == GLFW_KEY_3 || t_key == GLFW_KEY_4) // ...and key is 1, 2, 3, or 4...
		&& glfwGetKey(t_window, GLFW_KEY_1) +                                                         // ...and no other key is pressed
		   glfwGetKey(t_window, GLFW_KEY_2) +
		   glfwGetKey(t_window, GLFW_KEY_3) +
		   glfwGetKey(t_window, GLFW_KEY_4) == GLFW_RELEASE)
		this->throwFireball();

	if (t_key == GLFW_KEY_0 && t_action == GLFW_PRESS) {
		ModelFireball* fireball = static_cast<ModelFireball*>(this->getModel("fireball"));
		if (fireball)
			fireball->setState(ModelFireball::fireballStateE::STATE_OFF);
	}
}

// --- private -----------------------------------------------------------------
void SceneFireball::chargeFireball(ModelFireball::fireballTypeE t_type) {
	ModelFireball* fireball = static_cast<ModelFireball*>(this->getModel("fireball"));
	if (!fireball) return;

	fireball->getTransformation()->updateTranslateStep(
		std::make_shared<TransformationStepTranslate>(glm::vec3(0.f))); // reset (no animation); no need to set position; it will follow the camera while charging
	fireball->setState(ModelFireball::fireballStateE::STATE_CHARGING, t_type);

	this->m_camera->addObserver(fireball);
}

void SceneFireball::throwFireball() {
	ModelFireball* fireball = static_cast<ModelFireball*>(this->getModel("fireball"));
	if (!fireball
		|| (fireball->getState() != ModelFireball::fireballStateE::STATE_CHARGING &&
			fireball->getState() != ModelFireball::fireballStateE::STATE_CHARGED)) return;

	fireball->setState(ModelFireball::fireballStateE::STATE_THROWN);

	this->m_camera->removeObserver(fireball);

	// parameters of the throw
	glm::vec3 direction = this->m_camera->getDirection();
	if (direction.y < 0.f) // do not throw below the horizon
		direction.y = .001f;

	direction = glm::normalize(direction);
	glm::vec3 directionXZ = glm::normalize(glm::vec3(direction.x, 0.f, direction.z)); // direction projected to xz plane

	float cosTheta =             glm::dot  (direction, directionXZ);  // dot product; cos(angle)
	float sinTheta = glm::length(glm::cross(direction, directionXZ)); // length of the cross product; sin(angle)

	float power = fireball->getPower(); // power of the throw
	float coef = 30.f * sqrt(2.f); // coefficient of the throw; sqrt(2) is the length of the diagonal of the unit square

	// range and height of the throw
	float range  = cosTheta * power * coef; // range in the direction of the xz plane projection
	float height = sinTheta * power * coef; // height above the start point

	// bezier curve points; bezier of 2nd degree (quadratic)
	glm::vec3 bStart = fireball->getTransformation()->getTranslateStep()->getTranslation(); // start point at the current position of the fireball
	glm::vec3 bEnd = bStart + range * directionXZ; // end point in the direction of the xz plane projection
	glm::vec3 bControl = (bStart + bEnd) / 2.f + glm::vec3(0.f, height, 0.f); // control point above the middle of the start point and the end point in the direction of the xz plane projection

	bEnd.y = this->m_min.y + .03f; // end point slightly above ground

	// throw curve
	std::vector<std::vector<glm::vec3>> curve;

	switch (fireball->getType()) {
	default: // fiery and icy are simple/classic straight throws
		curve = std::vector<std::vector<glm::vec3>>{ { bStart, bControl, bEnd } }; break;

	case ModelFireball::fireballTypeE::FIREBALL_NECROMANTIC: // necromantic is a spiraling throw
		curve = this->specialCurve(std::vector<glm::vec3>{ bStart, bControl, bEnd }, power, curveTypeE::CURVE_SPIRAL); break;

	case ModelFireball::fireballTypeE::FIREBALL_ELDRITCH: // eldritch is a zigzagging throw
		curve = this->specialCurve(std::vector<glm::vec3>{ bStart, bControl, bEnd }, power, curveTypeE::CURVE_ZIGZAG); break;
	}

	fireball->getTransformation()->updateTranslateStep(
		std::make_shared<TransformationAnimationBezierCurve>(curve, power * 3.f)); // 3 times longer duration; power = seconds
}

std::vector<std::vector<glm::vec3>> SceneFireball::specialCurve(const std::vector<glm::vec3>& t_bezierCurve, float t_power, curveTypeE t_type) {
	std::vector<glm::vec3> curveSegment;
	std::vector<std::vector<glm::vec3>> curve;

	curveSegment.push_back(t_bezierCurve[0]); // the starting point remains the same as on the original bezier curve

	// sampling the original bezier curve
	// curve of (sharply connected) segments
	size_t numSegments = Config::ENVIRONMENT_FIREBALL_PATH_COMPLEXITY; // separate segments; each segment is a smooth curve, but sharply connected to each other
	size_t bezierCurveDegree = 2;

	float spiralRadius    = t_power / 2.f; // 2 times smaller; power = radius; apply to spiral curve only
	float zigzagDiffRange = t_power / 3.f; // 3 times smaller; power = range; apply to zigzag curve only

	/*// one smooth curve
	size_t numSegments = 1; // smoth curve has only one segment
	size_t bezierCurveDegree = Config::ENVIRONMENT_FIREBALL_PATH_COMPLEXITY;

	float spiralRadius    = t_power * 2.f; // 2 times bigger; power = radius; apply to spiral curve only
	float zigzagDiffRange = t_power * 3.f; // 3 times bigger; power = range; apply to zigzag curve only*/

	size_t numSamples = numSegments * bezierCurveDegree; // degree + 1 points per segment; but! start and end points shared between neighbors
	float angleStep = 2.f * glm::pi<float>() * t_power * 3.f / numSamples; // rotation angle step per sample; power = number of turns of the spiral; apply to the spiral curve only

	for (size_t i = 1; i < numSamples; ++i) { // omit the first point (it is already added) and the last point (will be added later)
		float t = static_cast<float>(i) / numSamples;
		glm::vec3 point = AppMath::getInstance()->bezierPoint(t_bezierCurve, t); // point on the original bezier curve

		switch (t_type) {
		case curveTypeE::CURVE_SPIRAL: { // { } because of T definition inside the case block
			glm::vec3 T = glm::normalize(AppMath::getInstance()->bezierTangent(t_bezierCurve, t)); // tangent at the point on the original bezier curve

			point = this->spiralPoint(point, T, spiralRadius, i * angleStep);
			break; }

		case curveTypeE::CURVE_ZIGZAG:
			point = this->zigzagPoint(point, zigzagDiffRange);
			break;
		}

		curveSegment.push_back(point);
		if (curveSegment.size() == bezierCurveDegree + 1) { // segment is complete
			curve.push_back(curveSegment); // add the segment to the curve

			curveSegment.clear();          // start a new segment
			curveSegment.push_back(point); // start point of the next segment
		}
	}

	curveSegment.push_back(t_bezierCurve.back()); // the ending point remains the same as on the original bezier curve
	curve.push_back(curveSegment); // add the last segment to the curve

	return curve;
}

glm::vec3 SceneFireball::zigzagPoint(const glm::vec3& t_point, float t_diffRange) {
	return t_point + glm::vec3(
		AppMath::getInstance()->randomNumber(-t_diffRange, t_diffRange),
		AppMath::getInstance()->randomNumber(-t_diffRange, t_diffRange),
		AppMath::getInstance()->randomNumber(-t_diffRange, t_diffRange));
}

glm::vec3 SceneFireball::spiralPoint(const glm::vec3& t_point, const glm::vec3& t_tangent, float t_radius, float t_angle) {
	glm::vec3 up(1.f, 0.f, 0.f); // up vector; in the direction of x-axis should never be parallel to the tangent; we always look up < 90 degrees
	if (glm::abs(glm::dot(t_tangent, up)) > .99f) // perpendicularity test to avoid the tangent ~ up situation
		up = glm::vec3(0.f, 1.f, 0.f);            // tangent is almost parallel to up; use another vector

	glm::vec3 B = glm::normalize(glm::cross(t_tangent, up)); // B = T x up; axis perpendicular to both T and up
	glm::vec3 N = glm::normalize(glm::cross(B, t_tangent));  // N = B x T; axis perpendicular to both B and T

	glm::vec3 offset = t_radius * (glm::cos(t_angle) * B + glm::sin(t_angle) * N); // rotation around the T axis; in the plane of B-N

	return t_point + offset;
}
