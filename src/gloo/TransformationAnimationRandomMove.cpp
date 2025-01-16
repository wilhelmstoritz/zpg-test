#include "TransformationAnimationRandomMove.h"
#include "AppMath.h"

// --- public ------------------------------------------------------------------
TransformationAnimationRandomMove::TransformationAnimationRandomMove(const glm::vec3& t_translation)
	: TransformationStepTranslate(t_translation) {
	this->randomMovement();
}

bool TransformationAnimationRandomMove::animate() {
	this->m_deltaTime.update();
	float delta = this->m_deltaTime.getDeltaSeconds();

	this->m_time -= delta;
	if (this->m_time <= 0.f)
		this->randomMovement();

	this->setTranslation(this->getTranslation() + this->m_direction * this->m_speed * delta);

	return true;
}

// --- private -----------------------------------------------------------------
void TransformationAnimationRandomMove::randomMovement() {
	this->m_direction = glm::normalize(glm::vec3(                    // direction; random vector
		AppMath::getInstance()->randomNumber(-1.f, 1.f),
		AppMath::getInstance()->randomNumber(-1.f, 1.f),
		AppMath::getInstance()->randomNumber(-1.f, 1.f)));

	this->m_speed = AppMath::getInstance()->randomNumber(.01f, .3f); // speed; between 0.01 and 0.3
	this->m_time  = AppMath::getInstance()->randomNumber(1.f, 10.f); // time; between 1 and 10 seconds
}
