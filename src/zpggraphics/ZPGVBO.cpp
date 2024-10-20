#include "ZPGVBO.h"

// --- public ------------------------------------------------------------------
ZPGVBO::ZPGVBO(const size_t t_size, const float* t_data) {
	glGenBuffers(1, &this->m_VBOID);
	this->bind();
	glBufferData(GL_ARRAY_BUFFER, t_size, t_data, GL_STATIC_DRAW);
}

ZPGVBO::ZPGVBO(const std::vector<float>& t_data)
	: ZPGVBO(t_data.size() * sizeof(float), t_data.data()) { }

ZPGVBO::~ZPGVBO() {
	glDeleteBuffers(1, &this->m_VBOID);
}
void ZPGVBO::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBOID);
}

void ZPGVBO::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
