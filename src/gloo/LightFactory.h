#pragma once

#include "Light.h"

// glm
#include <glm/glm.hpp>

// standard c++ libraries
#include <memory>
#include <string>

class LightFactory {
public:
	LightFactory() = default;
	~LightFactory() = default;

	std::unique_ptr<Light> createLight(
		const std::string& t_name,
		const Light::lightTypeE t_type,
		const glm::vec3& t_position,
		const glm::vec3& t_direction = glm::vec3(0.f, 0.f, -1.f),
		const float t_spotCutoff = 0.f);

	std::unique_ptr<Light> createFlashlight(
		const std::string& t_name,
		const glm::vec3& t_position = glm::vec3(0.f),
		const glm::vec3& t_direction = glm::vec3(0.f, 0.f, -1.f));
	std::unique_ptr<Light> createFlashlight(const std::string& t_name, Camera* t_camera);
};
