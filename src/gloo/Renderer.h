#pragma once

#include "Model.h"
#include "Controller.h"

// include GLFW
#include <GLFW/glfw3.h>

// include the standard C++ headers
#include <vector>

class Renderer {
public:
	Renderer(GLFWwindow* t_window, std::vector<Model*>& models, Controller& t_controller);

	void renderLoop();

private:
	GLFWwindow* m_window;
	std::vector<Model*>& m_models;
	Controller& m_controller;

	// ffmpeg related
	int m_sizeX, m_sizeY;
	std::vector<uint8_t> m_pixels;
	FILE* m_ffmpeg;

	void preLoopProcessing();
	void onLoopProcessing();
	void postLoopProcessing();
};
