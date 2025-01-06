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

void SceneFireball::callbackKey(int t_key, int t_scancode, int t_action, int t_mods) {
	Scene::callbackKey(t_key, t_scancode, t_action, t_mods);

	// 'F' key to toggle flashlight
	if (t_key == GLFW_KEY_F && t_action == GLFW_PRESS) {
		LightFlashlight* flashlight = static_cast<LightFlashlight*>(this->getLight("flashlight"));
		if (flashlight)
			flashlight->toggle();
	}

	// 'SPACE' key to toggle fireball
	if (t_key == GLFW_KEY_SPACE && t_action == GLFW_PRESS) {
		ModelFireball* fireball = static_cast<ModelFireball*>(this->getModel("fireball"));
		if (fireball) {
			glm::vec3 position = *this->m_camera->getEye() + *this->m_camera->getDirection() * 5.f;
			fireball->getTransformation()->updateTranslateStep(
				std::make_shared<TransformationStepTranslate>(position));

			this->m_camera->addObserver(fireball);

			fireball->setState(ModelFireball::stateT::STATE_CHARGING);
		}
	}

	if (t_key == GLFW_KEY_SPACE && t_action == GLFW_RELEASE)
		this->throwFireball();
}

// --- private -----------------------------------------------------------------
void SceneFireball::prepareFireball() {
	Model* fireball = this->getModels().at("fireball");
	if (!fireball) return;
}

void SceneFireball::throwFireball() {
	ModelFireball* fireball = static_cast<ModelFireball*>(this->getModel("fireball"));
	if (!fireball) return;

	this->m_camera->removeObserver(fireball);

	glm::vec3 eye = *this->m_camera->getEye();
	glm::vec3 direction = *this->m_camera->getDirection();
	glm::vec3 up = *this->m_camera->getUp();

	// parameters of the throw
	glm::vec3 directionXZ = glm::normalize(glm::vec3(direction.x, 0.f, direction.z)); // direction projected to XZ plane
	float angle = glm::acos(glm::dot(glm::normalize(direction), directionXZ)); // angle between direction and directionXZ
	if (angle < 0.f) angle = 0;

	float speed = 10.f * sqrt(2.f); // speed of the throw; 1 second throw to 10 units when angle is 45 degrees
	float time = 6.f; // time of the throw; also means power of the throw

	// calculate range and height of the throw
	float range = speed * glm::cos(angle) * time; // range on XZ plane
	float height = speed * glm::sin(angle) * time;

	// bezier curve points
	glm::vec3 start = eye;
	glm::vec3 end = eye + range * directionXZ; // end point in the direction of the XZ plane projection
	end.y = 0.0f; // end point on the ground; XZ plane

	glm::vec3 controlPoint = (start + end) * .5f + glm::vec3(0, height, 0); // control point above the middle of the start and end points
	std::vector<glm::vec3> controlPoints = { controlPoint };

	fireball->getTransformation()->updateTranslateStep(
		std::make_shared<TransformationAnimationBezierCurve>(start, end, controlPoints, time));
}
