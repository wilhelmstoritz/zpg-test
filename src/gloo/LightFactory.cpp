#include "LightFactory.h"
#include "LightFlashlight.h"

// --- public ------------------------------------------------------------------
std::unique_ptr<Light> LightFactory::createLight(
	const std::string& t_name,
	const Light::lightTypeE t_type,
	const glm::vec3& t_position,
	const glm::vec3& t_direction,
	const float t_spotCutoff)
{
	return std::make_unique<Light>(t_name, t_type, t_position, t_direction, t_spotCutoff);
}

std::unique_ptr<Light> LightFactory::createFlashlight(
	const std::string& t_name,
	const glm::vec3& t_position,
	const glm::vec3& t_direction)
{
	return std::make_unique<LightFlashlight>(t_name, t_position, t_direction);
}

std::unique_ptr<Light> LightFactory::createFlashlight(const std::string& t_name, Camera* t_camera) {
	return std::make_unique<LightFlashlight>(t_name, t_camera);
}
