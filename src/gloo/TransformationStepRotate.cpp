#include "TransformationStepRotate.h"

// --- public ------------------------------------------------------------------
TransformationStepRotate::TransformationStepRotate(const glm::vec3& t_axis, float t_angle)
	: m_axis(t_axis), m_angle(t_angle), m_singleAxis(true) {
	this->updateMatrix();
}

TransformationStepRotate::TransformationStepRotate(const glm::vec3& t_rotation)
	: m_rotation(t_rotation), m_singleAxis(false) {
	this->updateMatrix();
}

glm::vec3 TransformationStepRotate::getAxis() const { return this->m_axis; }
float TransformationStepRotate::getAngle() const { return this->m_angle; }
glm::vec3 TransformationStepRotate::getEulerAngles() const { return this->m_rotation; }

void TransformationStepRotate::setAxis(const glm::vec3& t_axis) {
	this->m_axis = t_axis;
	this->m_singleAxis = true;

	this->updateMatrix();
}

void TransformationStepRotate::setAngle(float t_angle) { // radians
	this->m_angle = t_angle;
	this->m_singleAxis = true;

	this->updateMatrix();
}

void TransformationStepRotate::setEulerAngles(const glm::vec3& t_rotation) { // degrees
	this->m_rotation = t_rotation;
	this->m_singleAxis = false;

	this->updateMatrix();
}

bool TransformationStepRotate::animate() { return false; } // default implementation; no animation

// --- protected ---------------------------------------------------------------
void TransformationStepRotate::updateMatrix() {
	if (this->m_singleAxis) {
		// radians
		this->m_matrix = glm::rotate(glm::mat4(1.f), this->m_angle, this->m_axis);

		/*// degrees
		this->m_matrix = glm::rotate(glm::mat4(1.f), glm::radians(this->m_angle), this->m_axis);*/
	} else {
		/*// radians
		this->m_matrix = glm::rotate(glm::mat4(1.f), this->m_rotation.x, glm::vec3(1.f, 0.f, 0.f));
		this->m_matrix = glm::rotate(this->m_matrix, this->m_rotation.y, glm::vec3(0.f, 1.f, 0.f));
		this->m_matrix = glm::rotate(this->m_matrix, this->m_rotation.z, glm::vec3(0.f, 0.f, 1.f));*/

		// degrees
		this->m_matrix = glm::rotate(glm::mat4(1.f), glm::radians(this->m_rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->m_matrix = glm::rotate(this->m_matrix, glm::radians(this->m_rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->m_matrix = glm::rotate(this->m_matrix, glm::radians(this->m_rotation.z), glm::vec3(0.f, 0.f, 1.f));
	}
}
