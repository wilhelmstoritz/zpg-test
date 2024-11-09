#pragma once

#include "Camera.h"
#include "ShaderFactory.h"
#include "ModelFactory.h"
#include "Model.h"

class Scene {
public:
	Scene(Camera* t_camera);
	~Scene();

	void clearAllModels();

	void addModel(Model* t_model);

	void removeModel(Model* t_model);

	Camera* getCamera();
	ShaderFactory* getShaderFactory() const;
	ModelFactory* getModelFactory() const;
	const std::vector<Model*>& getModels() const;
	//const std::vector<Model*>* getModels() const;

	void setCamera();
	void setCamera(Camera* t_camera);

private:
	Camera* m_camera;

	ShaderFactory* m_shaderFactory;
	ModelFactory* m_modelFactory;
	std::vector<Model*> m_models;
};
