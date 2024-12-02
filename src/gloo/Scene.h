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
	
	void addCamera(Camera* t_camera);
	void addLight(Light* t_light);
	void addModel(const std::string& t_name, Model* t_model);

	void removeLight(const std::string& t_name);
	void removeModel(const std::string& t_name);
	void removeAllModels();

	ShaderFactory* getShaderFactory() const;
	ModelFactory* getModelFactory() const;
	
	Camera* getCamera();
	Light* getLight(const std::string& t_name) const;
	const std::unordered_map<std::string, Model*>& getModels() const;
	//const std::unordered_map<std::string, Model*>* getModels() const;

	void setAllCameras();
	void setAllLights();

	void callbackFramebufferSize(int t_width, int t_height);

private:
	ShaderFactory* m_shaderFactory;
	ModelFactory* m_modelFactory;

	Camera* m_camera;
	std::unordered_map<std::string, Light*> m_lights;
	std::vector<std::string> m_lightsOrder;
	std::unordered_map<std::string, size_t> m_lightsOrderIndex;
	std::unordered_map<std::string, Model*> m_models;

	void setCamera(Camera* t_camera);
	void setLight(Light* t_light);
};
