#include "TransformationAnimationRotate.h"

// --- public ------------------------------------------------------------------
TransformationAnimationRotate::TransformationAnimationRotate(const glm::vec3& t_rotation, const glm::vec3& t_rps)
	: TransformationStepRotate(t_rotation), m_rps(t_rps) { }

void TransformationAnimationRotate::animate() {
	this->m_deltaTime.update();

	float delta = this->m_deltaTime.getDeltaSeconds();
	this->setEulerAngles(this->getEulerAngles() + this->m_rps * delta);
}
