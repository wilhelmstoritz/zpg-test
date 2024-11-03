#pragma once

#include "VAO.h"
#include "ShaderProgram.h"

// GLFW
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <unordered_map>
#include <mutex>

class ModelVault {
public:
	struct renderingDataT {
		ShaderProgram* shaderProgram;
		VAO* vao;
		GLint first;
		GLsizei count;

		renderingDataT(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
			: shaderProgram(t_shaderProgram), vao(t_vao), first(t_first), count(t_count) { }
	};

	~ModelVault();

	static ModelVault* getInstance();

	void addShader(const std::string t_name, Shader* t_shader);
	void addShaderProgram(const std::string t_name, ShaderProgram* t_shaderProgram);
	void addVBO(const std::string t_name, VBO* t_vbo);
	void addVAO(const std::string t_name, VAO* t_vao);
	void addRenderingData(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count);
	Shader* getShader(const std::string t_name);
	ShaderProgram* getShaderProgram(const std::string t_name);
	VBO* getVBO(const std::string t_name);
	VAO* getVAO(const std::string t_name);
	std::vector<ModelVault::renderingDataT>* getRenderingData();

	/*
	void addVertexShader(const std::string t_name, const char* t_source);
	void addFragmentShader(const std::string t_name, const char* t_source);
	*/

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

	std::unordered_map<std::string, VBO*> m_vbos;
	std::unordered_map<std::string, VAO*> m_vaos;
	std::unordered_map<std::string, Shader*> m_shaders;
	std::unordered_map<std::string, ShaderProgram*> m_shaderPrograms;
	std::vector<renderingDataT> m_renderingData;

	void createShaders();
	void createModels();
	void createRenderingData();

	void createSceneMagicForest(int t_numberOfTrees, float t_areaSize);
};
