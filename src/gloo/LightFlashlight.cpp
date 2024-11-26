#include "LightFlashlight.h"
#include "Config.h"

// --- public ------------------------------------------------------------------
LightFlashlight::LightFlashlight(const std::string& t_name, Camera* t_camera)
	: Light(t_name, LightType::SPOT, *t_camera->getEye(), *t_camera->getDirection()) {
	this->setSpotCutoffDegrees(15.f);
	this->setDiffuseColor(glm::vec3(1.f, 1.f, 0.f)); // yellow
	this->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
	this->setAttenuation(1.f, .09f, .032f);

	t_camera->addObserver(this); // follow the camera
}

// --- protected ---------------------------------------------------------------
void LightFlashlight::processSubject(Camera* t_camera) {
	printf("[flashlight] name '%s' process subject : camera name '%s'\n", this->getName().c_str(), t_camera->getName().c_str());

	this->setPosition(*t_camera->getEye() - glm::vec3(0.f, Config::PLAYER_FLASHLIGHT_HEIGHT, 0.f));
	this->setDirection(*t_camera->getDirection());
}
