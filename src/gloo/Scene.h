#pragma once

#include "Camera.h"
#include "Model.h"
#include "Config.h"

// glfw
#include <GLFW/glfw3.h>

// standard c++ libraries
#include <string>
#include <unordered_map>
#include <unordered_set>

class Scene {
public:
	Scene(const std::string& t_name, Camera* t_camera);
	Scene(Camera* t_camera);
	virtual ~Scene();
	
	void addCamera(Camera* t_camera);
	void addLight(const std::string& t_name, Light* t_light);
	void addModel(const std::string& t_name, Model* t_model);

	void removeLight(const std::string& t_name);
	void removeModel(const std::string& t_name);
	void removeAllModels();

	const std::string getName() const;
	const std::string getTitle() const;

	glm::vec3 getMin() const;
	glm::vec3 getMax() const;
	glm::vec3 getSize() const;
	glm::vec3 getCenter() const;

	Camera* getCamera() const;
	Light* getLight(const std::string& t_name) const;
	Model* getModel(const std::string& t_name) const;
	const std::unordered_map<std::string, Model*>& getModels() const;
	//const std::unordered_map<std::string, Model*>* getModels() const;

	void setTitle(const std::string& t_title);

	void setSize(const glm::vec3& t_min, const glm::vec3& t_max);

	void setAllCameras();
	void setAllLights();

	void callbackWindowSize(int t_width, int t_height);
	virtual void callbackKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods);

protected:
	std::string m_name;
	std::string m_title;

	glm::vec3 m_min; // minimum corner of the scene
	glm::vec3 m_max; // maximum corner of the scene
	glm::vec3 m_size; // size of the scene
	glm::vec3 m_center; // center of the scene

	Camera* m_camera;
	std::unordered_map<std::string, Light*> m_lights;
	std::vector<std::string> m_lightsOrder;
	std::unordered_map<std::string, size_t> m_lightsOrderIndex;
	std::unordered_map<std::string, Model*> m_models;

	void setCamera(Camera* t_camera);
	void setLight(Light* t_light);
};
