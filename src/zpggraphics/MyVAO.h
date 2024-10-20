#pragma once

#include "MyVBO.h"

class MyVAO {
public:
	MyVAO();
	~MyVAO();

	void addBuffer(const MyVBO& t_VBO, GLuint t_index, GLint t_size, GLsizei t_stride, const void* t_pointer);
	void bind();
	void unbind();

private:
	GLuint m_VAOID = 0;
};
