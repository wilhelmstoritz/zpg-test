#pragma once

#include "TransformationStepRotate.h"
#include "DeltaTime.h"

class TransformationAnimationRotate : public TransformationStepRotate {
public:
	TransformationAnimationRotate(const glm::vec3& t_rotation, const glm::vec3& t_rps); // rotation around the X, Y, Z axes; rotation speed (in rps) around the X, Y, Z axes

	void setRPS(const glm::vec3& t_rps);

	virtual bool animate() override;

private:
	//glm::vec3 m_radSpeed; // rotation speed (in rad/s) around the X, Y, Z axes
	glm::vec3 m_degSpeed; // rotation speed (in deg/s) around the X, Y, Z axes
	DeltaTime m_deltaTime;
};
