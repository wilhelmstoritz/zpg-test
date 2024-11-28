#pragma once

#include "TransformationStep.h"

class TransformationStepTranslate : public TransformationStep {
public:
	TransformationStepTranslate(const glm::vec3& t_translation);

	glm::vec3 getTranslation() const;

	void setTranslation(const glm::vec3& t_translation);

	virtual bool animate() override;

protected:
	virtual void updateMatrix() override;

private:
	glm::vec3 m_translation;
};
