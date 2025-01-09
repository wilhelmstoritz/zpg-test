#pragma once

#include "Scene.h"
#include "ShaderWarehouse.h"
#include "LightWarehouse.h"
#include "ModelWarehouse.h"
#include "TextureWarehouse.h"

class SceneBuilderPlugin {
public:
	SceneBuilderPlugin();
	virtual ~SceneBuilderPlugin() = default;

	virtual void setSceneProperties(Scene* t_scene); // i.e. scene title, etc.

	void createContext(Scene* t_scene);

protected:
	std::string m_windowTitle;

	std::string m_shaderResourcesPath;
	std::string m_textureResourcesPath;
	std::string m_modelResourcesPath;

	ShaderWarehouse* m_shaderWarehouse;
	LightWarehouse* m_lightWarehouse;
	ModelWarehouse* m_modelWarehouse;
	TextureWarehouse* m_textureWarehouse;

	Scene* m_scene;

	glm::vec3 m_min, m_max, m_size, m_center; // for simplified access

	virtual void setEnvironment(); // set the environment for the scene plugin; i.e. scene dimensions, center, etc.

	virtual void createShaders() = 0; // no default implementation; shaders must be created
	virtual void createLights();
	virtual void createModels()  = 0; // no default implementation; models must be created
	virtual void loadTextures();

	virtual void preProcess();
	virtual void postProcess();

	virtual void addContextToScene();
};
