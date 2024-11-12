#include "Scene.h"

// --- public ------------------------------------------------------------------
Scene::Scene(Camera* t_camera) : m_camera(t_camera) {
	this->m_shaderFactory = new ShaderFactory();
	this->m_modelFactory = new ModelFactory(this->m_shaderFactory);
}

Scene::~Scene() {
	// cleanup
	delete this->m_modelFactory;
	delete this->m_shaderFactory;

	delete this->m_camera;
	delete this->m_light;
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

void Scene::setCamera() {
	printf("[scene] set camera\n");

	this->m_camera->removeAllObservers();

	for (const auto& pair : *this->m_shaderFactory->getShaderPrograms()) {
		this->m_camera->addObserver(pair.second.get());
	}
}

void Scene::setCamera(Camera* t_camera) {
	this->m_camera = t_camera;
	this->setCamera();
}

void Scene::setLight() {
	printf("[scene] set light\n");

	this->m_light->getObserverSubject()->removeAllObservers();

	for (const auto& pair : *this->m_shaderFactory->getShaderPrograms()) {
		this->m_light->getObserverSubject()->addObserver(pair.second.get());
	}
}

void Scene::setLight(Light* t_light) {
	this->m_light = t_light;
	this->setLight();
}
