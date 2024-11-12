#pragma once

#include "ObserverSubject.h"

// include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4

class Camera {
public:
	Camera(const glm::vec3& t_eye, const glm::vec3& t_direction, float t_aspectRatio);
	//Camera();

	ObserverSubject<Camera>* getObserverSubject();

	glm::mat4* getView();
	glm::mat4* getProjection();

	void setPosition(const glm::vec3& t_eye, const glm::vec3& t_direction);

	void moveCamera(float t_distance);
	void strafeCamera(float t_distanceH, float t_distanceV);
	void rotateCamera(float t_degreesH, float t_degreesV);

private:
	ObserverSubject<Camera> m_observerSubject;
	//std::shared_ptr<ObserverSubject<Camera>> m_observerSubject;

	glm::vec3 m_eye;
	glm::vec3 m_direction;
	glm::vec3 m_up;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	void calculateView();
};
