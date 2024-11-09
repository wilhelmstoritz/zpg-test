#pragma once

#include "VAO.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Model.h"
#include "ObserverSubject.h"

// GLFW
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <unordered_map>
#include <mutex>

class ModelVaultOBSOLETE {
public:
	~ModelVaultOBSOLETE();

	static ModelVaultOBSOLETE* getInstance();

	void addShader(const std::string t_name, Shader* t_shader);
	void addShaderProgram(const std::string t_name, ShaderProgram* t_shaderProgram);
	void addVBO(const std::string t_name, VBO* t_vbo);
	void addVAO(const std::string t_name, VAO* t_vao);
	void addModel(Model* t_model);
	void addModel(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count);
	Shader* getShader(const std::string t_name);
	ShaderProgram* getShaderProgram(const std::string t_name);
	VBO* getVBO(const std::string t_name);
	VAO* getVAO(const std::string t_name);
	std::vector<Model*>& getModels(Camera* t_camera);
	//std::vector<Model*>* getModels(Camera* t_camera);

	/*
	void addVertexShader(const std::string t_name, const char* t_source);
	void addFragmentShader(const std::string t_name, const char* t_source);
	*/

private:
	// private constructor to avoid creating multiple instances
	ModelVaultOBSOLETE();

	// disable copy constructor and assignment operator
	ModelVaultOBSOLETE(const ModelVaultOBSOLETE&) = delete;
	ModelVaultOBSOLETE& operator=(const ModelVaultOBSOLETE&) = delete;

	// a singleton instance pointer
	//static ModelVault* _instance;
	static std::unique_ptr<ModelVaultOBSOLETE> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;

	std::unordered_map<std::string, VBO*> m_vbos;
	std::unordered_map<std::string, VAO*> m_vaos;
	std::unordered_map<std::string, Shader*> m_shaders;
	std::unordered_map<std::string, ShaderProgram*> m_shaderPrograms;
	std::vector<Model*> m_models;

	void createShaders();
	void createModels();

	void createScene();
	void createSceneMagicForest(int t_numberOfTrees, float t_areaSize);
};
