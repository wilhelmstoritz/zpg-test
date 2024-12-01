#pragma once

#include "Drawable.h"
#include "Model.h"
#include "Controller.h"
#include "Scene.h"
#include "DeltaTime.h"

// include GLFW
#include <GLFW/glfw3.h>

// include the standard C++ headers
#include <vector>

class Renderer {
public:
	Renderer(GLFWwindow* t_window, Controller* t_controller, const Scene& t_scene);

	void renderLoop();

private:
	GLFWwindow* m_window;
	Controller* m_controller;
	const Scene& m_scene;

	DeltaTime m_deltaTime;

	// ffmpeg related
	int m_sizeX = 0, m_sizeY = 0;
	std::vector<uint8_t> m_pixels;
	FILE* m_ffmpeg = nullptr;

	void preLoopProcessing();
	void onLoopProcessing();
	void postLoopProcessing();
};
