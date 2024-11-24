#pragma once

#include "ObserverSubject.h"

// include GLM
#include <glm/vec3.hpp> // glm::vec3

// include the standard C++ headers
#include <string>

class Light : public ObserverSubject<Light> {
public:
    Light(const std::string& t_name, const int t_type,
        const glm::vec3& t_position,
        const glm::vec3& t_direction = glm::vec3(0.f, 0.f, -1.f),
        const float t_spotCutoff = 0.f);

    std::string getName();
    int getID();
    int getNumLights();

    int getType();
    glm::vec3* getPosition();
    glm::vec3* getDirection();
    float getSpotCutoff();

    // get colors
    glm::vec3* getDiffuseColor();
    glm::vec3* getSpecularColor();

    // get attenuation coefficients
    float getConstantAttenuation();
    float getLinearAttenuation();
    float getQuadraticAttenuation();

    void setID(size_t t_ID);
    void setNumLights(size_t t_numLights);

    void setPosition(const glm::vec3& t_position);
    void setDirection(const glm::vec3& t_direction);
    void setSpotCutoff(float t_spotCutoff); // value of cos(radians)
    void setSpotCutoffDegrees(float t_spotCutoffDegrees);

    // set colors
    void setDiffuseColor(const glm::vec3& t_diffuseColor);
    void setSpecularColor(const glm::vec3& t_specularColor);

    // set attenuation coefficients
    void setAttenuation(float t_constantAttenuation, float t_linearAttenuation, float t_quadraticAttenuation);
    void setConstantAttenuation(float t_constantAttenuation);
    void setLinearAttenuation(float t_linearAttenuation);
    void setQuadraticAttenuation(float t_quadraticAttenuation);

    //void updateLight(const glm::vec3& t_position, const glm::vec3& t_direction, const float t_spotCutoff, const glm::vec3& t_diffuseColor, const glm::vec3& t_specularColor, const float t_intensity);

private:
    std::string m_name;
    int m_ID;
    int m_numLights;

    int m_type; // 0 = directional light, 1 = point light, 2 = spotlight

    glm::vec3 m_position;
    glm::vec3 m_direction;
    float m_spotCutoff; // value of cos(radians)

    // colors
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;

    // attenuation coefficients
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};
