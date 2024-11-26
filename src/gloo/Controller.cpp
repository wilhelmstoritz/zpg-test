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
	//distance = 10.f; // TODO: remove this line
	if (glfwGetKey(this->m_window, GLFW_KEY_LEFT_SHIFT)  == GLFW_PRESS ||
		glfwGetKey(this->m_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) { distance = Config::MOVEMENT_SPEED_RUN * delta; }

	if (glfwGetKey(this->m_window, GLFW_KEY_UP) == GLFW_PRESS)   { this->moveCameraForward(distance); }
	if (glfwGetKey(this->m_window, GLFW_KEY_DOWN) == GLFW_PRESS) { this->moveCameraBackward(distance); }

	//if (glfwGetKey(this->m_window, GLFW_KEY_UP)    == GLFW_PRESS) { this->m_camera->moveCamera(std::min(distance, distanceToSkyboxForward)); }
	//if (glfwGetKey(this->m_window, GLFW_KEY_DOWN)  == GLFW_PRESS) { this->m_camera->moveCamera(-std::min(distance, distanceToSkyboxBackward)); }
	//if (glfwGetKey(this->m_window, GLFW_KEY_RIGHT) == GLFW_PRESS) { this->m_camera->strafeCamera(std::min(distance, distanceToSkyboxForward), 0.f); }
	//if (glfwGetKey(this->m_window, GLFW_KEY_LEFT)  == GLFW_PRESS) { this->m_camera->strafeCamera(-std::min(distance, distanceToSkyboxBackward), 0.f); }

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
void Controller::moveCameraForward(const float t_distance) {
	float epsilon = 1e-6f;
	epsilon = 1;

	glm::vec3 cameraPosition = *this->m_camera->getEye();
	glm::vec3 cameraDirection = *this->m_camera->getDirection();

	if (cameraPosition.x <= Config::SKYBOX_XMIN + 1) cameraPosition.x = Config::SKYBOX_XMIN + epsilon + 1;
	if (cameraPosition.x >= Config::SKYBOX_XMAX - 1) cameraPosition.x = Config::SKYBOX_XMAX - epsilon - 1;
	if (cameraPosition.y <= Config::SKYBOX_YMIN + 1) cameraPosition.y = Config::SKYBOX_YMIN + epsilon + 1;
	if (cameraPosition.y >= Config::SKYBOX_YMAX - 1) cameraPosition.y = Config::SKYBOX_YMAX - epsilon - 1;
	if (cameraPosition.z <= Config::SKYBOX_ZMIN + 1) cameraPosition.z = Config::SKYBOX_ZMIN + epsilon + 1;
	if (cameraPosition.z >= Config::SKYBOX_ZMAX - 1) cameraPosition.z = Config::SKYBOX_ZMAX - epsilon - 1;

	float distanceToSkybox = this->distanceToSkybox(*this->m_camera->getEye(), *this->m_camera->getDirection());
	float movementDistance = std::min(t_distance, distanceToSkybox);
	//if (movementDistance != distanceToSkybox || distanceToSkybox > epsilon) {
		this->m_camera->moveCamera(movementDistance);
	//}
}

void Controller::moveCameraBackward(const float t_distance) {
	this->m_camera->moveCamera(-t_distance);
}

float Controller::distanceToSkybox(const glm::vec3 t_position, const glm::vec3 t_direction) {
	//t_direction = glm::normalize(t_direction); // already normalized in Camera::getDirection()

	// calculate the distance to each (relevant) plane of the skybox
	float distances[6] = { std::numeric_limits<float>::infinity() };
	
	if (t_direction.x != 0) {
		distances[0] = this->distanceToPlane(Config::SKYBOX_XMIN + 1, t_position.x, t_direction.x);
		distances[1] = this->distanceToPlane(Config::SKYBOX_XMAX - 1, t_position.x, t_direction.x);
	}
	if (t_direction.y != 0) {
		distances[2] = this->distanceToPlane(Config::SKYBOX_YMIN + Config::CAMERA_HEIGHT, t_position.y, t_direction.y);
		distances[3] = this->distanceToPlane(Config::SKYBOX_YMAX - 1,                     t_position.y, t_direction.y);
	}
	if (t_direction.z != 0) {
		distances[4] = this->distanceToPlane(Config::SKYBOX_ZMIN + 1, t_position.z, t_direction.z);
		distances[5] = this->distanceToPlane(Config::SKYBOX_ZMAX - 1, t_position.z, t_direction.z);
	}

	float minDistance = std::numeric_limits<float>::infinity();
	for (uint32_t i = 0; i < 6; ++i) {
		if (distances[i] >= 0) {
			// the intersection point
			glm::vec3 intersection = t_position + t_direction * distances[i];

			// check if the intersection point is inside the skybox
			if (this->isInsideSkybox(intersection)) {
				minDistance = std::min(minDistance, distances[i]);
			}
		}
	}

	return minDistance;
}

float Controller::distanceToPlane(const float t_planeCoord, const float t_positionCoord, const float t_directionCoord) {
	return (t_planeCoord - t_positionCoord) / t_directionCoord;
}

bool Controller::isInsideSkybox(const glm::vec3 t_position) {
	//return !Config::STAY_INSIDE_SKYBOX || (
	return (
		t_position.x >= Config::SKYBOX_XMIN + 1                     && t_position.x <= Config::SKYBOX_XMAX - 1 &&
		t_position.y >= Config::SKYBOX_YMIN + Config::CAMERA_HEIGHT && t_position.y <= Config::SKYBOX_YMAX - 1 &&
		t_position.z >= Config::SKYBOX_ZMIN + 1                     && t_position.z <= Config::SKYBOX_ZMAX - 1);
}
