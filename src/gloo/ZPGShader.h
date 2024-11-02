#pragma once

// GLEW
#include <GL/glew.h>

// standard C++ libraries
#include <string>

class ZPGShader {
public:
	virtual ~ZPGShader() = 0; // pure virtual destructor ensure that the class cannot be instantiated

	GLuint getShaderID() const;

protected:
	GLuint m_shaderID;

	ZPGShader(GLenum t_shaderType, const char* t_source);
	ZPGShader(GLenum t_shaderType, const std::string& t_source);

	virtual void compileShader(const char* t_source);
};
