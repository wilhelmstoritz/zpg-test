#pragma once

// glew
#include <GL/glew.h>

// standard c++ libraries
#include <vector>

class IBO {
public:
	IBO(const size_t t_size, const unsigned int* t_data);
	IBO(const std::vector<unsigned int>& t_data);
	~IBO();

	void bind() const;
	void unbind() const;

private:
	GLuint m_ID = 0;
};
