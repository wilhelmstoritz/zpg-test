#pragma once

#include "TransformationStep.h"

class TransformationStepMatrix : public TransformationStep {
public:
	TransformationStepMatrix(const glm::mat4& t_matrix);

	void setMatrix(const glm::mat4& t_matrix);

	virtual bool animate() override;

protected:
	virtual void updateMatrix() override;
};
