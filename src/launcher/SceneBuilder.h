#pragma once

#include "ShaderFactory.h"
#include "ModelFactory.h"
#include "Scene.h"

// standard C++ libraries
#include <unordered_map>
#include <mutex>

class SceneBuilder {
public:
	~SceneBuilder() = default;

	static SceneBuilder* getInstance();

	Scene* createScene();

private:
	// private constructor to avoid creating multiple instances
	SceneBuilder() = default;

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

	glm::vec3 m_dimensions;

	void createContext();
	void addContextToScene();

	// === shader factory ===========
	void createDefaultShaders();
	void createTransformingShaders();

	// === model factory ============
	void createDefaultModels_01();
	void createDefaultModels_02();
	void createSceneForest(const glm::vec2 t_areaSize, const int t_numberOfTrees);
};
