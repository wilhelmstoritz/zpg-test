#pragma once

//#include "Camera.h"
#include "Scene.h"
#include "DeltaTime.h"

// glfw
#include <GLFW/glfw3.h>

class Controller {
public:
	Controller(GLFWwindow* t_window);

	void setScene(Scene* t_scene);

	void processInput();
	void updateCursor();

private:
	enum class platformE {
		PLATFORM_WINDOWS = 0x00060001, // 0x00060001 = GLFW_PLATFORM_WIN32
		PLATFORM_COCOA   = 0x00060002, // 0x00060002 = GLFW_PLATFORM_COCOA
		PLATFORM_WAYLAND = 0x00060003, // 0x00060003 = GLFW_PLATFORM_WAYLAND
		PLATFORM_X11     = 0x00060004, // 0x00060004 = GLFW_PLATFORM_X11
		PLATFORM_NULL    = 0x00060005  // 0x00060005 = GLFW_PLATFORM_NULL
	};

	GLFWwindow* m_window;

	Scene* m_scene;

	glm::vec3 m_min, m_max; // for simplified access
	Camera* m_camera; // for simplified access

	DeltaTime m_deltaTime;

	platformE m_platform;
	bool m_rawMouse;
	double m_lastX, m_lastY;

	void resetCursor();

	glm::vec3 getDestination(const glm::vec3& t_cameraDestination);
	float distanceToSkybox(const glm::vec3& t_position, const glm::vec3& t_direction);
	float distanceToPlane(const float t_planeCoord, const float t_positionCoord, const float t_directionCoord);
	bool isInsideSkybox(const glm::vec3& t_position);
};
