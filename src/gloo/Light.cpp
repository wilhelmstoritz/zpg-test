#include "Light.h"

// include GLM
#include <glm/glm.hpp>

// --- public ------------------------------------------------------------------
Light::Light(const std::string& t_name, const int t_type, const glm::vec3& t_position, const glm::vec3& t_direction, const float t_spotCutoff)
	: m_name(t_name), m_type(t_type), m_position(t_position), m_direction(t_direction), m_spotCutoff(t_spotCutoff) {
	// colors
	this->diffuseColor = glm::vec3(1.f, 1.f, 1.f);
	this->specularColor = glm::vec3(1.f, 1.f, 1.f);

	// attenuation coefficients
	this->constantAttenuation = 1.f; // basic light intensity
	this->linearAttenuation = .01f; // ...depends on the range of the light
	this->quadraticAttenuation = .001f; // ...larger value ensures faster attenuation

	// initialization to prevent visual studio warnings; values will be set later during setup
	this->m_ID = 0;
	this->m_numLights = 0;
}

std::string Light::getName() { return this->m_name; }
int Light::getID() { return this->m_ID; }
int Light::getNumLights() { return this->m_numLights; }

int Light::getType() { return this->m_type; }
glm::vec3* Light::getPosition() { return &this->m_position; }
glm::vec3* Light::getDirection() { return &this->m_direction; }
float Light::getSpotCutoff() { return this->m_spotCutoff; }

// get colors
glm::vec3* Light::getDiffuseColor() { return &this->diffuseColor; }
glm::vec3* Light::getSpecularColor() { return &this->specularColor; }

// get attenuation coefficients
float Light::getConstantAttenuation() { return this->constantAttenuation; }
float Light::getLinearAttenuation() { return this->linearAttenuation; }
float Light::getQuadraticAttenuation() { return this->quadraticAttenuation; }

void Light::setID(size_t t_ID) {
	this->m_ID = static_cast<int>(t_ID);
}

void Light::setNumLights(size_t t_numLights) {
	this->m_numLights = static_cast<int>(t_numLights);
}

void Light::setPosition(const glm::vec3& t_position) {
	this->m_position = t_position;

	this->notifyObservers();
}

void Light::setDirection(const glm::vec3& t_direction) {
	this->m_direction = t_direction;

	this->notifyObservers();
}

void Light::setSpotCutoff(float t_spotCutoff) {
	this->m_spotCutoff = t_spotCutoff;

	this->notifyObservers();
}

void Light::setSpotCutoffDegrees(float t_spotCutoffDegrees) {
	this->setSpotCutoff(glm::cos(glm::radians(t_spotCutoffDegrees)));
}

// set colors
void Light::setDiffuseColor(const glm::vec3& t_diffuseColor) {
	this->diffuseColor = t_diffuseColor;

	this->notifyObservers();
}

void Light::setSpecularColor(const glm::vec3& t_specularColor) {
	this->specularColor = t_specularColor;

	this->notifyObservers();
}

// set attenuation coefficients
void Light::setAttenuation(float t_constantAttenuation, float t_linearAttenuation, float t_quadraticAttenuation) {
	this->constantAttenuation = t_constantAttenuation;
	this->linearAttenuation = t_linearAttenuation;
	this->quadraticAttenuation = t_quadraticAttenuation;

	this->notifyObservers();
}

void Light::setConstantAttenuation(float t_constantAttenuation) {
	this->constantAttenuation = t_constantAttenuation;

	this->notifyObservers();
}

void Light::setLinearAttenuation(float t_linearAttenuation) {
	this->linearAttenuation = t_linearAttenuation;

	this->notifyObservers();
}

void Light::setQuadraticAttenuation(float t_quadraticAttenuation) {
	this->quadraticAttenuation = t_quadraticAttenuation;

	this->notifyObservers();
}

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

// --- protected ---------------------------------------------------------------
void Light::processSubject(Camera* t_camera) {
	printf("[light] name '%s' process subject : camera name '%s'\n", this->getName().c_str(), t_camera->getName().c_str());

	this->setPosition(*t_camera->getEye());
	this->setDirection(*t_camera->getDirection());
}

void Light::processSubject(Model* t_model) {
	printf("[light] name '%s' process subject : model\n", this->getName().c_str());
}
