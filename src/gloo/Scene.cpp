#include "Scene.h"
#include "ShaderWarehouse.h"

// glfw
#include <GLFW/glfw3.h>

// --- public ------------------------------------------------------------------
Scene::Scene(const std::string& t_name, Camera* t_camera)
	: m_name(t_name) {
	//this->m_title = "@!#?@!";
	this->m_title = Config::WINDOW_TITLE
		+ Config::WINDOW_TITLE_HELP
		+ Config::WINDOW_TITLE_HELP_MOVE; // default scene title; most common title; can/should be changed via setTitle()

	this->setSize( // default scene size
		Config::SKYBOX_MIN_REALWORLD,
		Config::SKYBOX_MAX);

	this->addCamera(t_camera); // !!! CONSIDER REMOVING FROM CONSTRUCTOR; JUST VIA ADDCAMERA() !!!
}

Scene::Scene(Camera* t_camera)
	: Scene("@!#?@!", t_camera) { }

Scene::~Scene() {
	// cleanup
	delete this->m_camera;
}

void Scene::addCamera(Camera* t_camera) {
	//printf("[scene] add camera : name '%s'\n", t_camera->getName().c_str());

	this->m_camera = t_camera;
	this->setCamera(t_camera); // cameras are set once at scene creation; ??? consider removing: then extra added camera(s) will not be observed by shaders automatically, should be set manually by calling setCamera()
}

void Scene::addLight(const std::string& t_name, Light* t_light) {
	//printf("[scene] add light : name '%s'\n", name.c_str());

	if (this->m_lights.find(t_name) == this->m_lights.end()) { // if light does not exist
		this->m_lightsOrder.push_back(t_name);
		this->m_lightsOrderIndex[t_name] = this->m_lightsOrder.size() - 1;
	}
	this->m_lights[t_name] = t_light;

	t_light->setID(this->m_lightsOrderIndex[t_name]);
	t_light->setNumLights(this->m_lightsOrder.size());

	this->setLight(t_light); // lights are set once at scene creation; ??? consider removing: then extra added light(s) will not be observed by shaders automatically, should be set manually by calling setLight()
}

void Scene::addModel(const std::string& t_name, Model* t_model) {
	//printf("[scene] add model : name '%s'\n", t_name.c_str());

	this->m_models[t_name] = t_model;
}

void Scene::removeLight(const std::string& t_name) {
	//printf("[scene] remove light : name %s\n", t_name.c_str());

	auto it = this->m_lights.find(t_name);
	if (it == this->m_lights.end()) {
		printf("error [scene] remove light : name %s; light not found\n", t_name.c_str());
		return;
	}

	// delete light and remove its reference from list
	delete this->m_lights.find(t_name)->second;

	//this->m_lights.erase(t_name);
	this->m_lights.erase(it);

	// remove light from order / order index lists
	auto itOrder = std::find(this->m_lightsOrder.begin(), this->m_lightsOrder.end(), t_name);
	if (itOrder != this->m_lightsOrder.end()) {
		this->m_lightsOrder.erase(itOrder);
		this->m_lightsOrderIndex.erase(t_name);
	}

	// recalculate order index to match the current order; update ID/numLights lights data
	size_t numLights = this->m_lightsOrder.size();

	for (size_t i = 0; i < numLights; ++i) {
		this->m_lightsOrderIndex[this->m_lightsOrder[i]] = i;

		Light* light = this->m_lights[this->m_lightsOrder[i]];
		light->setID(i);
		light->setNumLights(numLights);

		//this->setLight(light); // !!! CONSIDER REMOVING; LIGHTS ARE SET ONCE !!!
	}
}

void Scene::removeModel(const std::string& t_name) {
	//printf("[scene] remove model : name %s\n", t_name.c_str());

	auto it = this->m_models.find(t_name);
	if (it == this->m_models.end()) {
		printf("error [scene] remove model : name %s; model not found\n", t_name.c_str());
		return;
	}

	// delete model reference from list
	//this->m_models.erase(t_name);
	this->m_models.erase(it);
}

void Scene::removeAllModels() {
	this->m_models.clear();
}

const std::string Scene::getName()  const { return this->m_name; }
const std::string Scene::getTitle() const { return this->m_title; }

glm::vec3 Scene::getMin()    const { return this->m_min; }
glm::vec3 Scene::getMax()    const { return this->m_max; }
glm::vec3 Scene::getSize()   const { return this->m_size; }
glm::vec3 Scene::getCenter() const { return this->m_center; }

Camera* Scene::getCamera() const {
	return this->m_camera;
}

Light* Scene::getLight(const std::string& t_name) const {
	auto it = this->m_lights.find(t_name);
	return (it != this->m_lights.end()) ? it->second : nullptr;
}

Model* Scene::getModel(const std::string& t_name) const {
	auto it = this->m_models.find(t_name);
	return (it != this->m_models.end()) ? it->second : nullptr;
}

const std::unordered_map<std::string, Model*>& Scene::getModels() const {
	return this->m_models;
}

/*
const std::unordered_map<std::string, Model*>* Scene::getModels() const {
	return &this->m_models;
}
*/

void Scene::setTitle(const std::string& t_title) {
	this->m_title = t_title;
}

void Scene::setSize(const glm::vec3& t_min, const glm::vec3& t_max) {
	this->m_min = t_min;
	this->m_max = t_max;

	this->m_size = this->m_max - this->m_min;
	this->m_center = (this->m_min + this->m_max) / 2.f;
}

void Scene::setAllCameras() {
	this->setCamera(this->m_camera);
}

void Scene::setAllLights() {
	if (this->m_lights.empty())
		return;

	// set the number of lights; shared by all lights
	// get the first light name; at least one light must exist at this point
	this->m_lights[this->m_lightsOrder[0]]->setNumLights(this->m_lightsOrder.size());

	for (const auto& pair : this->m_lights)
		this->setLight(pair.second);
}

void Scene::callbackWindowSize(int t_width, int t_height) {
	//printf("[scene] callback window size : width %d, height %d\n", t_width, t_height);

	// update camera projection matrix
	this->m_camera->setProjection(Config::CAMERA_FOV, static_cast<float>(t_width) / static_cast<float>(t_height), Config::CAMERA_NEAR, Config::CAMERA_FAR);
}

void Scene::callbackKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) {
	//printf("[scene] callback key : key %d, scancode %d, action %d, mods %d\n", t_key, t_scancode, t_action, t_mods);
}

// --- protected ---------------------------------------------------------------
void Scene::setCamera(Camera* t_camera) {
	//printf("[scene] set camera : name '%s'\n", t_camera->getName().c_str());

	//t_camera->removeAllObservers(); // !!! CONSIDER REMOVING; OBSERVERS ARE/CAN BE SET NOT ONLY FROM HERE !!!

	// add camera as observer subject to all shader programs
	for (const auto& pair : this->m_models)
		t_camera->addObserver(pair.second->getShaderProgram()); // will not be added twice if already added
}

void Scene::setLight(Light* t_light) {
	//printf("[scene] set light : name '%s'\n", t_light->getName().c_str());

	//t_light->removeAllObservers(); // !!! CONSIDER REMOVING; OBSERVERS ARE/CAN BE SET NOT ONLY FROM HERE !!!

	// add light as observer subject to all shader programs
	for (const auto& pair : this->m_models)
		t_light->addObserver(pair.second->getShaderProgram()); // will not be added twice if already added
}
