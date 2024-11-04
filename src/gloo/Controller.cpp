#include "Controller.h"

// --- public ------------------------------------------------------------------
Controller::Controller(GLFWwindow* t_window, Camera* t_camera)
	: m_window(t_window), m_camera(t_camera) {
	int width, height;
	glfwGetWindowSize(t_window, &width, &height);

	this->m_centerX = width / 2.0;
	this->m_centerY = height / 2.0;

	glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide the cursor and lock it in the window
	glfwSetCursorPos(this->m_window, this->m_centerX, this->m_centerY); // set the cursor to the center of the window
}

Controller::Controller(GLFWwindow* t_window)
	: Controller(t_window, nullptr) { }

/*
void Controller::registerCamera(Camera* t_camera) {
	this->m_camera = t_camera;
}
*/

void Controller::processInput() {
	// keyboard controls
	if (glfwGetKey(this->m_window, GLFW_KEY_UP)    == GLFW_PRESS) { this->m_camera->moveCamera(.1f); }
	if (glfwGetKey(this->m_window, GLFW_KEY_DOWN)  == GLFW_PRESS) { this->m_camera->moveCamera(-.1f); }
	if (glfwGetKey(this->m_window, GLFW_KEY_RIGHT) == GLFW_PRESS) { this->m_camera->strafeCamera(.1f, 0.f); }
	if (glfwGetKey(this->m_window, GLFW_KEY_LEFT)  == GLFW_PRESS) { this->m_camera->strafeCamera(-.1f, 0.f); }

	// mouse control
	double xpos, ypos;
	glfwGetCursorPos(this->m_window, &xpos, &ypos); // get the current position of the mouse cursor

	// calculate deltaX and deltaY relative to the center of the window
	double deltaX = xpos - this->m_centerX;
	double deltaY = ypos - this->m_centerY;

	if (deltaX != 0.0 || deltaY != 0.0) {
		if (glfwGetMouseButton(this->m_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
			this->m_camera->strafeCamera(static_cast<float>(deltaX / 20), static_cast<float>(-deltaY / 20));
		} else {
			this->m_camera->rotateCamera(static_cast<float>(-deltaX / 20), static_cast<float>(-deltaY / 20));
		}

		glfwSetCursorPos(this->m_window, this->m_centerX, this->m_centerY); // reset the cursor to the center of the window
	}
}

// --- private -----------------------------------------------------------------
