#pragma once

#include "ObserverSubject.h"

// include GLM
#include <glm/vec3.hpp> // glm::vec3

class Light : public ObserverSubject<Light> {
public:
    Light(const glm::vec3& t_position, const glm::vec3& t_color, float t_intensity);

    int getLightID();
    int getNumLights();

    glm::vec3* getPosition();
    glm::vec3* getColor();
    float getIntensity();

    void setLightID(size_t t_lightID);
    void setNumLights(size_t t_numLights);

    void updateLight(const glm::vec3& t_position, const glm::vec3& t_color, float t_intensity);

private:
    int m_lightID;
    int m_numLights;

    glm::vec3 m_position;
    glm::vec3 m_color;
    float m_intensity;
};
