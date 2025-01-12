#pragma once

#include "VBO.h"

class VAO {
public:
	struct bufferInfoT {
		GLuint index;
		GLint size;
		GLsizei stride;
		const void* pointer;

		bufferInfoT(GLuint t_index, GLint t_size, GLsizei t_stride, const void* t_pointer)
			: index(t_index), size(t_size), stride(t_stride), pointer(t_pointer) { }
	};

	VAO();
	~VAO();

	void addBuffer(const VBO& t_vbo, GLuint t_index, GLint t_size, GLsizei t_stride, const void* t_pointer);
	void addBuffer(const VBO& t_vbo, const std::vector<bufferInfoT>& t_bufferInfoList);

	void bind();
	void unbind();

private:
	GLuint m_ID;
};
