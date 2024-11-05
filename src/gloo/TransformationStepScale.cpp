#include "TransformationStepScale.h"

// --- public ------------------------------------------------------------------
TransformationStepScale::TransformationStepScale(const glm::vec3& t_scale)
	: m_scale(t_scale) {
	this->updateMatrix();
}

void TransformationStepScale::setScale(const glm::vec3& t_scale) {
	this->m_scale = t_scale;
	this->updateMatrix();
}

// --- protected ---------------------------------------------------------------
void TransformationStepScale::updateMatrix() {
    this->m_matrix = glm::scale(glm::mat4(1.0f), this->m_scale);
}
