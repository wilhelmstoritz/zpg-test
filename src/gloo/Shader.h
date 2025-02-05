#pragma once

// glew
#include <GL/glew.h>

// standard c++ libraries
#include <string>

class Shader {
public:
	virtual ~Shader() = 0; // pure virtual destructor ensure that the class cannot be instantiated

	GLuint getID() const;

protected:
	GLuint m_ID;

	Shader(GLenum t_shaderType, const char* t_source);
	Shader(GLenum t_shaderType, const std::string& t_source);

	virtual void compileShader(const char* t_source);
};
