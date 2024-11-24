#include "Transformation.h"
#include "TransformationStepTranslate.h"
#include "TransformationStepRotate.h"
#include "TransformationStepScale.h"

// --- public ------------------------------------------------------------------
Transformation::Transformation() {
    // default transformations
    this->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(0.f))); // index 0
    this->addStep(std::make_shared<TransformationStepRotate>(glm::vec3(0.f))); // index 1
    this->addStep(std::make_shared<TransformationStepScale>(glm::vec3(1.f))); // index 2

    this->updateMatrix();
}

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

/*
void Transformation::updateStep(size_t t_index) {
    if (t_index < this->m_steps.size()) {
        // tbd
        this->updateMatrix();
    }
}
*/

TransformationStep* Transformation::getStep(size_t t_index) {
    if (t_index < this->m_steps.size()) {
        return m_steps[t_index].get();
    }

    return nullptr; // nullptr if the index is out of range

    /*
    TransformationStep* step = transformation.getStep(stepIndex);
    if (step) {
        TransformationStepTranslate* translateStep = dynamic_cast<TransformationStepTranslate*>(step);
        if (translateStep) {
            translateStep->setTranslation(glm::vec3(1.f, 2.f, 3.f));
        }
    }
    */
}

const glm::mat4& Transformation::getTransformation() const { return this->m_finalMatrix; }

bool Transformation::hasChanged() const { return this->m_hasChanged; }
void Transformation::clearChanged() { this->m_hasChanged = false; }

// --- private -----------------------------------------------------------------
void Transformation::updateMatrix() {
    this->m_finalMatrix = glm::mat4(1.f);
    for (const auto& step : this->m_steps) {
        this->m_finalMatrix *= step->getMatrix();
    }

    this->m_hasChanged = true;
}
