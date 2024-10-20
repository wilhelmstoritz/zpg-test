#pragma once

// GLEW
#include <GL/glew.h>

// standard C++ libraries
#include <vector>

class ZPGVBO {
public:
	ZPGVBO(const size_t t_size, const float* t_data);
	ZPGVBO(const std::vector<float>& t_data);
	~ZPGVBO();

	void bind() const;
	void unbind() const;

private:
	GLuint m_VBOID = 0;
};
