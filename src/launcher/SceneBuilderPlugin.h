#pragma once

#include "Scene.h"
#include "ShaderFactory.h"
#include "ModelFactory.h"

class SceneBuilderPlugin {
public:
	void createContext(Scene* t_scene);

protected:
	std::string m_shaderResourcesPath;

	Scene* m_scene;
	ShaderFactory* m_shaderFactory;
	ModelFactory* m_modelFactory;

	virtual void createShaders() = 0;
	virtual void createLights();
	virtual void createModels();

	virtual void preProcess();
	virtual void postProcess();

	virtual void addContextToScene();
};
