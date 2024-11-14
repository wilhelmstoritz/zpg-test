#pragma once

#include "Camera.h"
#include "ShaderFactory.h"
#include "ModelFactory.h"
#include "Model.h"

// include the standard C++ headers
#include <unordered_set>

class Scene {
public:
	Scene(Camera* t_camera);
	~Scene();

	void clearAllModels();

	void addModel(Model* t_model);

	void removeModel(Model* t_model);

	Camera* getCamera();
	Light* getLight(const std::string& t_name) const;
	ShaderFactory* getShaderFactory() const;
	ModelFactory* getModelFactory() const;
	const std::vector<Model*>& getModels() const;
	//const std::vector<Model*>* getModels() const;

	void addCamera(Camera* t_camera);
	void setAllCameras();

	void addLight(const std::string& t_name, Light* t_light);
	void setAllLights();

private:
	Camera* m_camera;
	std::unordered_map<std::string, Light*> m_lights;

	ShaderFactory* m_shaderFactory;
	ModelFactory* m_modelFactory;
	std::vector<Model*> m_models;

	void setCamera(Camera* t_camera);
	void setLight(Light* t_light);
};
