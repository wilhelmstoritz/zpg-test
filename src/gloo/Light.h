#pragma once

#include "ObserverSubject.h"

// include GLM
#include <glm/vec3.hpp> // glm::vec3

class Light {
public:
    Light(const glm::vec3& t_position, const glm::vec3& t_color, float t_intensity);

    ObserverSubject<Light>* getObserverSubject();

    glm::vec3* getPosition();
    glm::vec3* getColor();
    float getIntensity();

    void updateLight(const glm::vec3& t_position, const glm::vec3& t_color, float t_intensity);

private:
    ObserverSubject<Light> m_observerSubject;

    glm::vec3 m_position;
    glm::vec3 m_color;
    float m_intensity;
};
