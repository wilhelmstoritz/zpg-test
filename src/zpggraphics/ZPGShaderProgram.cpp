#include "ZPGShaderProgram.h"
#include "ZPGCamera.h"

// include GLM
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// --- public ------------------------------------------------------------------
/*
ZPGShaderProgram::ZPGShaderProgram(const ZPGShader& t_vertexShader, const ZPGShader& t_fragmentShader, ZPGCamera* t_camera) {
	this->m_programID = glCreateProgram();
	this->linkProgram(t_vertexShader, t_fragmentShader);

	this->m_camera = t_camera;
}

ZPGShaderProgram::ZPGShaderProgram(const ZPGShader& t_vertexShader, const ZPGShader& t_fragmentShader)
	: ZPGShaderProgram(t_vertexShader, t_fragmentShader, new ZPGCamera()) {
}
*/

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

void ZPGShaderProgram::transform(const GLchar* t_matrixName, glm::mat4 t_value) const {
	GLint matrixID = glGetUniformLocation(this->m_programID, t_matrixName);
	if (matrixID != -1) { // matrixName exists -> matrixID returned
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(t_value));
	}
}

void ZPGShaderProgram::followCamera(ZPGCamera* t_camera) const {
	this->transform("viewMatrix", t_camera->getView());
	this->transform("projectionMatrix", t_camera->getProjection());
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
