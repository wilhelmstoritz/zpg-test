#include "SceneBuilderPlugin.h"
#include "AppUtils.h"

// --- public ------------------------------------------------------------------
SceneBuilderPlugin::SceneBuilderPlugin() {
	this->m_shaderResourcesPath  = AppUtils::getInstance()->getResourcesPath() + "shaders.glsl/";
	this->m_textureResourcesPath = AppUtils::getInstance()->getResourcesPath() + "textures/";
	this->m_modelResourcesPath   = AppUtils::getInstance()->getResourcesPath() + "models.obj/";

	this->m_shaderWarehouse = ShaderWarehouse::getInstance(); // for simplified use
	this->m_lightWarehouse = LightWarehouse::getInstance();
	this->m_modelWarehouse = ModelWarehouse::getInstance();
	this->m_textureWarehouse = TextureWarehouse::getInstance();

	// to prevent visual studio warnings; value(s) will be set later
	this->m_scene = nullptr;

	this->m_xmin = this->y_min = this->z_min = 0.f;
	this->m_xmax = this->y_max = this->z_max = 0.f;
	this->m_xsize = this->y_size = this->z_size = 0.f;
	this->m_xcenter = this->y_center = this->z_center = 0.f;
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
	glm::vec3 data;
	data = this->m_scene->getMin();    this->m_xmin    = data.x; this->y_min    = data.y; this->z_min    = data.z;
	data = this->m_scene->getMax();    this->m_xmax    = data.x; this->y_max    = data.y; this->z_max    = data.z;
	data = this->m_scene->getSize();   this->m_xsize   = data.x; this->y_size   = data.y; this->z_size   = data.z;
	data = this->m_scene->getCenter(); this->m_xcenter = data.x; this->y_center = data.y; this->z_center = data.z;
}

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
