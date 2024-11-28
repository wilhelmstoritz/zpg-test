#include "TransformationStepScale.h"

// --- public ------------------------------------------------------------------
TransformationStepScale::TransformationStepScale(const glm::vec3& t_scale)
	: m_scale(t_scale) {
	this->updateMatrix();
}

glm::vec3 TransformationStepScale::getScale() const { return this->m_scale; }

void TransformationStepScale::setScale(const glm::vec3& t_scale) {
	this->m_scale = t_scale;

	this->updateMatrix();
}

bool TransformationStepScale::animate() { return false; } // default implementation; no animation

// --- protected ---------------------------------------------------------------
void TransformationStepScale::updateMatrix() {
    this->m_matrix = glm::scale(glm::mat4(1.f), this->m_scale);
}
