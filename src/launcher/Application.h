#pragma once

#include "ZPGVAO.h"
#include "ZPGShaderProgram.h"

// GLFW
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <unordered_map>
#include <mutex>

class Application {
public:
	~Application();

	static Application* getInstance();

	void addShader(const std::string t_name, ZPGShader* t_shader);
	void addShaderProgram(const std::string t_name, ZPGShaderProgram* t_shaderProgram);
	void addVBO(const std::string t_name, ZPGVBO* t_VBO);
	void addVAO(const std::string t_name, ZPGVAO* t_VAO);
	ZPGShader* getShader(const std::string t_name);
	ZPGShaderProgram* getShaderProgram(const std::string t_name);
	ZPGVBO* getVBO(const std::string t_name);
	ZPGVAO* getVAO(const std::string t_name);
	void addRenderingData(ZPGShaderProgram* t_shaderProgram, ZPGVAO* t_VAO, GLint t_first, GLsizei t_count);
	void createShaders();
	void createModels();
	void createRenderingData();
	void run();

private:
	struct renderingDataT {
		ZPGShaderProgram* shaderProgram;
		ZPGVAO* VAO;
		GLint first;
		GLsizei count;
		
		renderingDataT(ZPGShaderProgram* t_shaderProgram, ZPGVAO* t_VAO, GLint t_first, GLsizei t_count)
			: shaderProgram(t_shaderProgram), VAO(t_VAO), first(t_first), count(t_count) { }
	};

	// private constructor to avoid creating multiple instances
	Application();

	// disable copy constructor and assignment operator
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	// a singleton instance pointer
	//static Application* _instance;
	static std::unique_ptr<Application> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;

	GLFWwindow* m_window;

	std::unordered_map<std::string, ZPGVBO*> m_VBOs;
	std::unordered_map<std::string, ZPGVAO*> m_VAOs;
	std::unordered_map<std::string, ZPGShader*> m_shaders;
	std::unordered_map<std::string, ZPGShaderProgram*> m_shaderPrograms;
	std::vector<renderingDataT> m_renderingData;

	void init();
	void initWindow();
};
