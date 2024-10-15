#include "MyShader.h"

// --- public ------------------------------------------------------------------
MyShader::~MyShader() {
	glDeleteShader(this->m_shaderID);
}

GLuint MyShader::getShaderID() const {
	return this->m_shaderID;
}

// --- protected ---------------------------------------------------------------
MyShader::MyShader(GLenum t_shaderType, const char* t_source) {
	this->m_shaderID = glCreateShader(t_shaderType);
	this->compileShader(t_source);
}

MyShader::MyShader(GLenum t_shaderType, const std::string& t_source)
	: MyShader(t_shaderType, t_source.c_str()) { }

void MyShader::compileShader(const char* t_source) {
	glShaderSource(this->m_shaderID, 1, &t_source, NULL);
	glCompileShader(this->m_shaderID);

	// check for shader compilation errors
	GLint status;
	glGetShaderiv(this->m_shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(this->m_shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(this->m_shaderID, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "error >> shader compilation failed: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}
