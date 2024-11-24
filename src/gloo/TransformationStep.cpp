#include "TransformationStep.h"

// --- public ------------------------------------------------------------------
TransformationStep::TransformationStep()
	: m_matrix(glm::mat4(1.f)) { }

glm::mat4 TransformationStep::getMatrix() const {
	return this->m_matrix;
}
