#pragma once

#include "Light.h"

// include the standard C++ headers
#include <memory>
#include <string>

class LightFactory {
public:
	LightFactory() = default;
	~LightFactory() = default;

	std::unique_ptr<Light> createLight(
		const std::string& t_name,
		const int t_type,
		const glm::vec3& t_position,
		const glm::vec3& t_direction = glm::vec3(0.f, 0.f, -1.f),
		const float t_spotCutoff = 0.f);
};
