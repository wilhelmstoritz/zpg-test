#include "SceneBuilderPlugin.h"
#include "AppUtils.h"

// --- public ------------------------------------------------------------------
SceneBuilderPlugin::SceneBuilderPlugin() {
	this->m_shaderResourcesPath = AppUtils::getInstance()->getResourcesPath() + "shaders.glsl/";

	this->m_shaderWarehouse = ShaderWarehouse::getInstance(); // for simplified use
	this->m_lightWarehouse = LightWarehouse::getInstance();
	this->m_modelWarehouse = ModelWarehouse::getInstance();
	this->m_textureWarehouse = TextureWarehouse::getInstance();

	// to prevent visual studio warnings; value(s) will be set later
	this->m_scene = nullptr;
}

void SceneBuilderPlugin::createContext(Scene* t_scene) {
	this->m_scene = t_scene;

	// fill the scene and bring it to life
	this->preProcess();

	this->createShaders();
	this->createLights();
	this->createModels();
	this->loadTextures();

	this->postProcess();
	this->addContextToScene();
}

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin::createLights() { } // default implementation; no lights
void SceneBuilderPlugin::createModels() { } // default implementation; no models
void SceneBuilderPlugin::loadTextures() { } // default implementation; no textures

void SceneBuilderPlugin::preProcess() { } // default implementation; no pre-processing
void SceneBuilderPlugin::postProcess() { } // default implementation; no post-processing

void SceneBuilderPlugin::addContextToScene() {
	// add all (existing) lights to the scene
	//for (const auto& pair : *LightWarehouse::getInstance()->getLights()) {
	for (const auto& pair : *this->m_lightWarehouse->getLights()) {
		this->m_scene->addLight(pair.first, pair.second.get());
	}

	// add all (existing) models to the scene
	//for (const auto& pair : *ModelWarehouse::getInstance()->getModels()) {
	for (const auto& pair : *this->m_modelWarehouse->getModels()) {
		this->m_scene->addModel(pair.first, pair.second.get());
	}
}
