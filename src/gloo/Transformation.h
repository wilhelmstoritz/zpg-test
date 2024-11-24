#pragma once

#include "TransformationStep.h"
#include "TransformationStepTranslate.h"
#include "TransformationStepRotate.h"
#include "TransformationStepScale.h"

// include the standard C++ headers
#include <vector>
#include <memory>

class Transformation {
public:
	Transformation();

	size_t addStep(std::shared_ptr<TransformationStep> t_step);
	void removeStep(size_t t_index);
	void updateStep(size_t t_index, std::shared_ptr<TransformationStep> t_step);
	void updateTranslateStep(std::shared_ptr<TransformationStepTranslate> t_step);
	void updateRotateStep(std::shared_ptr<TransformationStepRotate> t_step);
	void updateScaleStep(std::shared_ptr<TransformationStepScale> t_step);

	TransformationStep* getStep(size_t t_index);
	TransformationStepTranslate* getTranslateStep(size_t t_index);
	TransformationStepRotate* getRotateStep(size_t t_index);
	TransformationStepScale* getScaleStep(size_t t_index);
	TransformationStepTranslate* getTranslateStep();
	TransformationStepRotate* getRotateStep();
	TransformationStepScale* getScaleStep();
	const glm::mat4& getTransformation();

	void setTranslation(const glm::vec3& t_translation);
	void setRotationAxisAngle(const glm::vec3& t_axis, float t_angle); // rotation by axis and angle
	void setRotationAxis(const glm::vec3& t_axis);
	void setRotationAngle(float t_angle);
	void setRotationEulerAngles(const glm::vec3& t_rotation); // rotation around the X, Y, Z axes
	void setScale(const glm::vec3& t_scale);

	bool hasChanged() const;
	void clearChanged();

private:
	std::vector<std::shared_ptr<TransformationStep>> m_steps;
	glm::mat4 m_finalMatrix;

	bool m_hasChanged;

	void updateMatrix();
	void animate();
};
