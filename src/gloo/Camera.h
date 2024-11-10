#pragma once

#include "ObserverSubject.h"

// include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4

// standard C++ libraries
#include <mutex>

// === default camera ==========================================================
class DefaultCamera {
public:
	static DefaultCamera* getInstance();

	glm::mat4* getView();
	glm::mat4* getProjection();

protected:
	// protected constructor to avoid creating multiple instances
	DefaultCamera(const glm::vec3& t_eye, const glm::vec3& t_direction, float t_aspectRatio);
	DefaultCamera();

	// disable copy constructor and assignment operator
	DefaultCamera(const DefaultCamera&) = delete;
	DefaultCamera& operator=(const DefaultCamera&) = delete;

	glm::vec3 m_eye;
	glm::vec3 m_direction;
	glm::vec3 m_up;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	virtual void calculateView();

private:
	// a singleton instance pointer
	static DefaultCamera* _instance;
	//static std::unique_ptr<DefaultCamera> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	//static std::mutex _mtx;
};



// === camera ==================================================================
class Camera : public DefaultCamera {
public:
	Camera(const glm::vec3& t_eye, const glm::vec3& t_direction, float t_aspectRatio);
	Camera();

	ObserverSubject<DefaultCamera>* getObserverSubject();

	void setPosition(const glm::vec3& t_eye, const glm::vec3& t_direction);

	void moveCamera(float t_distance);
	void strafeCamera(float t_distanceH, float t_distanceV);
	void rotateCamera(float t_degreesH, float t_degreesV);

private:
	ObserverSubject<DefaultCamera> m_observerSubject;
	//std::shared_ptr<ObserverSubject<DefaultCamera>> m_observerSubject;

	virtual void calculateView() override;
};
