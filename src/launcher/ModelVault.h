#pragma once

#include "ShaderFactory.h"
#include "ModelFactory.h"

// standard C++ libraries
#include <unordered_map>
#include <mutex>

class ModelVault {
public:
	~ModelVault();

	static ModelVault* getInstance();
	static ModelVault* getInstance(Camera* t_camera);

	void setCamera(Camera* t_camera);
	const std::vector<Model*>& getModels() const;
	//const std::vector<Model*>* getModels() const;

private:
	// private constructor to avoid creating multiple instances
	ModelVault();

	// disable copy constructor and assignment operator
	ModelVault(const ModelVault&) = delete;
	ModelVault& operator=(const ModelVault&) = delete;

	// a singleton instance pointer
	//static ModelVault* _instance;
	static std::unique_ptr<ModelVault> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;

	ShaderFactory* m_shaderFactory;
	ModelFactory* m_modelFactory;
	std::vector<Model*> m_models;

	void createContext();

	// === shader factory ===========
	void createDefaultShaders();
	void createTransformingShaders();

	// === model factory ============
	void createDefaultModels();
	void createSceneForest(const float t_areaSize, const int t_numberOfTrees);
};
