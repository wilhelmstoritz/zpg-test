#pragma once

#include "Scene.h"
#include "SceneBuilderPlugin.h"

// standard c++ libraries
#include <mutex>
#include <memory>
#include <unordered_map>

class SceneBuilder {
public:
	static SceneBuilder* getInstance();
	~SceneBuilder() = default;

	template <typename T>
	T*     createScene(const std::string& t_name, SceneBuilderPlugin* t_sceneBuilderPlugin);
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
#include "SceneBuilder.tpp"
