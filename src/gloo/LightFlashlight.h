#pragma once

#include "Light.h"
#include "Camera.h"

class LightFlashlight : public Light {
public:
    LightFlashlight(const std::string& t_name, Camera* t_camera);

protected:
    virtual void processSubject(Camera* t_camera) override;
};
