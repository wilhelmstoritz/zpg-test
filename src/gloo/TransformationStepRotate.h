#pragma once

#include "TransformationStep.h"

class TransformationStepRotate : public TransformationStep {
public:
	TransformationStepRotate(const glm::vec3& t_axis, float t_angle); // rotation by axis and angle
	TransformationStepRotate(float t_angleX, float t_angleY, float t_angleZ); // rotating around the X, Y, Z axes

	void setAngle(float t_angle);
	void setAxis(const glm::vec3& t_axis);
	void setEulerAngles(float t_angleX, float t_angleY, float t_angleZ);

protected:
	virtual void updateMatrix() override;

private:
	bool m_singleAxis;
	glm::vec3 m_axis;
	float m_angle;
	float m_angleX, m_angleY, m_angleZ;
};
