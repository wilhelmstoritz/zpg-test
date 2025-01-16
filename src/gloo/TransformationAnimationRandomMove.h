#pragma once

#include "TransformationStepTranslate.h"
#include "DeltaTime.h"

class TransformationAnimationRandomMove : public TransformationStepTranslate {
public:
	TransformationAnimationRandomMove(const glm::vec3& t_translation);

	virtual bool animate() override;

private:
	glm::vec3 m_direction;
	float m_speed;
	float m_time;

	DeltaTime m_deltaTime;

	void randomMovement();
};
