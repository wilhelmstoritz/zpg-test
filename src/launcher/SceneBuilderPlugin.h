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

	virtual void createShaders() = 0;
	virtual void createLights();
	virtual void createModels();
	virtual void loadTextures();

	virtual void preProcess();
	virtual void postProcess();

	virtual void addContextToScene();
};
