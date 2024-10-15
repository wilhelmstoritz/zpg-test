#pragma once

// GLEW
#include <GL/glew.h>

// standard C++ libraries
#include <vector>

class MyVBO {
public:
	MyVBO(const size_t t_size, const float* t_data);
	MyVBO(const std::vector<float>& t_data);
	~MyVBO();

	void bind() const;
	void unbind() const;

private:
	GLuint m_VBOID = 0;
};
