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
	//Renderer(GLFWwindow* t_window, Controller& t_controller, std::vector<Drawable*>& t_models);
	//Renderer(GLFWwindow* t_window, Controller* t_controller, std::vector<Drawable*>* t_models);
	Renderer(GLFWwindow* t_window, Controller* t_controller, std::vector<Model*>* t_models);

	void renderLoop();

private:
	GLFWwindow* m_window;
	//std::vector<Drawable*>* m_models;
	std::vector<Model*>* m_models;
	Controller* m_controller;

	// ffmpeg related
	int m_sizeX, m_sizeY;
	std::vector<uint8_t> m_pixels;
	FILE* m_ffmpeg;

	void preLoopProcessing();
	void onLoopProcessing();
	void postLoopProcessing();
};
