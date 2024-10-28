#include "ZPGCamera.h"
//#include "ZPGShaderProgram.h"

// include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

// --- public ------------------------------------------------------------------
//ZPGCamera::ZPGCamera(ZPGShaderProgram* t_shaderProgram) { }

ZPGCamera::ZPGCamera() {
	//this->m_shaderProgram = t_shaderProgram;

	// initial view
	//this->m_eye = glm::vec3(0.f, 0.f, 10.f);
	this->m_direction = glm::vec3(0.f, 0.f, -1.f);
	this->m_up = glm::vec3(0.f, 1.f, 0.f);

	this->m_eye = glm::vec3(0.f, 0.f, 40.f);
	
	// view matrix
	//this->m_viewMatrix = glm::mat4(1.f); // identity matrix (jednotkova matice)
	this->calculateView();

	/*
	poměr okna byste měli upravovat podle rozlišení okna, ve kterém se obsah zobrazuje.
	z_near nastavte na hodnotu 0.1, nepouživejte hodnotu 0.
	*/
	// projection matrix: 60° field of view, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//this->m_projectionMatrix = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// projection matrix: 45° field of view, 4:3 ratio, display range : 0.1 unit <-> 100 units
	this->m_projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

}

glm::mat4 ZPGCamera::getView(void) { return this->m_viewMatrix; }
glm::mat4 ZPGCamera::getProjection(void) { return this->m_projectionMatrix; }

void ZPGCamera::moveCamera(float t_distance) {
	this->m_eye += glm::normalize(this->m_direction) * t_distance; // move in the direction of the vector

	this->calculateView();
}

void ZPGCamera::strafeCamera(float t_distance) {
	this->m_eye += glm::normalize(glm::cross(this->m_direction, this->m_up)) * t_distance; // move in the direction of the vector right perpendicular to m_direction and m_up

	this->calculateView();
}

void ZPGCamera::rotateCamera(float t_degreesH, float t_degreesV) {
    // conversion from degrees to radians
    float radiansH = glm::radians(t_degreesH);
    float radiansV = glm::radians(t_degreesV);

	// find the current vertical angle between direction vector and the horizontal plane (XZ axes)
	float currentVerticalAngle = asin(this->m_direction.y / glm::length(this->m_direction));

	// limit vertical rotation so that the resulting pitch does not exceed ±π/2 (±90°)
	if (currentVerticalAngle + radiansV > glm::half_pi<float>()) {
		radiansV = glm::half_pi<float>() - currentVerticalAngle; // limit upward rotation
	}
	else if (currentVerticalAngle + radiansV < -glm::half_pi<float>()) {
		radiansV = -glm::half_pi<float>() - currentVerticalAngle; // limit downward rotation
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

	// rotation matrixes for horizontal and vertical rotation
	glm::mat4 rotationH = glm::rotate(glm::mat4(1.0f), radiansH, glm::vec3(0.0f, 1.0f, 0.0f)); // horizontal rotation around the Y axis
	glm::mat4 rotationV = glm::rotate(glm::mat4(1.0f), radiansV, glm::vec3(1.0f, 0.0f, 0.0f)); // vertical rotation around the X axis

	// combine both rotations (horizontal first, then vertical)
	glm::mat4 combinedRotation = rotationV * rotationH;

	// apply a combined rotation to the direction vector
	this->m_direction = glm::vec3(combinedRotation * glm::vec4(this->m_direction, 1.0f));

	// normalize direction to become a unit vector (again)
	this->m_direction = glm::normalize(this->m_direction);

	this->calculateView();
}

// --- private -----------------------------------------------------------------
void ZPGCamera::calculateView() {
	this->m_viewMatrix = glm::lookAt(this->m_eye, this->m_eye + this->m_direction, this->m_up);
}
