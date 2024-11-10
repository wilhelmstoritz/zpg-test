#include "Light.h"

// --- public ------------------------------------------------------------------
Light::Light(const glm::vec3& t_position, const glm::vec3& t_color, float t_intensity)
	: m_position(t_position), m_color(t_color), m_intensity(t_intensity) { }

ObserverSubject<Light>* Light::getObserverSubject() { return &this->m_observerSubject; }

glm::vec3* Light::getPosition() { return &this->m_position; }
glm::vec3* Light::getColor() { return &this->m_color; }
float Light::getIntensity() { return this->m_intensity; }

void Light::updateLight(const glm::vec3& t_position, const glm::vec3& t_color, float t_intensity) {
	this->m_position = t_position;
	this->m_color = t_color;
	this->m_intensity = t_intensity;
}
