#include "TransformationStepMatrix.h"

// --- public ------------------------------------------------------------------
TransformationStepMatrix::TransformationStepMatrix(const glm::mat4& t_matrix) {
	this->setMatrix(t_matrix);
}

void TransformationStepMatrix::setMatrix(const glm::mat4& t_matrix) {
	this->m_matrix = t_matrix;
}

bool TransformationStepMatrix::animate() { return false; } // default implementation; no animation

// --- protected ---------------------------------------------------------------
void TransformationStepMatrix::updateMatrix() { } // no need to recalculate; matrix is ​​set directly
