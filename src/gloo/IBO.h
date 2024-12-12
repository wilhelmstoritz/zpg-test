#pragma once

// include GLEW
#include <GL/glew.h>

// standard C++ libraries
#include <vector>

class IBO {
public:
	IBO(const size_t t_size, const float* t_data);
	IBO(const std::vector<float>& t_data);
	~IBO();

	void bind() const;
	void unbind() const;

private:
	GLuint m_ID = 0;
};
