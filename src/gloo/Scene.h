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

	void addModel(Model* t_model);
	void addCamera(Camera* t_camera);
	void addLight(const std::string& t_name, Light* t_light);

	void removeModel(Model* t_model);
	void removeLight(const std::string& t_name);
	void removeAllModels();
	//void removeAllLights();

	ShaderFactory* getShaderFactory() const;
	ModelFactory* getModelFactory() const;
	const std::vector<Model*>& getModels() const;
	//const std::vector<Model*>* getModels() const;
	Camera* getCamera();
	Light* getLight(const std::string& t_name) const;

	void setAllCameras();
	void setAllLights();

private:
	ShaderFactory* m_shaderFactory;
	ModelFactory* m_modelFactory;

	std::vector<Model*> m_models;
	Camera* m_camera;
	std::unordered_map<std::string, Light*> m_lights;

	void setCamera(Camera* t_camera);
	void setLight(Light* t_light);
};
