#include "SceneFireball.h"
#include "LightFlashlight.h"
#include "ModelFireball.h"
#include "TransformationAnimationBezierCurve.h"

// GLFW
#include <GLFW/glfw3.h>

// --- public ------------------------------------------------------------------
SceneFireball::SceneFireball(const std::string& t_name, Camera* t_camera)
	: Scene(t_name, t_camera) { }

SceneFireball::SceneFireball(Camera* t_camera)
	: Scene(t_camera) { }

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
	glm::vec3 directionXZ = glm::normalize(glm::vec3(direction.x, 0.f, direction.z)); // direction projected to XZ plane

	float cos =             glm::dot  (direction, directionXZ);  // dot product; cos(angle)
	float sin = glm::length(glm::cross(direction, directionXZ)); // length of the cross product; sin(angle)

	float power = fireball->getPower(); // power of the throw
	float coef = 30.f * sqrt(2.f); // coefficient of the throw; sqrt(2) is the length of the diagonal of the unit square

	// range and height of the throw
	float range  = cos * power * coef; // range in the direction of the XZ plane projection
	float height = sin * power * coef; // height above the XZ plane

	// bezier curve points
	glm::vec3 start = fireball->getTransformation()->getTranslateStep()->getTranslation(); // start point at the current position of the fireball
	glm::vec3 end = start + range * directionXZ; // end point in the direction of the XZ plane projection
	end.y = .1f; // end point slightly above ground; XZ plane

	std::vector<glm::vec3> controlPoints = { (start + end) * .5f + glm::vec3(0.f, height, 0.f) }; // control point above the middle of the start and end points

	fireball->getTransformation()->updateTranslateStep(
		std::make_shared<TransformationAnimationBezierCurve>(start, end, controlPoints, power * 3.f)); // 3 times longer duration; power = seconds
}
