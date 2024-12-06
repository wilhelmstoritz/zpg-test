#pragma once

#include "Scene.h"
#include "SceneBuilderPlugin.h"

// include GLFW
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <unordered_map>
#include <mutex>

class SceneBuilder {
public:
	//~SceneBuilder() = default;
	~SceneBuilder();

	static SceneBuilder* getInstance();

	void setPlugin(SceneBuilderPlugin* t_sceneBuilderPlugin);
	Scene* createScene(GLFWwindow* t_window);

private:
	// private constructor to avoid creating multiple instances
	SceneBuilder();

	// disable copy constructor and assignment operator
	SceneBuilder(const SceneBuilder&) = delete;
	SceneBuilder& operator=(const SceneBuilder&) = delete;

	// a singleton instance pointer
	//static SceneBuilder* _instance;
	static std::unique_ptr<SceneBuilder> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;

	Scene* m_scene;
	SceneBuilderPlugin* m_sceneBuilderPlugin;
};
