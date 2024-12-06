#include "SceneBuilderPlugin.h"
#include "AppUtils.h"

// --- public ------------------------------------------------------------------
void SceneBuilderPlugin::createContext(Scene* t_scene) {
	this->m_shaderResourcesPath = AppUtils::getInstance()->getResourcesPath() + "shaders.glsl/";

	this->m_scene = t_scene;
	this->m_shaderFactory = this->m_scene->getShaderFactory(); // for simplified use
	this->m_modelFactory = this->m_scene->getModelFactory();

	// fill the scene and bring it to life
	this->createShaders();
	this->createModels();

	this->addContextToScene();
}
