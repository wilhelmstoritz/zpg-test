#include "Light.h"

// --- public ------------------------------------------------------------------
Light::Light(const std::string& t_name, const int t_type, const glm::vec3& t_position, const glm::vec3& t_direction, const float t_spotCutoff)
	: m_name(t_name), m_type(t_type), m_position(t_position), m_direction(t_direction), m_spotCutoff(t_spotCutoff) {
	// colors and intensity
	this->diffuseColor = glm::vec3(1.f, 1.f, 1.f);
	this->specularColor = glm::vec3(1.f, 1.f, 1.f);

	this->m_intensity = 1.f;

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
glm::vec3* Light::getDiffuseColor() { return &this->diffuseColor; }
glm::vec3* Light::getSpecularColor() { return &this->specularColor; }
float Light::getIntensity() { return this->m_intensity; }

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

void Light::setDiffuseColor(const glm::vec3& t_diffuseColor) {
	this->diffuseColor = t_diffuseColor;

	this->notifyObservers();
}

void Light::setSpecularColor(const glm::vec3& t_specularColor) {
	this->specularColor = t_specularColor;

	this->notifyObservers();
}

void Light::setIntensity(float t_intensity) {
	this->m_intensity = t_intensity;

	this->notifyObservers();
}

/*
void Light::updateLight(const glm::vec3& t_position, const glm::vec3& t_direction, const float t_spotCutoff, const glm::vec3& t_diffuseColor, const glm::vec3& t_specularColor, const float t_intensity) {
	this->m_position = t_position;
	this->m_direction = t_direction;
	this->m_spotCutoff = t_spotCutoff;

	this->diffuseColor = t_diffuseColor;
	this->specularColor = t_specularColor;
	this->m_intensity = t_intensity;

	this->notifyObservers();
}
*/
