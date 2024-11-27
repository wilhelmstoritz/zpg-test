#pragma once

#include "Camera.h"
#include "DeltaTime.h"

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

	DeltaTime m_deltaTime;

	glm::vec3 getDestination(const glm::vec3& t_cameraDestination);
	float distanceToSkybox(const glm::vec3& t_position, const glm::vec3& t_direction);
	float distanceToPlane(const float t_planeCoord, const float t_positionCoord, const float t_directionCoord);
	bool isInsideSkybox(const glm::vec3& t_position);
};
