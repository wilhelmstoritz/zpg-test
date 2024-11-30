#include "LightFlashlight.h"
#include "Config.h"

// --- public ------------------------------------------------------------------
LightFlashlight::LightFlashlight(const std::string& t_name, Camera* t_camera)
	: Light(t_name, LightTypeE::SPOT, *t_camera->getEye(), *t_camera->getDirection()) {
	this->setSpotCutoffDegrees(Config::FLASHLIGHT_CUTOFF);
	//this->setDiffuseColor(glm::vec3(1.f, 1.f, 0.f)); // yellow
	//this->setDiffuseColor(glm::vec3(1.f, .9f, .7f)); // warm yellowish
	this->m_light.diffuseColor = glm::vec3(.9f, .95f, 1.f); // cold blue
	this->m_light.specularColor = glm::vec3(1.f, 1.f, 1.f);
	this->m_light.attenuation = glm::vec3(
		Config::FLASHLIGHT_ATTENUATION_CONSTANT,
		Config::FLASHLIGHT_ATTENUATION_LINEAR,
		Config::FLASHLIGHT_ATTENUATION_QUADRATIC);

	t_camera->addObserver(this); // follow the camera
}

// --- protected ---------------------------------------------------------------
void LightFlashlight::processSubject(Camera* t_camera) {
	printf("[flashlight] name '%s' process subject : camera name '%s'\n", this->getName().c_str(), t_camera->getName().c_str());

	this->m_light.position = *t_camera->getEye() - glm::vec3(0.f, Config::FLASHLIGHT_HEIGHT, 0.f);
	this->m_light.direction = *t_camera->getDirection();
}
