#include "ZPGShaderProgram.h"

// --- public ------------------------------------------------------------------
ZPGShaderProgram::ZPGShaderProgram(const ZPGShader& t_vertexShader, const ZPGShader& t_fragmentShader) {
	this->m_programID = glCreateProgram();
	this->linkProgram(t_vertexShader, t_fragmentShader);
}

ZPGShaderProgram::~ZPGShaderProgram() {
	glDeleteProgram(this->m_programID);
}

/* for debugging purposes
GLuint MyShaderProgram::getProgramID() const {
	return this->mProgramID;
}
*/

void ZPGShaderProgram::use() const {
	glUseProgram(this->m_programID);
}

// --- private -----------------------------------------------------------------
void ZPGShaderProgram::linkProgram(const ZPGShader& t_vertexShader, const ZPGShader& t_fragmentShader) {
	glAttachShader(this->m_programID, t_vertexShader.getShaderID());
	glAttachShader(this->m_programID, t_fragmentShader.getShaderID());
	glLinkProgram(this->m_programID);

	// check for shader program compilation and linking errors
	GLint status;
	glGetProgramiv(this->m_programID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(this->m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->m_programID, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "error >> program linking failed: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}
