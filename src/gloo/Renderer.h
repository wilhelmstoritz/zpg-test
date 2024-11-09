#pragma once

#include "Drawable.h"
#include "Model.h"
#include "Controller.h"

// include GLFW
#include <GLFW/glfw3.h>

// include the standard C++ headers
#include <vector>

class Renderer {
public:
	//Renderer(GLFWwindow* t_window, Controller* t_controller, const std::vector<Drawable*>& t_models);
	Renderer(GLFWwindow* t_window, Controller* t_controller, const std::vector<Model*>& t_models);

	void renderLoop();

private:
	GLFWwindow* m_window;
	Controller* m_controller;
	//const std::vector<Drawable*>& m_models;
	const std::vector<Model*>& m_models;

	// ffmpeg related
	int m_sizeX = 0, m_sizeY = 0;
	std::vector<uint8_t> m_pixels;
	FILE* m_ffmpeg = nullptr;

	void preLoopProcessing();
	void onLoopProcessing();
	void postLoopProcessing();
};
