#pragma once

#include "Drawable.h"
#include "Model.h"
#include "Controller.h"
#include "Scene.h"
#include "DeltaTime.h"

// glfw
#include <GLFW/glfw3.h>

// standard c++ libraries
#include <vector>

class Renderer {
public:
	Renderer(GLFWwindow* t_window, Controller* t_controller);

	void setScene(Scene* t_scene);

	void renderLoop();

private:
	GLFWwindow* m_window;

	Controller* m_controller;
	Scene* m_scene;

	DeltaTime m_deltaTime;

	// related to video capturing
	int m_captureXsize = 0, m_captureYsize = 0;
	std::vector<uint8_t> m_capturePixels;
	FILE* m_capturePipe = nullptr;

	void preLoopProcessing();
	void onLoopProcessing();
	void postLoopProcessing();
};
