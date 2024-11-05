#include "TransformationStepTranslate.h"

// --- public ------------------------------------------------------------------
TransformationStepTranslate::TransformationStepTranslate(const glm::vec3& t_translation)
	: m_translation(t_translation) {
	this->updateMatrix();
}

void TransformationStepTranslate::setTranslation(const glm::vec3& t_translation) {
	this->m_translation = t_translation;
	this->updateMatrix();
}

// --- protected ---------------------------------------------------------------
void TransformationStepTranslate::updateMatrix() {
    this->m_matrix = glm::translate(glm::mat4(1.0f), this->m_translation);
}
