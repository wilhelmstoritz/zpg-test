#pragma once

#include "TransformationStep.h"

class TransformationStepScale : public TransformationStep {
public:
	TransformationStepScale(const glm::vec3& t_scale);

	void setScale(const glm::vec3& t_scale);

protected:
	virtual void updateMatrix() override;

private:
	glm::vec3 m_scale;
};
