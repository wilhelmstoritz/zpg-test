#pragma once

#include "Scene.h"
#include "ShaderWarehouse.h"
#include "ModelWarehouse.h"

class SceneBuilderPlugin {
public:
	void createContext(Scene* t_scene);

protected:
	std::string m_shaderResourcesPath;

	Scene* m_scene;
	ShaderWarehouse* m_shaderWarehouse;
	ModelWarehouse* m_modelWarehouse;

	virtual void createShaders() = 0;
	virtual void createLights();
	virtual void createModels();

	virtual void preProcess();
	virtual void postProcess();

	virtual void addContextToScene();
};
