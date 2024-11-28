#include "TransformationStepTranslate.h"

// --- public ------------------------------------------------------------------
TransformationStepTranslate::TransformationStepTranslate(const glm::vec3& t_translation)
	: m_translation(t_translation) {
	this->updateMatrix();
}

glm::vec3 TransformationStepTranslate::getTranslation() const { return this->m_translation; }

void TransformationStepTranslate::setTranslation(const glm::vec3& t_translation) {
	this->m_translation = t_translation;

	this->updateMatrix();
}

bool TransformationStepTranslate::animate() { return false; } // default implementation; no animation

// --- protected ---------------------------------------------------------------
void TransformationStepTranslate::updateMatrix() {
    this->m_matrix = glm::translate(glm::mat4(1.f), this->m_translation);
}
