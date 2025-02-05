#pragma once

#include "ObserverSubject.h"

// include glm
#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4

// standard c++ libraries
#include <string>

class Camera : public ObserverSubject<Camera> {
public:
	Camera(const std::string& t_name, const glm::vec3& t_eye, const glm::vec3& t_direction,
		float t_aspectRatio = 1.f); // default aspect ratio is 1:1; square window; should be/will be updated according to the window size when the window is created

	std::string getName();

	glm::vec3 getEye();
	glm::vec3 getDirection();
	glm::vec3 getUp();
	glm::mat4 getView();
	glm::mat4 getProjection();

	glm::vec3 getMoveDestination(float t_distance);
	glm::vec3 getStrafeDestination(float t_distanceH, float t_distanceV);

	void setPosition(const glm::vec3& t_eye, const glm::vec3& t_direction);
	void setProjection(float t_fov, float t_aspectRatio, float t_near, float t_far);

	void moveCamera(float t_distance);
	void strafeCamera(float t_distanceH, float t_distanceV);
	void rotateCamera(float t_degreesH, float t_degreesV);

private:
	std::string m_name;

	glm::vec3 m_eye;
	glm::vec3 m_direction;
	glm::vec3 m_up;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	void calculateView();
};
