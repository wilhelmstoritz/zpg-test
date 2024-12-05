#pragma once

#include "ShaderFactory.h"
#include "ModelFactory.h"
#include "Scene.h"

// include GLFW
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <unordered_map>
#include <mutex>

class SceneBuilder {
public:
	~SceneBuilder() = default;

	static SceneBuilder* getInstance();

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
	ShaderFactory* m_shaderFactory;
	ModelFactory* m_modelFactory;

	std::string m_shaderResourcesPath;

	void createContext();
	void addContextToScene();

	// === shader factory ===========
	void createBasicShaders();
	void createShaders();

	void createTemporaryShaders();

	// === model factory ============
	void createModels_01();
	void createModels_02();
	void createScene_02_woods();
	void createScene_03_illuminatedSpheres();
	void createScene_04_magicWoods();

	void createTemporaryScene();
};
