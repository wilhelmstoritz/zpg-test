#include "IBO.h"

// --- public ------------------------------------------------------------------
IBO::IBO(const size_t t_size, const float* t_data) {
	glGenBuffers(1, &this->m_ID);
	this->bind();
	glBufferData(GL_ARRAY_BUFFER, t_size, t_data, GL_STATIC_DRAW);
}

IBO::IBO(const std::vector<float>& t_data)
	: IBO(t_data.size() * sizeof(float), t_data.data()) {
}

IBO::~IBO() {
	glDeleteBuffers(1, &this->m_ID);
}
void IBO::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
}

void IBO::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
