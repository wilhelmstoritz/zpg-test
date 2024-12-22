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
	std::string m_shaderResourcesPath;
	std::string m_textureResourcesPath;
	std::string m_modelResourcesPath;

	ShaderWarehouse* m_shaderWarehouse;
	LightWarehouse* m_lightWarehouse;
	ModelWarehouse* m_modelWarehouse;
	TextureWarehouse* m_textureWarehouse;

	Scene* m_scene;
	float m_xmin, y_min, z_min;
	float m_xmax, y_max, z_max;
	float m_xsize, y_size, z_size;
	float m_xcenter, y_center, z_center;

	virtual void createShaders() = 0;
	virtual void createLights();
	virtual void createModels();
	virtual void loadTextures();

	virtual void preProcess();
	virtual void postProcess();

	virtual void addContextToScene();
};
