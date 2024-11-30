#include "Light.h"
#include "Model.h"

// include GLM
#include <glm/glm.hpp>

// initialization of static class members
int Light::m_numLights = 0;

// --- public ------------------------------------------------------------------
Light::Light(const std::string& t_name, const int t_type, const glm::vec3& t_position, const glm::vec3& t_direction, const float t_spotCutoff)
	//: m_name(t_name), m_type(t_type), m_position(t_position), m_direction(t_direction), m_spotCutoff(t_spotCutoff) {
	: m_name(t_name), m_light({ t_type, t_position, t_direction, t_spotCutoff }) {
	//this->m_light = { t_type, t_position, t_direction, t_spotCutoff };

	/*
	// colors
	this->diffuseColor = glm::vec3(1.f, 1.f, 1.f);
	this->specularColor = glm::vec3(1.f, 1.f, 1.f);

	// attenuation coefficients
	this->constantAttenuation = 1.f; // basic light intensity
	this->linearAttenuation = .01f; // ...depends on the range of the light
	this->quadraticAttenuation = .001f; // ...larger value ensures faster attenuation
	*/

	// initialization to prevent visual studio warnings; values will be set later during setup
	this->m_ID = 0;
}

std::string Light::getName() { return this->m_name; }
int Light::getID() { return this->m_ID; }
int Light::getNumLights() { return Light::m_numLights; }

Light::lightT& Light::getLight() { return this->m_light; }

/* obsolete; for backward compatibility only; use getLight() instead */
int Light::getType() { return this->m_light.type; }
glm::vec3& Light::getPosition() { return this->m_light.position; }
glm::vec3& Light::getDirection() { return this->m_light.direction; }
float Light::getSpotCutoff() { return this->m_light.spotCutoff; }

// get colors
glm::vec3& Light::getDiffuseColor() { return this->m_light.diffuseColor; }
glm::vec3& Light::getSpecularColor() { return this->m_light.specularColor; }

// get attenuation coefficients
glm::vec3& Light::getAttenuation() { return this->m_light.attenuation; }
/* obsolete end */

void Light::setID(size_t t_ID) {
	this->m_ID = static_cast<int>(t_ID);
}

void Light::setNumLights(size_t t_numLights) {
	Light::m_numLights = static_cast<int>(t_numLights);
}

void Light::setLight(const lightT& t_light) {
	this->m_light = t_light;

	this->notifyObservers();
}

/* obsolete; for backward compatibility only; use getLight() instead */
void Light::setPosition(const glm::vec3& t_position) {
	this->m_light.position = t_position;

	this->notifyObservers();
}

void Light::setDirection(const glm::vec3& t_direction) {
	this->m_light.direction = t_direction;

	this->notifyObservers();
}

void Light::setSpotCutoff(float t_spotCutoff) {
	this->m_light.spotCutoff = t_spotCutoff;

	this->notifyObservers();
}

void Light::setSpotCutoffDegrees(float t_spotCutoffDegrees) {
	this->setSpotCutoff(glm::cos(glm::radians(t_spotCutoffDegrees)));
}

// set colors
void Light::setDiffuseColor(const glm::vec3& t_diffuseColor) {
	this->m_light.diffuseColor = t_diffuseColor;

	this->notifyObservers();
}

void Light::setSpecularColor(const glm::vec3& t_specularColor) {
	this->m_light.specularColor = t_specularColor;

	this->notifyObservers();
}

// set attenuation coefficients
void Light::setAttenuation(const glm::vec3& t_attenuation) {
	this->m_light.attenuation = t_attenuation;

	this->notifyObservers();
}
/* obsolete end */

/*
void Light::updateLight(const glm::vec3& t_position, const glm::vec3& t_direction, const float t_spotCutoff, const glm::vec3& t_diffuseColor, const glm::vec3& t_specularColor) {
	this->m_position = t_position;
	this->m_direction = t_direction;
	this->m_spotCutoff = t_spotCutoff;

	this->diffuseColor = t_diffuseColor;
	this->specularColor = t_specularColor;

	this->notifyObservers();
}
*/

void Light::addNotifyingSubject(Camera* t_camera) {
	this->processSubject(t_camera);
}

void Light::addNotifyingSubject(Model* t_model) {
	this->processSubject(t_model);
}

// --- protected ---------------------------------------------------------------
void Light::processSubject(Camera* t_camera) {
	//printf("[light] name '%s' process subject : camera name '%s'\n", this->getName().c_str(), t_camera->getName().c_str());

	this->m_light.position = *t_camera->getEye();
	this->m_light.direction = *t_camera->getDirection();
}

void Light::processSubject(Model* t_model) {
	//printf("[light] name '%s' process subject : model\n", this->getName().c_str());

	this->m_light.position = glm::vec3(t_model->getTransformation()->getModelMatrix()[3]); // position is the fourth column of the model matrix
	this->m_light.direction = glm::normalize(glm::vec3(t_model->getTransformation()->getModelMatrix()[2])); // direction is the third column of the model matrix; direction of the z-axis

	this->m_light.diffuseColor = t_model->getKDiffuse() * t_model->getDiffuseColor();
}
