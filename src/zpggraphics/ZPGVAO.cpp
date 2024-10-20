#include "ZPGVAO.h"

// --- public ------------------------------------------------------------------
ZPGVAO::ZPGVAO() {
	glGenVertexArrays(1, &this->m_VAOID);
	this->bind();
}

ZPGVAO::~ZPGVAO() {
	glDeleteVertexArrays(1, &this->m_VAOID);
}

void ZPGVAO::addBuffer(const ZPGVBO& t_VBO, GLuint t_index, GLint t_size, GLsizei t_stride, const void* t_pointer) {
	t_VBO.bind();
	glEnableVertexAttribArray(t_index);
	glVertexAttribPointer(t_index, t_size, GL_FLOAT, GL_FALSE, t_stride, t_pointer);
}

void ZPGVAO::bind() {
	glBindVertexArray(this->m_VAOID);
}

void ZPGVAO::unbind() {
	glBindVertexArray(0);
}
