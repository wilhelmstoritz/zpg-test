#include "LightWarehouse.h"

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//LightWarehouse* LightWarehouse::_instance = nullptr;
std::unique_ptr<LightWarehouse> LightWarehouse::_instance = nullptr;
std::mutex LightWarehouse::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// --- public ------------------------------------------------------------------
LightWarehouse* LightWarehouse::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr)
		//_instance = new LightWarehouse();
		_instance.reset(new LightWarehouse());

	//return _instance;
	return _instance.get();
}

LightWarehouse::~LightWarehouse() {
	// cleanup
	delete this->m_lightFactory;
}

void LightWarehouse::clearAll() {
	this->m_lights.clear();
}

void LightWarehouse::addLight(const std::string& t_name, std::unique_ptr<Light> t_light) {
	this->m_lights[t_name] = std::move(t_light);
}

void LightWarehouse::removeLight(const std::string& t_name) {
	this->m_lights.erase(t_name);
}

Light* LightWarehouse::getLight(const std::string& t_name) const {
	auto it = this->m_lights.find(t_name);

	return (it != this->m_lights.end()) ? it->second.get() : nullptr;
}

Light* LightWarehouse::createLight(
	const std::string& t_name,
	const Light::lightTypeE t_type,
	const glm::vec3& t_position,
	const glm::vec3& t_direction,
	const float t_spotCutoff)
{
	auto light = this->getLight(t_name);
	if (light == nullptr) {
		this->addLight(t_name, this->m_lightFactory->createLight(t_name, t_type, t_position, t_direction, t_spotCutoff));

		light = this->getLight(t_name);
	}

	return light;
}

Light* LightWarehouse::createFlashlight(
	const std::string& t_name,
	const glm::vec3& t_position,
	const glm::vec3& t_direction)
{
	auto light = this->getLight(t_name);
	if (light == nullptr) {
		this->addLight(t_name, this->m_lightFactory->createFlashlight(t_name, t_position, t_direction));

		light = this->getLight(t_name);
	}

	return light;
}

Light* LightWarehouse::createFlashlight(const std::string& t_name, Camera* t_camera) {
	auto light = this->getLight(t_name);
	if (light == nullptr) {
		this->addLight(t_name, this->m_lightFactory->createFlashlight(t_name, t_camera));

		light = this->getLight(t_name);
	}

	return light;
}

const std::unordered_map<std::string, std::unique_ptr<Light>>* LightWarehouse::getLights() const {
	return &this->m_lights;
}

// --- private -----------------------------------------------------------------
LightWarehouse::LightWarehouse() {
	this->m_lightFactory = new LightFactory();
}
