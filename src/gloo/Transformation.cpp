#include "Transformation.h"

// --- public ------------------------------------------------------------------
Transformation::Transformation() {
    // default transformations
    this->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(0.f))); // default translate step; index 0
    this->addStep(std::make_shared<TransformationStepRotate>   (glm::vec3(0.f))); // default rotate step; index 1
    this->addStep(std::make_shared<TransformationStepScale>    (glm::vec3(1.f))); // default scale step; index 2

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

void Transformation::updateStep(size_t t_index, std::shared_ptr<TransformationStep> t_step) {
	if (t_index < this->m_steps.size()) {
		this->m_steps[t_index] = t_step;
		this->updateMatrix();
	}
}

void Transformation::updateTranslateStep(std::shared_ptr<TransformationStepTranslate> t_step) {
	this->updateStep(0, t_step); // default translate step; index 0
}

void Transformation::updateRotateStep(std::shared_ptr<TransformationStepRotate> t_step) {
	this->updateStep(1, t_step); // default rotate step; index 1
}

void Transformation::updateScaleStep(std::shared_ptr<TransformationStepScale> t_step) {
	this->updateStep(2, t_step); // default scale step; index 2
}

TransformationStep* Transformation::getStep(size_t t_index) {
    if (t_index < this->m_steps.size())
        return m_steps[t_index].get();

    return nullptr; // nullptr if the index is out of range
}

TransformationStepTranslate* Transformation::getTranslateStep(size_t t_index) { // default translate step; index 0
    TransformationStep* step = this->getStep(t_index);
    if (step)
        return dynamic_cast<TransformationStepTranslate*>(step);

    return nullptr; // nullptr if the index is out of range or the step is not a translate step
}

TransformationStepRotate* Transformation::getRotateStep(size_t t_index) { // default rotate step; index 1
	TransformationStep* step = this->getStep(t_index);
    if (step)
        return dynamic_cast<TransformationStepRotate*>(step);

	return nullptr; // nullptr if the index is out of range or the step is not a rotate step
}

TransformationStepScale* Transformation::getScaleStep(size_t t_index) { // default scale step; index 2
	TransformationStep* step = this->getStep(t_index);
    if (step)
        return dynamic_cast<TransformationStepScale*>(step);

	return nullptr; // nullptr if the index is out of range or the step is not a scale step
}

const glm::mat4& Transformation::getModelMatrix() { return this->m_modelMatrix; }

void Transformation::setTranslation(const glm::vec3& t_translation) {
	TransformationStepTranslate* translateStep = this->getTranslateStep();
	if (translateStep) {
		translateStep->setTranslation(t_translation);

        this->updateMatrix();
	}
}

void Transformation::setRotationAxisAngle(const glm::vec3& t_axis, float t_angle) {
	TransformationStepRotate* rotateStep = this->getRotateStep();
	if (rotateStep) {
		rotateStep->setAxis(t_axis);
		rotateStep->setAngle(t_angle);

        this->updateMatrix();
	}
}

void Transformation::setRotationAxis(const glm::vec3& t_axis) {
	TransformationStepRotate* rotateStep = this->getRotateStep();
	if (rotateStep) {
		rotateStep->setAxis(t_axis);

        this->updateMatrix();
	}
}

void Transformation::setRotationAngle(float t_angle) {
	TransformationStepRotate* rotateStep = this->getRotateStep();
	if (rotateStep) {
		rotateStep->setAngle(t_angle);

		this->updateMatrix();
	}
}

void Transformation::setRotationEulerAngles(const glm::vec3& t_rotation) {
	TransformationStepRotate* rotateStep = this->getRotateStep();
	if (rotateStep) {
		rotateStep->setEulerAngles(t_rotation);

        this->updateMatrix();
	}
}

void Transformation::setScale(const glm::vec3& t_scale) {
	TransformationStepScale* scaleStep = this->getScaleStep();
	if (scaleStep) {
		scaleStep->setScale(t_scale);

		this->updateMatrix();
	}
}

void Transformation::animate() {
	bool hasChanged = false;
	for (const auto& step : this->m_steps)
		hasChanged |= step->animate();

	if (hasChanged) this->updateMatrix();
}

bool Transformation::hasChanged() const { return this->m_hasChanged; }
void Transformation::clearChanged() { this->m_hasChanged = false; }

// --- private -----------------------------------------------------------------
void Transformation::updateMatrix() {
    this->m_modelMatrix = glm::mat4(1.f);
    for (const auto& step : this->m_steps)
        this->m_modelMatrix *= step->getMatrix();

    this->m_hasChanged = true;
}
