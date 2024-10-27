#pragma once

#include "ZPGVAO.h"
#include "ZPGShaderProgram.h"

// GLFW
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <unordered_map>
#include <mutex>

class ModelVault {
public:
	struct renderingDataT {
		ZPGShaderProgram* shaderProgram;
		ZPGVAO* VAO;
		GLint first;
		GLsizei count;

		renderingDataT(ZPGShaderProgram* t_shaderProgram, ZPGVAO* t_VAO, GLint t_first, GLsizei t_count)
			: shaderProgram(t_shaderProgram), VAO(t_VAO), first(t_first), count(t_count) { }
	};

	~ModelVault();

	static ModelVault* getInstance();

	void addShader(const std::string t_name, ZPGShader* t_shader);
	void addShaderProgram(const std::string t_name, ZPGShaderProgram* t_shaderProgram);
	void addVBO(const std::string t_name, ZPGVBO* t_VBO);
	void addVAO(const std::string t_name, ZPGVAO* t_VAO);
	void addRenderingData(ZPGShaderProgram* t_shaderProgram, ZPGVAO* t_VAO, GLint t_first, GLsizei t_count);
	ZPGShader* getShader(const std::string t_name);
	ZPGShaderProgram* getShaderProgram(const std::string t_name);
	ZPGVBO* getVBO(const std::string t_name);
	ZPGVAO* getVAO(const std::string t_name);
	std::vector<ModelVault::renderingDataT>* getRenderingData();

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

	std::unordered_map<std::string, ZPGVBO*> m_VBOs;
	std::unordered_map<std::string, ZPGVAO*> m_VAOs;
	std::unordered_map<std::string, ZPGShader*> m_shaders;
	std::unordered_map<std::string, ZPGShaderProgram*> m_shaderPrograms;
	std::vector<renderingDataT> m_renderingData;

	void createShaders();
	void createModels();
	void createRenderingData();
};
