#include "VAO.h"

// --- public ------------------------------------------------------------------
VAO::VAO() {
	glGenVertexArrays(1, &this->m_ID);
	this->bind();
}

VAO::~VAO() {
	glDeleteVertexArrays(1, &this->m_ID);
}

void VAO::addBuffer(const VBO& t_vbo, GLuint t_index, GLint t_size, GLsizei t_stride, const void* t_pointer) {
	t_vbo.bind();
	glEnableVertexAttribArray(t_index);
	glVertexAttribPointer(t_index, t_size, GL_FLOAT, GL_FALSE, t_stride, t_pointer);
}

void VAO::addBuffer(const VBO& t_vbo, const std::vector<bufferInfoT>& t_bufferInfoList) {
	for (const auto& bufferInfo : t_bufferInfoList)
		this->addBuffer(t_vbo, bufferInfo.index, bufferInfo.size, bufferInfo.stride, bufferInfo.pointer);
}

void VAO::bind()   { glBindVertexArray(this->m_ID); }
void VAO::unbind() { glBindVertexArray(0); }
