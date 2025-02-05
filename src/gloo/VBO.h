#pragma once

// glew
#include <GL/glew.h>

// glm
#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4

// standard c++ libraries
#include <vector>

class VBO {
public:
	VBO(const size_t t_size, const float* t_data);
	VBO(const std::vector<float>& t_data);
	~VBO();

	void bind() const;
	void unbind() const;

	void transform(glm::mat4 t_vertexTransformation);
	void transform(glm::mat4 t_vertexTransformation, glm::mat4 t_normalTransformation);
	void transform(float t_scale, float t_rotationXdegrees, float t_rotationYdegrees, float t_rotationZdegrees, glm::vec3 t_position,
		bool t_withNormals);

private:
	GLuint m_ID;
};
