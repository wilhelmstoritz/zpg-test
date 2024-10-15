#include "MyVBO.h"

// --- public ------------------------------------------------------------------
MyVBO::MyVBO(const size_t t_size, const float* t_data) {
	glGenBuffers(1, &this->m_VBOID);
	this->bind();
	glBufferData(GL_ARRAY_BUFFER, t_size, t_data, GL_STATIC_DRAW);
}

MyVBO::MyVBO(const std::vector<float>& t_data)
	: MyVBO(t_data.size() * sizeof(float), t_data.data()) { }

MyVBO::~MyVBO() {
	glDeleteBuffers(1, &this->m_VBOID);
}
void MyVBO::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBOID);
}

void MyVBO::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
