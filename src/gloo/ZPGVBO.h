#pragma once

// GLEW
#include <GL/glew.h>

// include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4

// standard C++ libraries
#include <vector>

class ZPGVBO {
public:
	ZPGVBO(const size_t t_size, const float* t_data);
	ZPGVBO(const std::vector<float>& t_data);
	~ZPGVBO();

	void bind() const;
	void unbind() const;

	void transform(glm::mat4 t_vertexTransformation);
	void transform(glm::mat4 t_vertexTransformation, glm::mat4 t_normalTransformation);
	void transform(glm::vec3 t_position, float t_scale,
		float t_rotationXdegrees, float t_rotationYdegrees, float t_rotationZdegrees,
		bool t_withNormals);

private:
	GLuint m_VBOID = 0;
};
