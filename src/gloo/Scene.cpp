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
}

void Scene::clearAllModels() {
	this->m_models.clear();
}

void Scene::addModel(Model* t_model) {
	this->m_models.push_back(t_model);
}

void Scene::removeModel(Model* t_model) {
	this->m_models.erase(std::remove(this->m_models.begin(), this->m_models.end(), t_model), this->m_models.end());
}

Camera* Scene::getCamera() {
	return this->m_camera;
}

Light* Scene::getLight(const std::string& t_name) const {
	auto it = this->m_lights.find(t_name);
	return (it != this->m_lights.end()) ? it->second : nullptr;
}

ShaderFactory* Scene::getShaderFactory() const {
	return this->m_shaderFactory;
}

ModelFactory* Scene::getModelFactory() const {
	return this->m_modelFactory;
}

const std::vector<Model*>& Scene::getModels() const {
	return this->m_models;
}

/*
const std::vector<Model*>* Scene::getModels() const {
	return &this->m_models;
}
*/

void Scene::addCamera(Camera* t_camera) {
	printf("[scene] add camera\n");

	this->m_camera = t_camera;
	this->setCamera(t_camera);
}

void Scene::setAllCameras() {
	this->setCamera(this->m_camera);
}

void Scene::addLight(const std::string& t_name, Light* t_light) {
	printf("[scene] add light : name %s\n", t_name);

	this->m_lights[t_name] = t_light;
	this->setLight(t_light);
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
