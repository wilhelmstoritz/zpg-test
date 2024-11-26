#pragma once

#include "Light.h"

class LightFlashlight : public Light {
public:
    LightFlashlight(const std::string& t_name, const int t_type,
        const glm::vec3& t_position,
        const glm::vec3& t_direction = glm::vec3(0.f, 0.f, -1.f),
        const float t_spotCutoff = 0.f);

protected:
    virtual void processSubject(Camera* t_camera) override;
};
