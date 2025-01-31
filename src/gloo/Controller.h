#pragma once

//#include "Camera.h"
#include "Scene.h"
#include "DeltaTime.h"

// GLFW
#include <GLFW/glfw3.h>

class Controller {
public:
	Controller(GLFWwindow* t_window);

	void setScene(Scene* t_scene);

	void processInput();
	void resetCursor();

private:
	GLFWwindow* m_window;

	Scene* m_scene;

	glm::vec3 m_min, m_max; // for simplified access
	Camera* m_camera; // for simplified access

	DeltaTime m_deltaTime;
	double m_lastX, m_lastY;

	glm::vec3 getDestination(const glm::vec3& t_cameraDestination);
	float distanceToSkybox(const glm::vec3& t_position, const glm::vec3& t_direction);
	float distanceToPlane(const float t_planeCoord, const float t_positionCoord, const float t_directionCoord);
	bool isInsideSkybox(const glm::vec3& t_position);
};
