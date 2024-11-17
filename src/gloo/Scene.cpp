#include "Scene.h"

// --- public ------------------------------------------------------------------
Scene::Scene(Camera* t_camera) {
	this->m_shaderFactory = new ShaderFactory();
	this->m_modelFactory = new ModelFactory(this->m_shaderFactory);

	this->addCamera(t_camera); // !!! CONSIDER REMOVING FROM CONSRUCTOR; JUST VIA ADDCAMERA() !!!
}

Scene::~Scene() {
	// cleanup
	delete this->m_modelFactory;
	delete this->m_shaderFactory;

	delete this->m_camera;
	for (const auto& pair : this->m_lights) {
		delete pair.second;
	}
}

void Scene::addModel(const std::string& t_name, Model* t_model) {
	printf("[scene] add model\n");

	this->m_models[t_name] = t_model;
}

void Scene::addCamera(Camera* t_camera) {
	printf("[scene] add camera\n");

	this->m_camera = t_camera;
	this->setCamera(t_camera);
}

void Scene::addLight(const std::string& t_name, Light* t_light) {
	printf("[scene] add light : name %s\n", t_name.c_str());

	if (this->m_lights.find(t_name) == this->m_lights.end()) { // if light does not exist
		this->m_lightsOrder.push_back(t_name);
		this->m_lightsOrderIndex[t_name] = this->m_lightsOrder.size() - 1;
	}
	this->m_lights[t_name] = t_light;

	t_light->setLightID(this->m_lightsOrderIndex[t_name]);
	t_light->setNumLights(this->m_lightsOrder.size());

	this->setLight(t_light);
}

void Scene::removeModel(const std::string& t_name) {
	printf("[scene] remove model : name %s\n", t_name.c_str());

	auto it = this->m_models.find(t_name);
	if (it == this->m_models.end()) {
		printf("error [scene] remove model : name %s; model not found\n", t_name.c_str());
		return;
	}

	// delete model reference from list
	//this->m_models.erase(t_name);
	this->m_models.erase(it);
}

void Scene::removeLight(const std::string& t_name) {
	printf("[scene] remove light : name %s\n", t_name.c_str());

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

	// recalculate order index to match the current order; update lightID/numLights lights data
	size_t numLights = this->m_lightsOrder.size();

	for (size_t i = 0; i < numLights; ++i) {
		this->m_lightsOrderIndex[this->m_lightsOrder[i]] = i;

		Light* light = this->m_lights[this->m_lightsOrder[i]];
		light->setLightID(i);
		light->setNumLights(numLights);

		this->setLight(light);
	}
}

void Scene::removeAllModels() {
	this->m_models.clear();
}

/*
void Scene::removeAllLights() {
	this->m_lights.clear();
}
*/

ShaderFactory* Scene::getShaderFactory() const {
	return this->m_shaderFactory;
}

ModelFactory* Scene::getModelFactory() const {
	return this->m_modelFactory;
}

const std::unordered_map<std::string, Model*>& Scene::getModels() const {
	return this->m_models;
}

/*
const std::unordered_map<std::string, Model*>* Scene::getModels() const {
	return &this->m_models;
}
*/

Camera* Scene::getCamera() {
	return this->m_camera;
}

Light* Scene::getLight(const std::string& t_name) const {
	auto it = this->m_lights.find(t_name);
	return (it != this->m_lights.end()) ? it->second : nullptr;
}

void Scene::setAllCameras() {
	this->setCamera(this->m_camera);
}

void Scene::setAllLights() {
	for (const auto& pair : this->m_lights) {
		this->setLight(pair.second);
	}
}

// --- private -----------------------------------------------------------------
void Scene::setCamera(Camera* t_camera) {
	printf("[scene] set camera\n");

	t_camera->removeAllObservers();

	for (const auto& pair : *this->m_shaderFactory->getShaderPrograms()) {
		t_camera->addObserver(pair.second.get());
	}
}

void Scene::setLight(Light* t_light) {
	printf("[scene] set light\n");

	t_light->removeAllObservers();

	for (const auto& pair : *this->m_shaderFactory->getShaderPrograms()) {
		t_light->addObserver(pair.second.get());
	}
}
