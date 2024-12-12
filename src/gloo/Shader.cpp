#include "Shader.h"

// --- public ------------------------------------------------------------------
Shader::~Shader() {
	glDeleteShader(this->m_ID);
}

GLuint Shader::getID() const {
	return this->m_ID;
}

// --- protected ---------------------------------------------------------------
Shader::Shader(GLenum t_shaderType, const char* t_source) {
	this->m_ID = glCreateShader(t_shaderType);
	this->compileShader(t_source);
}

Shader::Shader(GLenum t_shaderType, const std::string& t_source)
	: Shader(t_shaderType, t_source.c_str()) { }

void Shader::compileShader(const char* t_source) {
	glShaderSource(this->m_ID, 1, &t_source, NULL);
	glCompileShader(this->m_ID);

	// check for shader compilation errors
	GLint status;
	glGetShaderiv(this->m_ID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(this->m_ID, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(this->m_ID, infoLogLength, NULL, strInfoLog);

		fprintf(stderr, "error >> shader compilation failed: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}
