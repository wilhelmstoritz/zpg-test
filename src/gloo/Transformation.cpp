#include "Transformation.h"

// --- public ------------------------------------------------------------------
Transformation::Transformation()
	: m_finalMatrix(glm::mat4(1.0f)) { }

void Transformation::addStep(std::shared_ptr<TransformationStep> t_step) {
    this->m_steps.push_back(t_step);
    this->updateMatrix();
}

void Transformation::removeStep(size_t t_index) {
    if (t_index < this->m_steps.size()) {
        this->m_steps.erase(this->m_steps.begin() + t_index);
        this->updateMatrix();
    }
}

void Transformation::updateStep(size_t t_index) {
    if (t_index < this->m_steps.size()) {
        this->updateMatrix();
    }
}

//const glm::mat4& Transformation::getTransformation() const { return this->m_finalMatrix; }
glm::mat4& Transformation::getTransformation() { return this->m_finalMatrix; }

// --- private -----------------------------------------------------------------
void Transformation::updateMatrix() {
    this->m_finalMatrix = glm::mat4(1.0f);
    for (const auto& step : this->m_steps) {
        this->m_finalMatrix *= step->getMatrix();
    }
}
