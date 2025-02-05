#include "Light.h"
#include "ModelLightEmitting.h"

// glm
#include <glm/glm.hpp>

// initialization of static class members
int Light::m_numLights = 0;

// --- public ------------------------------------------------------------------
Light::Light(const std::string& t_name, const lightTypeE t_type, const glm::vec3& t_position, const glm::vec3& t_direction, const float t_spotCutoff)
	//: m_name(t_name), m_type(t_type), m_position(t_position), m_direction(t_direction), m_spotCutoff(t_spotCutoff) {
	: m_name(t_name), m_light({ t_type, t_position, t_direction, t_spotCutoff }) {
	//this->m_light = { t_type, t_position, t_direction, t_spotCutoff };

	// to prevent visual studio warnings; value(s) will be set later
	this->m_ID = 0;
}

Light::Light(const lightTypeE t_type, const glm::vec3& t_position, const glm::vec3& t_direction, const float t_spotCutoff)
	: Light("@!#?@!", t_type, t_position, t_direction, t_spotCutoff) { }

std::string Light::getName() { return this->m_name; }
int Light::getID() { return this->m_ID; }
int Light::getNumLights() { return Light::m_numLights; }

const Light::lightT& Light::getLight() const { return this->m_light; }

/* obsolete; use getLight() instead
Light::lightTypeE Light::getType()     const { return static_cast<lightTypeE>(this->m_light.type); }
const glm::vec3& Light::getPosition()  const { return this->m_light.position; }
const glm::vec3& Light::getDirection() const { return this->m_light.direction; }
float Light::getSpotCutoff()           const { return this->m_light.spotCutoff; }*/

// get colors
const glm::vec3& Light::getDiffuseColor() const { return this->m_light.diffuseColor; }
const glm::vec3& Light::getSpecularColor() const { return this->m_light.specularColor; }

// get attenuation coefficients
const glm::vec3& Light::getAttenuation() const { return this->m_light.attenuation; }
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

/* debugging purposes only; template specialization is used in production
template <>
void Light::follow<Camera>() {
	/ *if (this->Observer<Camera>::needsUpdate())
		printf("[light] name %s id %d : follow camera\n", this->getName().c_str(), this->getID());* /

	this->Observer<Camera>::processAllSubjects();
}

template <>
void Light::follow<ModelLightEmitting>() {
	/ *if (this->Observer<ModelLightEmitting>::needsUpdate())
		printf("[light] name %s id %d : follow model\n", this->getName().c_str(), this->getID());* /

	this->Observer<ModelLightEmitting>::processAllSubjects();
}*/

void Light::addNotifyingSubject(Camera* t_camera) {
	//this->processSubject(t_camera); // directly process the subject

	this->Observer<Camera>::addNotifyingSubject(t_camera);
	this->notifyObservers();
}

void Light::addNotifyingSubject(ModelLightEmitting* t_model) {
	//this->processSubject(t_model); // directly process the subject

	this->Observer<ModelLightEmitting>::addNotifyingSubject(t_model);
	this->notifyObservers();
}

// --- protected ---------------------------------------------------------------
void Light::processSubject(Camera* t_camera) {
	//printf("[light] name '%s' process subject : camera name '%s'\n", this->getName().c_str(), t_camera->getName().c_str());

	this->m_light.position  = t_camera->getEye();
	this->m_light.direction = t_camera->getDirection();

	//this->notifyObservers(); // in case directly process the subject
}

void Light::processSubject(ModelLightEmitting* t_model) {
	//printf("[light] name '%s' process subject : model\n", this->getName().c_str());

	this->m_light.position = glm::vec3(t_model->getTransformation()->getModelMatrix()[3]); // position is the fourth column of the model matrix
	this->m_light.direction = glm::normalize(glm::vec3(t_model->getTransformation()->getModelMatrix()[2])); // direction is the third column of the model matrix; direction of the z-axis

	this->m_light.diffuseColor  = t_model->getKDiffuse()  * t_model->getDiffuseColor();
	this->m_light.specularColor = t_model->getKSpecular() * t_model->getSpecularColor();

	//this->notifyObservers(); // in case directly process the subject
}
