#include "TransformationAnimationRotate.h"

// --- public ------------------------------------------------------------------
TransformationAnimationRotate::TransformationAnimationRotate(const glm::vec3& t_rotation, const glm::vec3& t_rps)
	: TransformationStepRotate(t_rotation) {
	this->setRPS(t_rps);
}

void TransformationAnimationRotate::setRPS(const glm::vec3& t_rps) {
	//this->m_radSpeed = t_rps * 2.f * glm::pi<float>();
	this->m_degSpeed = t_rps * 360.f;
}

bool TransformationAnimationRotate::animate() {
	this->m_deltaTime.update();
	float delta = this->m_deltaTime.getDeltaSeconds();

	this->setEulerAngles(this->getEulerAngles() + this->m_degSpeed * delta);

	return true;
}
