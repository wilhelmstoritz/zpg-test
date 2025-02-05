#pragma once

#include "Light.h"
#include "LightFactory.h"

// standard c++ libraries
#include <mutex>
#include <memory>
#include <unordered_map>

class LightWarehouse {
public:
	static LightWarehouse* getInstance();
	~LightWarehouse();

	void clearAll();

	/* likely to become private after the end of development/debugging */
	void addLight(const std::string& t_name, std::unique_ptr<Light> t_light);
	/* likely to become private after the end of development/debugging */

	void removeLight(const std::string& t_name);

	Light* getLight(const std::string& t_name) const;
	Light* createLight(
		const std::string& t_name,
		const Light::lightTypeE t_type,
		const glm::vec3& t_position = glm::vec3(0.f),
		const glm::vec3& t_direction = glm::vec3(0.f, 0.f, -1.f),
		const float t_spotCutoff = 0.f);

	Light* createFlashlight(
		const std::string& t_name,
		const glm::vec3& t_position = glm::vec3(0.f),
		const glm::vec3& t_direction = glm::vec3(0.f, 0.f, -1.f));
	Light* createFlashlight(const std::string& t_name, Camera* t_camera);
	const std::unordered_map<std::string, std::unique_ptr<Light>>* getLights() const;

private:
	// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - -
	// private constructor to avoid creating multiple instances
	LightWarehouse();

	// disable copy constructor and assignment operator
	LightWarehouse(const LightWarehouse&) = delete;
	LightWarehouse& operator=(const LightWarehouse&) = delete;

	// a singleton instance pointer
	//static LightWarehouse* _instance;
	static std::unique_ptr<LightWarehouse> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	std::unordered_map<std::string, std::unique_ptr<Light>> m_lights; // also retention for lifetime management

	LightFactory* m_lightFactory;
};
