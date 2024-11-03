#pragma once

#include "VBO.h"

class VAO {
public:
	VAO();
	~VAO();

	void addBuffer(const VBO& t_vbo, GLuint t_index, GLint t_size, GLsizei t_stride, const void* t_pointer);
	void bind();
	void unbind();

private:
	GLuint m_vaoID = 0;
};
