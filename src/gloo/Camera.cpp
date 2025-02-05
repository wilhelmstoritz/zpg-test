#include "Camera.h"
#include "Config.h"

// glm
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

// --- public ------------------------------------------------------------------
Camera::Camera(const std::string& t_name, const glm::vec3& t_eye, const glm::vec3& t_direction, float t_aspectRatio)
	: m_name(t_name), m_eye(t_eye), m_direction(glm::normalize(t_direction)) {
	// initial view
	this->m_up = glm::vec3(0.f, 1.f, 0.f);
	this->calculateView();

	// initial projection
	this->setProjection(Config::CAMERA_FOV, t_aspectRatio, Config::CAMERA_NEAR, Config::CAMERA_FAR);
}

std::string Camera::getName() { return this->m_name; }

glm::vec3 Camera::getEye()        { return this->m_eye; }
glm::vec3 Camera::getDirection()  { return this->m_direction; }
glm::vec3 Camera::getUp()         { return this->m_up; }
glm::mat4 Camera::getView()       { return this->m_viewMatrix; }
glm::mat4 Camera::getProjection() { return this->m_projectionMatrix; }

glm::vec3 Camera::getMoveDestination(float t_distance) {
	return this->m_eye
		+ glm::normalize(this->m_direction) * t_distance; // move in the direction of the vector
}

glm::vec3 Camera::getStrafeDestination(float t_distanceH, float t_distanceV) {
	return this->m_eye
		+ glm::normalize(glm::cross(this->m_direction, this->m_up)) * t_distanceH // move in the direction of the vector right perpendicular to direction and up vectors
		+ this->m_up * t_distanceV; // move in the direction of the up vector
}

void Camera::setPosition(const glm::vec3& t_eye, const glm::vec3& t_direction) {
	this->m_eye = t_eye;
	this->m_direction = glm::normalize(t_direction);

	this->calculateView();
}

void Camera::setProjection(float t_fov, float t_aspectRatio, float t_near, float t_far) {
	// projection matrix: field of view (rad; optimal deg 45-60°), x:y ratio (should respect the aspect ratio of the window), display range; min units (do not use a value of 0) <-> max units
	//this->m_projectionMatrix = glm::perspective(glm::radians(45.f), 4.f / 3.f, .1f, 100.f);
	//this->m_projectionMatrix = glm::perspective(glm::radians(Config::CAMERA_FOV), t_aspectRatio, Config::CAMERA_NEAR, Config::CAMERA_FAR);
	this->m_projectionMatrix = glm::perspective(glm::radians(t_fov), t_aspectRatio, t_near, t_far);

	// projection matrix: left, right, bottom, top, near plane, far plane
	//this->m_projectionMatrix = glm::ortho(-100.f, 100.f, 0.f, 100.f, .1f, 300.f);
	//this->m_projectionMatrix = glm::ortho(-40.f, 40.f, -30.f, 30.f, .1f, 300.f);
	
	this->notifyObservers();
}

void Camera::moveCamera(float t_distance) {
	//printf("[camera] move : distance %f\n", t_distance);

	//this->m_eye += glm::normalize(this->m_direction) * t_distance; // move in the direction of the vector
	this->m_eye = this->getMoveDestination(t_distance);

	this->calculateView();
}

void Camera::strafeCamera(float t_distanceH, float t_distanceV) {
	//printf("[camera] strafe : h %f, v %f\n", t_distanceH, t_distanceV);

	//this->m_eye += glm::normalize(glm::cross(this->m_direction, this->m_up)) * t_distanceH; // move in the direction of the vector right perpendicular to direction and up vectors
	//this->m_eye += this->m_up * t_distanceV; // move in the direction of the up vector
	this->m_eye = this->getStrafeDestination(t_distanceH, t_distanceV);

	this->calculateView();
}

void Camera::rotateCamera(float t_degreesH, float t_degreesV) {
	//printf("[camera] rotate : h %fdeg, v %fdeg\n", t_degreesH, t_degreesV);

	// conversion from degrees to radians
	float radiansH = glm::radians(t_degreesH);
	float radiansV = glm::radians(t_degreesV);

	// pitch limitation between ±π/2 (±90°)
	//constexpr float maxPitch =  glm::half_pi<float>(); // +90°
	//constexpr float minPitch = -glm::half_pi<float>(); // -90°
	constexpr float maxPitch =  glm::radians(88.f); // +88°
	constexpr float minPitch = -glm::radians(88.f); // -88°

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
	glm::mat4 rotationH = glm::rotate(glm::mat4(1.f), radiansH, glm::vec3(0.f, 1.f, 0.f));

	// apply a horizontal rotation to the direction of the camera
	this->m_direction = glm::vec3(rotationH * glm::vec4(this->m_direction, 1.f));

	// matrix for vertical rotation around the X axis; pitch
	glm::vec3 right = glm::normalize(glm::cross(this->m_direction, this->m_up)); // vector to the right of the direction
	glm::mat4 rotationV = glm::rotate(glm::mat4(1.f), radiansV, right);

	// apply a vertical rotation
	this->m_direction = glm::vec3(rotationV * glm::vec4(this->m_direction, 1.f));

	// normalize direction to become a unit vector (again)
	this->m_direction = glm::normalize(this->m_direction);

	this->calculateView();
}

// --- private -----------------------------------------------------------------
void Camera::calculateView() {
	this->m_viewMatrix = glm::lookAt(this->m_eye, this->m_eye + this->m_direction, this->m_up);

	this->notifyObservers();
}
