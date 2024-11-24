#pragma once

#include "TransformationStep.h"

class TransformationStepScale : public TransformationStep {
public:
	TransformationStepScale(const glm::vec3& t_scale);

	glm::vec3 getScale() const;

	void setScale(const glm::vec3& t_scale);

protected:
	virtual void updateMatrix() override;
	virtual void animate() override;

private:
	glm::vec3 m_scale;
};
