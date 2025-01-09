#include "SceneBuilderPlugin.h"
#include "AppUtils.h"
#include "Config.h"

// --- public ------------------------------------------------------------------
SceneBuilderPlugin::SceneBuilderPlugin() {
	this->m_windowTitle = Config::WINDOW_TITLE + Config::WINDOW_TITLE_HELP;

	this->m_shaderResourcesPath  = AppUtils::getInstance()->getResourcesPath() + Config::SYSTEM_RESOURCES_RELPATH_SHADERS;
	this->m_modelResourcesPath   = AppUtils::getInstance()->getResourcesPath() + Config::SYSTEM_RESOURCES_RELPATH_MODELS;
	this->m_textureResourcesPath = AppUtils::getInstance()->getResourcesPath() + Config::SYSTEM_RESOURCES_RELPATH_TEXTURES;

	this->m_shaderWarehouse  = ShaderWarehouse::getInstance(); // for simplified access
	this->m_lightWarehouse   = LightWarehouse::getInstance();
	this->m_modelWarehouse   = ModelWarehouse::getInstance();
	this->m_textureWarehouse = TextureWarehouse::getInstance();

	// to prevent visual studio warnings; value(s) will be set later
	this->m_scene = nullptr;

	this->m_min = this->m_max = this->m_size = this->m_center = glm::vec3(0.f);
}

void SceneBuilderPlugin::setSceneProperties(Scene* t_scene) {
	t_scene->setTitle(this->m_windowTitle);
}

void SceneBuilderPlugin::createContext(Scene* t_scene) {
	this->m_scene = t_scene;
	this->setEnvironment();

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
void SceneBuilderPlugin::setEnvironment() {
	// scene dimensions
	this->m_min    = this->m_scene->getMin();
	this->m_max    = this->m_scene->getMax();
	this->m_size   = this->m_scene->getSize();
	this->m_center = this->m_scene->getCenter();
}

void SceneBuilderPlugin::createLights() { } // default implementation; no lights
void SceneBuilderPlugin::loadTextures() { } // default implementation; no textures

void SceneBuilderPlugin::preProcess()  { } // default implementation; no pre-processing
void SceneBuilderPlugin::postProcess() { } // default implementation; no post-processing

void SceneBuilderPlugin::addContextToScene() { // default implementation; debugging purposes only; should be overridden
	// add all (existing) lights to the scene
	for (const auto& pair : *this->m_lightWarehouse->getLights())
		this->m_scene->addLight(pair.first, pair.second.get());

	// add all (existing) models to the scene
	for (const auto& pair : *this->m_modelWarehouse->getModels())
		this->m_scene->addModel(pair.first, pair.second.get());
}
