#pragma once

// include GLM
#include <glm/mat4x4.hpp> // glm::mat4

// include the standard C++ headers
#include <vector>

class Transformation {
public:
	Transformation();

	void addTransformation(glm::mat4 t_transformation);
	glm::mat4* getTransformation();

private:
	std::vector<glm::mat4> m_transformations;
	glm::mat4 m_transformation;
};
