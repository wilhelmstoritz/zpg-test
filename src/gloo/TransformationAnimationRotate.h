#pragma once

#include "TransformationStepRotate.h"
#include "DeltaTime.h"

class TransformationAnimationRotate : public TransformationStepRotate {
public:
	TransformationAnimationRotate(const glm::vec3& t_rotation, const glm::vec3& t_rps); // rotation around the X, Y, Z axes; rotation speed (in rps) around the X, Y, Z axes

	virtual void animate() override;

private:
	glm::vec3 m_rps; // rotation speed (in rps) around the X, Y, Z axes
	DeltaTime m_deltaTime;
};
