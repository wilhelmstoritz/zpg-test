#pragma once

#include "Camera.h"

// include GLFW
#include <GLFW/glfw3.h>

class Controller {
public:
	Controller(GLFWwindow* t_window, Camera* t_camera);
	//Controller(GLFWwindow* t_window);

	//void registerCamera(Camera* t_camera);
	void processInput();
	void resetCursor();

private:
	GLFWwindow* m_window;
	Camera* m_camera;
	double m_centerX, m_centerY;
};
