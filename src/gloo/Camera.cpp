#include "Camera.h"

// include GLM
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

// initialization of static class members
DefaultCamera* DefaultCamera::_instance = nullptr;
//std::unique_ptr<DefaultCamera> DefaultCamera::_instance = nullptr;
//std::mutex DefaultCamera::_mtx;

// === default camera ==========================================================
// --- public ------------------------------------------------------------------
DefaultCamera* DefaultCamera::getInstance() {
	//std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr) {
		_instance = new DefaultCamera();
		//_instance.reset(new DefaultCamera());
	}

	return _instance;
	//return _instance.get();
}

glm::mat4* DefaultCamera::getView(void) { return &this->m_viewMatrix; }
glm::mat4* DefaultCamera::getProjection(void) { return &this->m_projectionMatrix; }

// --- protected ---------------------------------------------------------------
DefaultCamera::DefaultCamera(const glm::vec3& t_eye, const glm::vec3& t_direction)
	: m_eye(t_eye), m_direction(t_direction) {
	// initial view
	this->m_up = glm::vec3(0.f, 1.f, 0.f);
	this->calculateView();

	// initial projection
	// projection matrix: field of view (degrees °), x:y ratio (should respect the aspect ratio of the window), display range; min units (do not use a value of 0) <-> max units
	//this->m_projectionMatrix = glm::perspective(60.f, 4.f / 3.f, 0.1f, 100.f);
	//this->m_projectionMatrix = glm::perspective(45.f, 4.f / 3.f, 0.1f, 100.f);
	this->m_projectionMatrix = glm::perspective(45.f, 4.f / 3.f, 0.1f, 300.f);
	
	// projection matrix: left, right, bottom, top, near plane, far plane
	//this->m_projectionMatrix = glm::ortho(-10.f, 10.f, 0.f, 10.f, 0.1f, 300.f);
}

DefaultCamera::DefaultCamera()
	: DefaultCamera(glm::vec3(0.f, 1.f, 10.f), glm::vec3(0.f, 0.f, -1.f)) {
}

// --- private -----------------------------------------------------------------
void DefaultCamera::calculateView() {
	this->m_viewMatrix = glm::lookAt(this->m_eye, this->m_eye + this->m_direction, this->m_up);
}



// === camera ==================================================================
// --- public ------------------------------------------------------------------
Camera::Camera(const glm::vec3& t_eye, const glm::vec3& t_direction)
	: DefaultCamera(t_eye, t_direction), m_observerSubject(ObserverSubject<DefaultCamera>()) {
	//this->m_observerSubject = std::make_shared<ObserverSubject<DefaultCamera>>();
}

Camera::Camera() : DefaultCamera() { }

ObserverSubject<DefaultCamera>* Camera::getObserverSubject() { return &this->m_observerSubject; }

void Camera::setPosition(const glm::vec3& t_eye, const glm::vec3& t_direction) {
	this->m_eye = t_eye;
	this->m_direction = t_direction;

	this->calculateView();
}

void Camera::moveCamera(float t_distance) {
	this->m_eye += glm::normalize(this->m_direction) * t_distance; // move in the direction of the vector

	this->calculateView();
}

void Camera::strafeCamera(float t_distanceH, float t_distanceV) {
	this->m_eye += glm::normalize(glm::cross(this->m_direction, this->m_up)) * t_distanceH; // move in the direction of the vector right perpendicular to direction and up vectors
	this->m_eye += this->m_up * t_distanceV; // move in the direction of the up vector

	this->calculateView();
}

void Camera::rotateCamera(float t_degreesH, float t_degreesV) {
	// conversion from degrees to radians
	float radiansH = glm::radians(t_degreesH);
	float radiansV = glm::radians(t_degreesV);

	// pitch limitation between ±π/2 (±90°)
	//constexpr float maxPitch = glm::half_pi<float>();  // +90°
	//constexpr float minPitch = -glm::half_pi<float>(); // -90°
	constexpr float maxPitch = glm::radians(89.f);  // +89°
	constexpr float minPitch = -glm::radians(89.f); // -89°

	// find the current vertical angle between direction vector and the horizontal plane (XZ axes); the current pitch of the camera
	//float currentVerticalAngle = asin(this->m_direction.y / glm::length(this->m_direction));
	float currentPitch = asin(this->m_direction.y);

	// limit vertical rotation so that the resulting pitch does not exceed limits; ±π/2 (±90°)
	if (currentPitch + radiansV > maxPitch) {
		radiansV = maxPitch - currentPitch; // limit upward rotation
	}
	else if (currentPitch + radiansV < minPitch) {
		radiansV = minPitch - currentPitch; // limit downward rotation
	}

	/* the old way
	// rotation around the Y axis (horizontal rotation)
	float cosH = cos(radiansH);
	float sinH = sin(radiansH);
	float newX = this->m_direction.x * cosH - this->m_direction.z * sinH;
	float newZ = this->m_direction.x * sinH + this->m_direction.z * cosH;
	// update horizontal coordinates after rotation
	this->m_direction.x = newX;
	this->m_direction.z = newZ;

	// rotation around the X axis (vertical rotation)
	float cosV = cos(radiansV);
	float sinV = sin(radiansV);
	float newY = this->m_direction.y * cosV - this->m_direction.z * sinV;
	newZ = this->m_direction.y * sinV + this->m_direction.z * cosV;
	// update vertical coordinates after rotation
	this->m_direction.y = newY;
	this->m_direction.z = newZ;
	*/

	// --- rotation matrixes for horizontal and vertical rotation
	// matrix for horizontal rotation around the Y axis; yaw
	glm::mat4 rotationH = glm::rotate(glm::mat4(1.0f), radiansH, glm::vec3(0.0f, 1.0f, 0.0f));

	// apply a horizontal rotation to the direction of the camera
	this->m_direction = glm::vec3(rotationH * glm::vec4(this->m_direction, 1.0f));

	// matrix for vertical rotation around the X axis; pitch
	glm::vec3 right = glm::normalize(glm::cross(this->m_direction, this->m_up)); // vector to the right of the direction
	glm::mat4 rotationV = glm::rotate(glm::mat4(1.0f), radiansV, right);

	// apply a vertical rotation
	this->m_direction = glm::vec3(rotationV * glm::vec4(this->m_direction, 1.0f));

	// normalize direction to become a unit vector (again)
	this->m_direction = glm::normalize(this->m_direction);

	this->calculateView();
}

// --- private -----------------------------------------------------------------
void Camera::calculateView() {
	DefaultCamera::calculateView();

	this->m_observerSubject.notify(this);
	//this->m_observerSubject.get()->notify(this);
}
