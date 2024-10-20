#include "MyVAO.h"

// --- public ------------------------------------------------------------------
MyVAO::MyVAO() {
	glGenVertexArrays(1, &this->m_VAOID);
	this->bind();
}

MyVAO::~MyVAO() {
	glDeleteVertexArrays(1, &this->m_VAOID);
}

void MyVAO::addBuffer(const MyVBO& t_VBO, GLuint t_index, GLint t_size, GLsizei t_stride, const void* t_pointer) {
	t_VBO.bind();
	glEnableVertexAttribArray(t_index);
	glVertexAttribPointer(t_index, t_size, GL_FLOAT, GL_FALSE, t_stride, t_pointer);
}

void MyVAO::bind() {
	glBindVertexArray(this->m_VAOID);
}

void MyVAO::unbind() {
	glBindVertexArray(0);
}
