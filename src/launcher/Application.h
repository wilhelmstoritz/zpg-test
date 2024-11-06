#pragma once

// include GLEW
#include <GL/glew.h>
// include GLFW
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <mutex>

#include "ModelVaultOBSOLETE.h"
#include "Camera.h"
#include "ObserverSubject.h"
#include "Controller.h"
#include "Renderer.h"

class Application {
public:
	~Application();

	static Application* getInstance();

	void run();

private:
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
	Camera* m_camera;
	Controller* m_controller;
	Renderer* m_renderer;

	std::vector<Model*>* m_models;

	void initWindow();
	void versionInfo();
};
