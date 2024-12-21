#include "Scene.h"
#include "ShaderWarehouse.h"

// --- public ------------------------------------------------------------------
Scene::Scene(const std::string& t_name, Camera* t_camera, float t_xmin, float t_xmax, float t_ymin, float t_ymax, float t_zmin, float t_zmax)
	: m_name(t_name), m_xmin(t_xmin), m_xmax(t_xmax), m_ymin(t_ymin), m_ymax(t_ymax), m_zmin(t_zmin), m_zmax(t_zmax)
{
	this->addCamera(t_camera); // !!! CONSIDER REMOVING FROM CONSTRUCTOR; JUST VIA ADDCAMERA() !!!
}

Scene::Scene(Camera* t_camera, float t_xmin, float t_xmax, float t_ymin, float t_ymax, float t_zmin, float t_zmax)
	: Scene("@!#?@!", t_camera, t_xmin, t_xmax, t_ymin, t_ymax, t_zmin, t_zmax) { }

Scene::~Scene() {
	// cleanup
	delete this->m_camera;
}

void Scene::addCamera(Camera* t_camera) {
	//printf("[scene] add camera : name '%s'\n", t_camera->getName().c_str());

	this->m_camera = t_camera;
	this->setCamera(t_camera);
}

void Scene::addLight(const std::string& t_name, Light* t_light) {
	//printf("[scene] add light : name '%s'\n", name.c_str());

	if (this->m_lights.find(t_name) == this->m_lights.end()) { // if light does not exist
		this->m_lightsOrder.push_back(t_name);
		this->m_lightsOrderIndex[t_name] = this->m_lightsOrder.size() - 1;
	}
	this->m_lights[t_name] = t_light;

	t_light->setID(this->m_lightsOrderIndex[t_name]);
	t_light->setNumLights(this->m_lightsOrder.size());

	this->setLight(t_light);
}

void Scene::addModel(const std::string& t_name, Model* t_model) {
	//printf("[scene] add model\n");

	this->m_models[t_name] = t_model;
}

void Scene::removeLight(const std::string& t_name) {
	//printf("[scene] remove light : name %s\n", t_name.c_str());

	auto it = this->m_lights.find(t_name);
	if (it == this->m_lights.end()) {
		printf("error [scene] remove light : name %s; light not found\n", t_name.c_str());
		return;
	}

	// delete light and remove its reference from list
	delete this->m_lights.find(t_name)->second;

	//this->m_lights.erase(t_name);
	this->m_lights.erase(it);

	// remove light from order / order index lists
	auto itOrder = std::find(this->m_lightsOrder.begin(), this->m_lightsOrder.end(), t_name);
	if (itOrder != this->m_lightsOrder.end()) {
		this->m_lightsOrder.erase(itOrder);
		this->m_lightsOrderIndex.erase(t_name);
	}

	// recalculate order index to match the current order; update ID/numLights lights data
	size_t numLights = this->m_lightsOrder.size();

	for (size_t i = 0; i < numLights; ++i) {
		this->m_lightsOrderIndex[this->m_lightsOrder[i]] = i;

		Light* light = this->m_lights[this->m_lightsOrder[i]];
		light->setID(i);
		light->setNumLights(numLights);

		//this->setLight(light); // !!! CONSIDER REMOVING; LIGHTS ARE SET ONCE !!!
	}
}

void Scene::removeModel(const std::string& t_name) {
	//printf("[scene] remove model : name %s\n", t_name.c_str());

	auto it = this->m_models.find(t_name);
	if (it == this->m_models.end()) {
		printf("error [scene] remove model : name %s; model not found\n", t_name.c_str());
		return;
	}

	// delete model reference from list
	//this->m_models.erase(t_name);
	this->m_models.erase(it);
}

void Scene::removeAllModels() {
	this->m_models.clear();
}

Camera* Scene::getCamera() {
	return this->m_camera;
}

Light* Scene::getLight(const std::string& t_name) const {
	auto it = this->m_lights.find(t_name);
	return (it != this->m_lights.end()) ? it->second : nullptr;
}

const std::unordered_map<std::string, Model*>& Scene::getModels() const {
	return this->m_models;
}

/*
const std::unordered_map<std::string, Model*>* Scene::getModels() const {
	return &this->m_models;
}
*/

void Scene::setAllCameras() {
	this->setCamera(this->m_camera);
}

void Scene::setAllLights() {
	for (const auto& pair : this->m_lights) {
		this->setLight(pair.second);
	}
}

void Scene::callbackFramebufferSize(int t_width, int t_height) {
	//printf("[scene] callback framebuffer size : width %d, height %d\n", t_width, t_height);

	// update camera projection matrix
	this->m_camera->setProjection(Config::CAMERA_FOV, static_cast<float>(t_width) / static_cast<float>(t_height), Config::CAMERA_NEAR, Config::CAMERA_FAR);
}

// --- private -----------------------------------------------------------------
void Scene::setCamera(Camera* t_camera) {
	//printf("[scene] set camera : name '%s'\n", t_camera->getName().c_str());

	//t_camera->removeAllObservers(); // !!! CONSIDER REMOVING; OBSERVERS ARE/CAN BE SET NOT ONLY FROM HERE !!!

	for (const auto& pair : *ShaderWarehouse::getInstance()->getShaderPrograms()) {
		t_camera->addObserver(pair.second.get());
	}
}

void Scene::setLight(Light* t_light) {
	//printf("[scene] set light : name '%s'\n", t_light->getName().c_str());

	//t_light->removeAllObservers(); // !!! CONSIDER REMOVING; OBSERVERS ARE/CAN BE SET NOT ONLY FROM HERE !!!

	for (const auto& pair : *ShaderWarehouse::getInstance()->getShaderPrograms()) {
		t_light->addObserver(pair.second.get());
	}
}
