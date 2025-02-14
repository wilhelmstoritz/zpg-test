#include "Controller.h"
#include "Config.h"

// --- public ------------------------------------------------------------------
Controller::Controller(GLFWwindow* t_window)
	: m_window(t_window) {
	/* glfwGetPlatform() is available in GLFW 3.3 and newer; not commonly included in today's linux distributions; use getenv() variant instead
	this->m_platform = static_cast<platformE>(glfwGetPlatform()); // get the platform; windows, x11, etc.*/

	this->m_platform = platformE::PLATFORM_NULL;
	// . . win32/64 platform . . . . . . . . . . . . . . . . . . . . . . . . . .
	#ifdef _WIN32
	this->m_platform = platformE::PLATFORM_WINDOWS;
	// . . apple (macos) platform  . . . . . . . . . . . . . . . . . . . . . . .
	#elif defined(__APPLE__)
	this->m_platform = platformE::PLATFORM_COCOA;
	// . . linux platform  . . . . . . . . . . . . . . . . . . . . . . . . . . .
	#elif defined(__linux__)
	if      (secure_getenv("XDG_SESSION_TYPE") && strcmp(secure_getenv("XDG_SESSION_TYPE"), "wayland") == 0) // secure_getenv() is a safer version of getenv()
		this->m_platform = platformE::PLATFORM_WAYLAND;
	else if (secure_getenv("XDG_SESSION_TYPE") && strcmp(secure_getenv("XDG_SESSION_TYPE"), "x11")     == 0)
		this->m_platform = platformE::PLATFORM_X11;
	#endif
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	this->m_rawMouse = false;

	// platform specific settings:
	//  windows - works as expected; no restrictions
	//  cocoa   - not tested; so cross fingers and good luck!
	//  wayland - platform not supported at all
	//  x11     - glfwSetInputMode(GLFW_CURSOR_DISABLED) and glfwSetCursorPos() behaves strangely and creepy under modern x11
	//            so raw mouse motion not supported; normal mouse motion but relative to the window/screen only restrictions apply
	switch (this->m_platform) {
	case platformE::PLATFORM_X11: // x11 special handling
		glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); // at least hide the cursor when inside the window

		this->m_rawMouse = true; // treat x11 mouse motion as raw mouse motion; no glfwSetCursorPos() calls
		break;

	default: // default handling; windows, cocoa, ...
		glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // disable (and hide) the cursor and lock it in the window

		if (glfwRawMouseMotionSupported()) {
			glfwSetInputMode(this->m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE); // enable raw mouse motion (if supported); no acceleration, no filtering, no cursor recentering

			this->m_rawMouse = true;
		}
		break;
	}
	
	this->updateCursor(); // initial cursor position

	// to prevent visual studio warnings; value(s) will be set later
	this->m_scene = nullptr;

	this->m_min = this->m_max = glm::vec3(0.f);
	this->m_camera = nullptr;
}

void Controller::setScene(Scene* t_scene) {
	this->m_scene = t_scene;

	// for simplified access
	this->m_min = this->m_scene->getMin();
	this->m_max = this->m_scene->getMax();

	this->m_camera = this->m_scene->getCamera();
}

