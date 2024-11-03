#include "ShaderProgram.h"

// include GLM
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// --- public ------------------------------------------------------------------
ShaderProgram::ShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader, DefaultCamera* t_camera)
	: m_camera(t_camera), m_cameraUpdate(true) {
	this->m_programID = glCreateProgram();
	this->linkProgram(t_vertexShader, t_fragmentShader);
}

ShaderProgram::ShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader)
	: ShaderProgram(t_vertexShader, t_fragmentShader, DefaultCamera::getInstance()) {
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(this->m_programID);
}

// --- overrides base class implementation; begin
void ShaderProgram::update(DefaultCamera* t_camera) {
	//printf("shader program %d: update\n", this->m_programID);

	this->m_camera = t_camera;
	this->m_cameraUpdate = true;
}
// --- overrides base class implementation; end

/* for debugging purposes
GLuint MyShaderProgram::getProgramID() const {
	return this->mProgramID;
}
*/

void ShaderProgram::use() const {
	glUseProgram(this->m_programID);
}

void ShaderProgram::transform(const GLchar* t_matrixName, glm::mat4* t_value) const {
	GLint matrixID = glGetUniformLocation(this->m_programID, t_matrixName);
	if (matrixID != -1) { // matrixName exists -> matrixID returned
		//printf("shader program %d: transform '%s'\n", this->m_programID, t_matrixName);

		glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(*t_value));
	}
}

void ShaderProgram::followCamera() {
	if (this->m_camera != nullptr && this->m_cameraUpdate) {
		//printf("shader program %d: follow camera\n", this->m_programID);

		this->transform("viewMatrix", this->m_camera->getView());
		this->transform("projectionMatrix", this->m_camera->getProjection());

		this->m_cameraUpdate = false;
	}
}

// --- private -----------------------------------------------------------------
void ShaderProgram::linkProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader) {
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
