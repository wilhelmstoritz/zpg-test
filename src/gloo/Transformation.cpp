#include "Transformation.h"

// --- public ------------------------------------------------------------------
Transformation::Transformation()
	: m_finalMatrix(glm::mat4(1.0f)) { }

size_t Transformation::addStep(std::shared_ptr<TransformationStep> t_step) {
    this->m_steps.push_back(t_step);
    this->updateMatrix();

    return this->m_steps.size() - 1;
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

TransformationStep* Transformation::getStep(size_t t_index) {
    if (t_index >= 0 && t_index < this->m_steps.size()) {
        return m_steps[t_index].get();
    }

    return nullptr; // nullptr if the index is out of range

    /*
    TransformationStep* step = transformation.getStep(stepIndex);
    if (step) {
        TransformationStepTranslate* translateStep = dynamic_cast<TransformationStepTranslate*>(step);
        if (translateStep) {
            translateStep->setTranslation(glm::vec3(1.0f, 2.0f, 3.0f));
        }
    }
    */
}

const glm::mat4& Transformation::getTransformation() const { return this->m_finalMatrix; }

// --- private -----------------------------------------------------------------
void Transformation::updateMatrix() {
    this->m_finalMatrix = glm::mat4(1.0f);
    for (const auto& step : this->m_steps) {
        this->m_finalMatrix *= step->getMatrix();
    }
}
