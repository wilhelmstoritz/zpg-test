#pragma once

#include "Camera.h"
#include "Model.h"
#include "Config.h"

// include the standard C++ headers
#include <string>
#include <unordered_set>

class Scene {
public:
	float m_xmin = 1.f;
	float m_xmax = 1.f;
	float m_ymin = 1.f;
	float m_ymax = 1.f;
	float m_zmin = 1.f;
	float m_zmax = 1.f;

	float m_xsize = 0, m_ysize = 0, m_zsize = 0;
	float m_xcenter = 0, m_ycenter = 0, m_zcenter =0;

	Scene(const std::string& t_name, Camera* t_camera);
	Scene(Camera* t_camera);
	~Scene();
	
	void addCamera(Camera* t_camera);
	void addLight(const std::string& t_name, Light* t_light);
	void addModel(const std::string& t_name, Model* t_model);

	void removeLight(const std::string& t_name);
	void removeModel(const std::string& t_name);
	void removeAllModels();

	const std::string& getName() const;

	Camera* getCamera() const;
	Light* getLight(const std::string& t_name) const;
	const std::unordered_map<std::string, Model*>& getModels() const;
	//const std::unordered_map<std::string, Model*>* getModels() const;

	void setAllCameras();
	void setAllLights();

	void callbackWindowSize(int t_width, int t_height);

private:
	std::string m_name;

	Camera* m_camera;
	std::unordered_map<std::string, Light*> m_lights;
	std::vector<std::string> m_lightsOrder;
	std::unordered_map<std::string, size_t> m_lightsOrderIndex;
	std::unordered_map<std::string, Model*> m_models;

	glm::vec3 m_min; // minimum corner of the scene
	glm::vec3 m_max; // maximum corner of the scene
	glm::vec3 m_size; // size of the scene
	glm::vec3 m_center; // center of the scene

	void setCamera(Camera* t_camera);
	void setLight(Light* t_light);
};
