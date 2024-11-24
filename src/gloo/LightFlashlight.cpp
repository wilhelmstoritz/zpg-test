#include "LightFlashlight.h"

// --- public ------------------------------------------------------------------
LightFlashlight::LightFlashlight(const std::string& t_name, const int t_type, const glm::vec3& t_position, const glm::vec3& t_direction, const float t_spotCutoff)
	: Light(t_name, t_type, t_position, t_direction, t_spotCutoff) { }

void LightFlashlight::addNotifyingSubject(Camera* t_camera) {
	this->processSubject(t_camera);
}

// --- protected ---------------------------------------------------------------
void LightFlashlight::processSubject(Camera* t_camera) {
	printf("[flashlight] name '%s' process subject : camera name '%s'\n", this->getName().c_str(), t_camera->getName().c_str());

	this->setPosition(*t_camera->getEye());
	this->setDirection(*t_camera->getDirection());
}
