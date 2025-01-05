#pragma once

#include "Scene.h"
#include "SceneBuilderPlugin.h"

// standard C++ libraries
#include <mutex>
#include <memory>
#include <unordered_map>

class SceneBuilder {
public:
	static SceneBuilder* getInstance();
	~SceneBuilder() = default;

	template <typename T>
	Scene* createScene(const std::string& t_name, SceneBuilderPlugin* t_sceneBuilderPlugin);

private:
	// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - -
	// private constructor to avoid creating multiple instances
	SceneBuilder() = default;

	// disable copy constructor and assignment operator
	SceneBuilder(const SceneBuilder&) = delete;
	SceneBuilder& operator=(const SceneBuilder&) = delete;

	// a singleton instance pointer
	//static SceneBuilder* _instance;
	static std::unique_ptr<SceneBuilder> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
};

// === template implementation =================================================
// --- public ------------------------------------------------------------------
template <typename T>
Scene* SceneBuilder::createScene(const std::string& t_name, SceneBuilderPlugin* t_sceneBuilderPlugin) {
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene"); // check if T is derived from Scene; if not, the compilation will fail

	// new empty scene
	Scene* scene = new T(t_name, new Camera("default",
		glm::vec3(0.f, 0.f, 1.f),    // eye
		glm::vec3(0.f, 0.f, -1.f))); // direction

	// fill the scene and bring it to life
	t_sceneBuilderPlugin->createContext(scene);
	scene->setAllCameras();
	scene->setAllLights();

	// cleanup
	delete t_sceneBuilderPlugin;

	return scene;
}
