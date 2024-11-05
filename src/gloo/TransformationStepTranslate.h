#pragma once

#include "TransformationStep.h"

class TransformationStepTranslate : public TransformationStep {
public:
	TransformationStepTranslate(const glm::vec3& t_translation);

	void setTranslation(const glm::vec3& t_translation);

protected:
	virtual void updateMatrix() override;

private:
	glm::vec3 m_translation;
};
