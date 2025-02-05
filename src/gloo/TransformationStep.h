#pragma once

// glm
//#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class TransformationStep {
public:
	TransformationStep();
	virtual ~TransformationStep() = default;

	glm::mat4 getMatrix() const;

	virtual bool animate() = 0;

protected:
	glm::mat4 m_matrix;

	virtual void updateMatrix() = 0;
};
