#include "LightFactory.h"

// --- public ------------------------------------------------------------------
std::unique_ptr<Light> LightFactory::createLight(
	const std::string& t_name,
	const int t_type,
	const glm::vec3& t_position,
	const glm::vec3& t_direction,
	const float t_spotCutoff)
{
	return std::make_unique<Light>(t_name, t_type, t_position, t_direction, t_spotCutoff);
}
