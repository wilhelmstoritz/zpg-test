#pragma once

// GLEW
#include <GL/glew.h>

// standard C++ libraries
#include <string>

class MyShader {
public:
	virtual ~MyShader() = 0; // pure virtual destructor ensure that the class cannot be instantiated

	GLuint getShaderID() const;

protected:
	GLuint m_shaderID;

	MyShader(GLenum t_shaderType, const char* t_source);
	MyShader(GLenum t_shaderType, const std::string& t_source);

	virtual void compileShader(const char* t_source);
};
