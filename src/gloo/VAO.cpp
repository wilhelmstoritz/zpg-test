#include "VAO.h"

// --- public ------------------------------------------------------------------
VAO::VAO() {
	glGenVertexArrays(1, &this->m_vaoID);
	this->bind();
}

VAO::~VAO() {
	glDeleteVertexArrays(1, &this->m_vaoID);
}

void VAO::addBuffer(const VBO& t_vbo, GLuint t_index, GLint t_size, GLsizei t_stride, const void* t_pointer) {
	t_vbo.bind();
	glEnableVertexAttribArray(t_index);
	glVertexAttribPointer(t_index, t_size, GL_FLOAT, GL_FALSE, t_stride, t_pointer);
}

void VAO::bind() {
	glBindVertexArray(this->m_vaoID);
}

void VAO::unbind() {
	glBindVertexArray(0);
}
