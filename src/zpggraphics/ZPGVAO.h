#pragma once

#include "ZPGVBO.h"

class ZPGVAO {
public:
	ZPGVAO();
	~ZPGVAO();

	void addBuffer(const ZPGVBO& t_VBO, GLuint t_index, GLint t_size, GLsizei t_stride, const void* t_pointer);
	void bind();
	void unbind();

private:
	GLuint m_VAOID = 0;
};
