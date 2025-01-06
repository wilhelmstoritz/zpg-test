#pragma once

#include "TransformationStep.h"

class TransformationStepRotate : public TransformationStep {
public:
	TransformationStepRotate(const glm::vec3& t_axis, float t_angle); // rotation by axis and angle
	TransformationStepRotate(const glm::vec3& t_rotation); // rotation around the X, Y, Z axes

	glm::vec3 getAxis() const;
	float getAngle() const;
	glm::vec3 getEulerAngles() const;

	void setAxis(const glm::vec3& t_axis);
	void setAngle(float t_angle);
	void setEulerAngles(const glm::vec3& t_rotation);

	virtual bool animate() override;

protected:
	virtual void updateMatrix() override;

private:
	bool m_singleAxis;

	glm::vec3 m_axis;
	float m_angle; // radians
	
	glm::vec3 m_rotation; // degrees
};
