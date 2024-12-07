#include "SceneBuilderPlugin.h"
#include "AppUtils.h"

// --- public ------------------------------------------------------------------
void SceneBuilderPlugin::createContext(Scene* t_scene) {
	this->m_shaderResourcesPath = AppUtils::getInstance()->getResourcesPath() + "shaders.glsl/";

	this->m_scene = t_scene;
	this->m_shaderWarehouse = ShaderWarehouse::getInstance(); // for simplified use
	this->m_modelFactory = this->m_scene->getModelFactory();

	// fill the scene and bring it to life
	this->preProcess();

	this->createShaders();
	this->createLights();
	this->createModels();

	this->postProcess();
	this->addContextToScene();
}

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin::createLights() { } // default implementation; no lights
void SceneBuilderPlugin::createModels() { } // default implementation; no models

void SceneBuilderPlugin::preProcess() { } // default implementation; no pre-processing
void SceneBuilderPlugin::postProcess() { } // default implementation; no post-processing

void SceneBuilderPlugin::addContextToScene() {
	// add all (existing) models to the scene
	for (const auto& pair : *this->m_modelFactory->getModels()) {
		this->m_scene->addModel(pair.first, pair.second.get());
	}
}
