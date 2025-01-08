#pragma once

#include "Light.h"
#include "Camera.h"

class LightFlashlight : public Light {
public:
    LightFlashlight(const std::string& t_name,
        const glm::vec3& t_position  = glm::vec3(0.f),
        const glm::vec3& t_direction = glm::vec3(0.f, 0.f, -1.f));
    LightFlashlight(
        const glm::vec3& t_position  = glm::vec3(0.f),
        const glm::vec3& t_direction = glm::vec3(0.f, 0.f, -1.f));
    LightFlashlight(const std::string& t_name, Camera* t_camera);
    LightFlashlight(Camera* t_camera);

	void turnOn();
	void turnOff();
	void toggle();

protected:
	bool m_state;

    virtual void processSubject(Camera* t_camera) override;
};
