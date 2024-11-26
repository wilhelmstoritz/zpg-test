#include "Controller.h"
#include "Config.h"

// --- public ------------------------------------------------------------------
Controller::Controller(GLFWwindow* t_window, Camera* t_camera)
	: m_window(t_window), m_camera(t_camera) {
	int width, height;
	glfwGetWindowSize(t_window, &width, &height);

	this->m_centerX = width / 2.;
	this->m_centerY = height / 2.;

	glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide the cursor and lock it in the window
	this->resetCursor(); // set the cursor to the center of the window
}

/*
Controller::Controller(GLFWwindow* t_window)
	: Controller(t_window, nullptr) { }
*/

/*
void Controller::registerCamera(Camera* t_camera) {
	this->m_camera = t_camera;
}
*/

void Controller::processInput() {
	this->m_deltaTime.update();
	float delta = this->m_deltaTime.getDeltaSeconds();

	// keyboard controls
	float distance = Config::MOVEMENT_SPEED_WALK * delta;
	if (glfwGetKey(this->m_window, GLFW_KEY_LEFT_SHIFT)  == GLFW_PRESS ||
		glfwGetKey(this->m_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) { distance = Config::MOVEMENT_SPEED_RUN * delta; }

	if (glfwGetKey(this->m_window, GLFW_KEY_UP)    == GLFW_PRESS) { this->m_camera->moveCamera(distance); }
	if (glfwGetKey(this->m_window, GLFW_KEY_DOWN)  == GLFW_PRESS) { this->m_camera->moveCamera(-distance); }
	if (glfwGetKey(this->m_window, GLFW_KEY_RIGHT) == GLFW_PRESS) { this->m_camera->strafeCamera(distance, 0.f); }
	if (glfwGetKey(this->m_window, GLFW_KEY_LEFT)  == GLFW_PRESS) { this->m_camera->strafeCamera(-distance, 0.f); }

	// mouse control
	double xpos, ypos;
	glfwGetCursorPos(this->m_window, &xpos, &ypos); // get the current position of the mouse cursor

	// calculate deltaX and deltaY relative to the center of the window
	double deltaX = xpos - this->m_centerX;
	double deltaY = ypos - this->m_centerY;

	if (deltaX != 0.0 || deltaY != 0.0) {
		if (glfwGetMouseButton(this->m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			this->m_camera->strafeCamera(
				static_cast<float>(deltaX * Config::MOUSE_SENSITIVITY),
				static_cast<float>(-deltaY * Config::MOUSE_SENSITIVITY));
		} else {
			this->m_camera->rotateCamera(
				static_cast<float>(-deltaX * Config::MOUSE_SENSITIVITY),
				static_cast<float>(-deltaY * Config::MOUSE_SENSITIVITY));
		}

		this->resetCursor(); // reset the cursor to the center of the window
	}
}

void Controller::resetCursor() {
	glfwSetCursorPos(this->m_window, this->m_centerX, this->m_centerY); // reset the cursor to the center of the window
}

// --- private -----------------------------------------------------------------
bool Controller::isInsideSkybox(const glm::vec3 t_position) {
	return !Config::STAY_INSIDE_SKYBOX || (
		t_position.x >= Config::SKYBOX_XMIN + 1                     && t_position.x <= Config::SKYBOX_XMAX - 1 &&
		t_position.y >= Config::SKYBOX_YMIN + Config::PLAYER_HEIGHT && t_position.y <= Config::SKYBOX_YMAX - 1 &&
		t_position.z >= Config::SKYBOX_ZMIN + 1                     && t_position.z <= Config::SKYBOX_ZMAX - 1);
}
