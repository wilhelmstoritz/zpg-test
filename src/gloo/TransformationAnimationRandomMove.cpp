#include "TransformationAnimationRandomMove.h"
#include "AppMath.h"

// --- public ------------------------------------------------------------------
TransformationAnimationRandomMove::TransformationAnimationRandomMove(const glm::vec3& t_translation)
	: TransformationStepTranslate(t_translation) {
	this->generateRandomMovement();
}

bool TransformationAnimationRandomMove::animate() {
	this->m_deltaTime.update();
	float delta = this->m_deltaTime.getDeltaSeconds();

	this->m_time -= delta;
	if (this->m_time <= 0.f) {
		this->generateRandomMovement();
	}

	this->setTranslation(this->getTranslation() + this->m_direction * this->m_speed * delta);

	return true;
}

// --- private -----------------------------------------------------------------
void TransformationAnimationRandomMove::generateRandomMovement() {
	// generate random direction
	this->m_direction = glm::normalize(glm::vec3(
		AppMath::getInstance()->randomNumber(-1.f, 1.f),
		AppMath::getInstance()->randomNumber(-1.f, 1.f),
		AppMath::getInstance()->randomNumber(-1.f, 1.f)));

	// generate random speed; between 0.01 and 0.3
	this->m_speed = AppMath::getInstance()->randomNumber(0.01f, 0.3f);

	// generate random time; between 1 and 10 seconds
	this->m_time = AppMath::getInstance()->randomNumber(1.f, 10.f);
}
