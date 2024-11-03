#pragma once

#include "Camera.h"
#include "ModelVault.h"

// GLFW
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <mutex>

class Application {
public:
	~Application();

	static Application* getInstance();

	void run();
	//Camera* getCamera();

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

	std::vector<ModelVault::renderingDataT> m_renderingData;

	void init();
	void initWindow();
};
