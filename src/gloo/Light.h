#pragma once

#include "ObserverSubject.h"

// include GLM
#include <glm/vec3.hpp> // glm::vec3

class Light : public ObserverSubject<Light> {
public:
    Light(const int t_type,
        const glm::vec3& t_position,
        const glm::vec3& t_direction = glm::vec3(0.f, 0.f, -1.f),
        const float t_spotCutoff = 0.f);

    int getLightID();
    int getNumLights();

    int getType();
    glm::vec3* getPosition();
    glm::vec3* getDirection();
    float getSpotCutoff();
    glm::vec3* getDiffuseColor();
    glm::vec3* getSpecularColor();
    float getIntensity();

    void setLightID(size_t t_lightID);
    void setNumLights(size_t t_numLights);

    void setPosition(const glm::vec3& t_position);
    void setDirection(const glm::vec3& t_direction);
    void setSpotCutoff(float t_spotCutoff);
    void setDiffuseColor(const glm::vec3& t_diffuseColor);
    void setSpecularColor(const glm::vec3& t_specularColor);
    void setIntensity(float t_intensity);

    //void updateLight(const glm::vec3& t_position, const glm::vec3& t_direction, const float t_spotCutoff, const glm::vec3& t_diffuseColor, const glm::vec3& t_specularColor, const float t_intensity);

private:
    int m_lightID;
    int m_numLights;

    int m_type; // 0 = directional light, 1 = point light, 2 = spotlight

    glm::vec3 m_position;
    glm::vec3 m_direction;
    float m_spotCutoff;

    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
    float m_intensity;
};
