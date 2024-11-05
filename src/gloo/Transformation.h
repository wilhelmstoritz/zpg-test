#pragma once

// include the standard C++ headers
#include <vector>
#include <memory>

#include "TransformationStep.h"

class Transformation {
public:
	Transformation();

	void addStep(std::shared_ptr<TransformationStep> t_step);
	void removeStep(size_t t_index);
	void updateStep(size_t t_index);
	//const glm::mat4& getTransformation() const;
	glm::mat4& getTransformation();

private:
	std::vector<std::shared_ptr<TransformationStep>> m_steps;
	glm::mat4 m_finalMatrix;

	void updateMatrix();
};
