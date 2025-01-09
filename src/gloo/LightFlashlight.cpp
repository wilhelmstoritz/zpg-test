#include "LightFlashlight.h"
#include "Config.h"

// --- public ------------------------------------------------------------------
LightFlashlight::LightFlashlight(const std::string& t_name,
	const glm::vec3& t_position,
	const glm::vec3& t_direction)
	: Light(t_name, lightTypeE::SPOT_LIGHT, t_position, t_direction)
{
	this->setSpotCutoffDegrees(Config::FLASHLIGHT_CUTOFF);
	/*//this->setDiffuseColor(glm::vec3(1.f, 1.f, 0.f)); // yellow
	//this->setDiffuseColor(glm::vec3(1.f, .9f, .7f)); // warm yellowish
	this->setDiffuseColor(glm::vec3(.9f, .95f, 1.f)); // cold blue
	this->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));*/
	this->turnOn();
	this->setAttenuation(Config::FLASHLIGHT_ATTENUATION);
}

LightFlashlight::LightFlashlight(
	const glm::vec3& t_position,
	const glm::vec3& t_direction)
	: LightFlashlight("flashlight:@!#?@!", t_position, t_direction) { }

LightFlashlight::LightFlashlight(const std::string& t_name, Camera* t_camera)
	: LightFlashlight(t_name, t_camera->getEye(), t_camera->getDirection()) {
	t_camera->addObserver(this); // follow the camera
}

LightFlashlight::LightFlashlight(Camera* t_camera)
	: LightFlashlight("flashlight:@!#?@!", t_camera) { }

void LightFlashlight::turnOn() {
	// temporary solution; hardcoded color -> will be replaced by a proper solution
	//this->setDiffuseColor(glm::vec3(1.f, 1.f, 0.f)); // yellow
	//this->setDiffuseColor(glm::vec3(1.f, .9f, .7f)); // warm yellowish
	this->setDiffuseColor(glm::vec3(.9f, .95f, 1.f)); // cold blue
	this->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));

	this->m_state = true;
}

void LightFlashlight::turnOff() {
	// temporary solution; set the color to black -> no light -->> will be replaced by a proper solution
	this->setDiffuseColor(glm::vec3(0.f));
	this->setSpecularColor(glm::vec3(0.f));

	this->m_state = false;
}

void LightFlashlight::toggle() {
	if (this->m_state) this->turnOff();
	else               this->turnOn();
}

// --- protected ---------------------------------------------------------------
void LightFlashlight::processSubject(Camera* t_camera) {
	//printf("[flashlight] name '%s' process subject : camera name '%s'\n", this->getName().c_str(), t_camera->getName().c_str());

	this->setPosition(t_camera->getEye() + glm::vec3(0.f, Config::FLASHLIGHT_OFFSET, 0.f));
	this->setDirection(t_camera->getDirection());
}
