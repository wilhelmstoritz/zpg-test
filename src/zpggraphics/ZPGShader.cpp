#include "ZPGShader.h"

// --- public ------------------------------------------------------------------
ZPGShader::~ZPGShader() {
	glDeleteShader(this->m_shaderID);
}

GLuint ZPGShader::getShaderID() const {
	return this->m_shaderID;
}

// --- protected ---------------------------------------------------------------
ZPGShader::ZPGShader(GLenum t_shaderType, const char* t_source) {
	this->m_shaderID = glCreateShader(t_shaderType);
	this->compileShader(t_source);
}

ZPGShader::ZPGShader(GLenum t_shaderType, const std::string& t_source)
	: ZPGShader(t_shaderType, t_source.c_str()) { }

void ZPGShader::compileShader(const char* t_source) {
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