void Controller::processInput() {
	this->m_deltaTime.update();
	float delta = this->m_deltaTime.getDeltaSeconds();

	// keyboard controls
	float distance = Config::MOVEMENT_SPEED_WALK * delta;
	if (glfwGetKey(this->m_window, GLFW_KEY_LEFT_SHIFT)  == GLFW_PRESS ||
		glfwGetKey(this->m_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) { distance = Config::MOVEMENT_SPEED_RUN * delta; }

	if (glfwGetKey(this->m_window, GLFW_KEY_UP)    == GLFW_PRESS) {
		this->m_camera->setPosition(
			this->getDestination(
				this->m_camera->getMoveDestination(
					std::min(
						distance,
						this->distanceToSkybox( // distance to skybox; forward
							this->m_camera->getEye(),
							this->m_camera->getDirection())))),
			this->m_camera->getDirection());
	}
	if (glfwGetKey(this->m_window, GLFW_KEY_DOWN)  == GLFW_PRESS) {
		this->m_camera->setPosition(
			this->getDestination(
				this->m_camera->getMoveDestination(
					-std::min(
						distance,
						this->distanceToSkybox( // distance to skybox; backward
							this->m_camera->getEye(),
							-this->m_camera->getDirection())))),
			this->m_camera->getDirection());
	}
	if (glfwGetKey(this->m_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		this->m_camera->setPosition(
			this->getDestination(
				this->m_camera->getStrafeDestination(
					std::min(
						distance,
						this->distanceToSkybox( // distance to skybox; right
							this->m_camera->getEye(),
							glm::cross( // the vector right perpendicular to direction and up vectors
								this->m_camera->getDirection(),
								this->m_camera->getUp()))),
					0.f)),
			this->m_camera->getDirection());
	}
	if (glfwGetKey(this->m_window, GLFW_KEY_LEFT)  == GLFW_PRESS) {
		this->m_camera->setPosition(
			this->getDestination(
				this->m_camera->getStrafeDestination(
					-std::min(
						distance,
						this->distanceToSkybox( // distance to skybox; left
							this->m_camera->getEye(),
							-glm::cross( // the vector left perpendicular to direction and up vectors
								this->m_camera->getDirection(),
								this->m_camera->getUp()))),
					0.f)),
			this->m_camera->getDirection());
	}

	// mouse control
	double xpos, ypos; // x, y position of the mouse cursor; absolute when using raw mouse motion; relative to the to the 'reset point' (top-left corner 0, 0) of the window when using normal mouse motion
	glfwGetCursorPos(this->m_window, &xpos, &ypos); // get the current position of the mouse cursor

	double deltaX = xpos - this->m_lastX; // universal code; supports both raw mouse motion and normal mouse motion...
	double deltaY = ypos - this->m_lastY; // ... due to different/lack of raw mouse motion support under x11
	this->m_lastX = xpos;
	this->m_lastY = ypos;

	if (deltaX != 0.0 || deltaY != 0.0) {
		if (glfwGetMouseButton(this->m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			this->m_camera->setPosition(
				this->getDestination(
					this->m_camera->getStrafeDestination(
						static_cast<float>( deltaX * Config::MOUSE_SENSITIVITY),
						static_cast<float>(-deltaY * Config::MOUSE_SENSITIVITY))),
				this->m_camera->getDirection());
		} else {
			this->m_camera->rotateCamera(
				static_cast<float>(-deltaX * Config::MOUSE_SENSITIVITY),
				static_cast<float>(-deltaY * Config::MOUSE_SENSITIVITY));
		}

		if (!this->m_rawMouse) // only if not using raw mouse motion
			this->resetCursor(); // set the cursor to the 'reset point' of the window
	}
}

void Controller::updateCursor() {
	if (this->m_rawMouse)
		glfwGetCursorPos(this->m_window, &this->m_lastX, &this->m_lastY); // get the current position of the mouse cursor
	else
		this->resetCursor(); // set the cursor to the 'reset point' of the window
}

// --- private -----------------------------------------------------------------
void Controller::resetCursor() {
	glfwSetCursorPos(this->m_window, 0.0, 0.0); // set the cursor to the 'reset point' (top-left corner 0, 0) of the window
	
	this->m_lastX = 0.0; // last position is the 'reset point' now (delta x, delta y)
	this->m_lastY = 0.0;
}

glm::vec3 Controller::getDestination(const glm::vec3& t_cameraDestination) {
	if (!Config::STAY_INSIDE_SKYBOX)
		return t_cameraDestination;

	glm::vec3 destination = t_cameraDestination;

	if (destination.x < this->m_min.x + Config::STAY_INSIDE_SKYBOX_BORDER) destination.x = this->m_min.x + Config::STAY_INSIDE_SKYBOX_BORDER;
	if (destination.x > this->m_max.x - Config::STAY_INSIDE_SKYBOX_BORDER) destination.x = this->m_max.x - Config::STAY_INSIDE_SKYBOX_BORDER;
	if (destination.y < this->m_min.y + Config::CAMERA_HEIGHT)             destination.y = this->m_min.y + Config::CAMERA_HEIGHT;
	if (destination.y > this->m_max.y - Config::STAY_INSIDE_SKYBOX_BORDER) destination.y = this->m_max.y - Config::STAY_INSIDE_SKYBOX_BORDER;
	if (destination.z < this->m_min.z + Config::STAY_INSIDE_SKYBOX_BORDER) destination.z = this->m_min.z + Config::STAY_INSIDE_SKYBOX_BORDER;
	if (destination.z > this->m_max.z - Config::STAY_INSIDE_SKYBOX_BORDER) destination.z = this->m_max.z - Config::STAY_INSIDE_SKYBOX_BORDER;

	return destination;
}

float Controller::distanceToSkybox(const glm::vec3& t_position, const glm::vec3& t_direction) {
	if (!Config::STAY_INSIDE_SKYBOX)
		return std::numeric_limits<float>::infinity();

	glm::vec3 direction = glm::normalize(t_direction);

	// calculate the distance to each (relevant) plane of the skybox
	float distances[6] = { std::numeric_limits<float>::infinity() };
	
	if (direction.x != 0) {
		distances[0] = this->distanceToPlane(this->m_min.x + Config::STAY_INSIDE_SKYBOX_BORDER - Config::STAY_INSIDE_SKYBOX_EPSILON, t_position.x, direction.x);
		distances[1] = this->distanceToPlane(this->m_max.x - Config::STAY_INSIDE_SKYBOX_BORDER + Config::STAY_INSIDE_SKYBOX_EPSILON, t_position.x, direction.x);
	}
	if (direction.y != 0) {
		distances[2] = this->distanceToPlane(this->m_min.y + Config::CAMERA_HEIGHT             - Config::STAY_INSIDE_SKYBOX_EPSILON, t_position.y, direction.y);
		distances[3] = this->distanceToPlane(this->m_max.y - Config::STAY_INSIDE_SKYBOX_BORDER + Config::STAY_INSIDE_SKYBOX_EPSILON, t_position.y, direction.y);
	}
	if (direction.z != 0) {
		distances[4] = this->distanceToPlane(this->m_min.z + Config::STAY_INSIDE_SKYBOX_BORDER - Config::STAY_INSIDE_SKYBOX_EPSILON, t_position.z, direction.z);
		distances[5] = this->distanceToPlane(this->m_max.z - Config::STAY_INSIDE_SKYBOX_BORDER + Config::STAY_INSIDE_SKYBOX_EPSILON, t_position.z, direction.z);
	}

	float minDistance = std::numeric_limits<float>::infinity();
	for (size_t i = 0; i < 6; ++i) {
		if (distances[i] > 0) {
			// the intersection point
			glm::vec3 intersection = t_position + direction * distances[i];

			// check if the intersection point is inside the skybox
			if (this->isInsideSkybox(intersection))
				minDistance = std::min(minDistance, distances[i]);
		}
	}

	return minDistance;
}

float Controller::distanceToPlane(const float t_planeCoord, const float t_positionCoord, const float t_directionCoord) {
	return (t_planeCoord - t_positionCoord) / t_directionCoord;
}

bool Controller::isInsideSkybox(const glm::vec3& t_position) {
	return (
		t_position.x >= this->m_min.x + Config::STAY_INSIDE_SKYBOX_BORDER - Config::STAY_INSIDE_SKYBOX_EPSILON && t_position.x <= this->m_max.x - Config::STAY_INSIDE_SKYBOX_BORDER + Config::STAY_INSIDE_SKYBOX_EPSILON &&
		t_position.y >= this->m_min.y + Config::CAMERA_HEIGHT             - Config::STAY_INSIDE_SKYBOX_EPSILON && t_position.y <= this->m_max.y - Config::STAY_INSIDE_SKYBOX_BORDER + Config::STAY_INSIDE_SKYBOX_EPSILON &&
		t_position.z >= this->m_min.z + Config::STAY_INSIDE_SKYBOX_BORDER - Config::STAY_INSIDE_SKYBOX_EPSILON && t_position.z <= this->m_max.z - Config::STAY_INSIDE_SKYBOX_BORDER + Config::STAY_INSIDE_SKYBOX_EPSILON);
}
