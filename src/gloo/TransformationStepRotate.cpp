#include "TransformationStepRotate.h"

// --- public ------------------------------------------------------------------
TransformationStepRotate::TransformationStepRotate(const glm::vec3& t_axis, float t_angle)
	: m_axis(t_axis), m_angle(t_angle), m_singleAxis(true) {
	this->updateMatrix();
}

TransformationStepRotate::TransformationStepRotate(float t_angleX, float t_angleY, float t_angleZ)
	: m_angleX(t_angleX), m_angleY(t_angleY), m_angleZ(t_angleZ), m_singleAxis(false) {
	this->updateMatrix();
}

void TransformationStepRotate::setAngle(float t_angle) {
	this->m_angle = t_angle;
	this->m_singleAxis = true;
	this->updateMatrix();
}

void TransformationStepRotate::setAxis(const glm::vec3& t_axis) {
	this->m_axis = t_axis;
	this->m_singleAxis = true;
	this->updateMatrix();
}

void TransformationStepRotate::setEulerAngles(float t_angleX, float t_angleY, float t_angleZ) {
	this->m_angleX = t_angleX;
	this->m_angleY = t_angleY;
	this->m_angleZ = t_angleZ;
	this->m_singleAxis = false;
	this->updateMatrix();
}

// --- protected ---------------------------------------------------------------
void TransformationStepRotate::updateMatrix() {
	if (this->m_singleAxis) {
		this->m_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(this->m_angle), this->m_axis);
	} else {
		this->m_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(this->m_angleX), glm::vec3(1.0f, 0.0f, 0.0f));
		this->m_matrix = glm::rotate(this->m_matrix, glm::radians(this->m_angleY), glm::vec3(0.0f, 1.0f, 0.0f));
		this->m_matrix = glm::rotate(this->m_matrix, glm::radians(this->m_angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
	}
}
