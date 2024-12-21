#pragma once

#include "Camera.h"
#include "Model.h"
#include "Config.h"

// include the standard C++ headers
#include <string>
#include <unordered_set>

class Scene {
public:
	const float m_xmin;
	const float m_xmax;
	const float m_ymin;
	const float m_ymax;
	const float m_zmin;
	const float m_zmax;

	const float m_xsize, m_ysize, m_zsize;
	const float m_xcenter, m_ycenter, m_zcenter;

	Scene(const std::string& t_name, Camera* t_camera,
		float t_xmin = Config::SKYBOX_XMIN,
		float t_xmax = Config::SKYBOX_XMAX,
		float t_ymin = Config::SKYBOX_YMIN_REALWORLDSCENE,
		float t_ymax = Config::SKYBOX_YMAX,
		float t_zmin = Config::SKYBOX_ZMIN,
		float t_zmax = Config::SKYBOX_ZMAX);
	Scene(Camera* t_camera,
		float t_xmin = Config::SKYBOX_XMIN,
		float t_xmax = Config::SKYBOX_XMAX,
		float t_ymin = Config::SKYBOX_YMIN_REALWORLDSCENE,
		float t_ymax = Config::SKYBOX_YMAX,
		float t_zmin = Config::SKYBOX_ZMIN,
		float t_zmax = Config::SKYBOX_ZMAX);
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

	void setCamera(Camera* t_camera);
	void setLight(Light* t_light);
};
