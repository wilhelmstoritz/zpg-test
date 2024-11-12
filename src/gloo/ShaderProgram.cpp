#include "ShaderProgram.h"

// include GLM
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// --- public ------------------------------------------------------------------
ShaderProgram::ShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader, Camera* t_camera) {
	this->m_programID = glCreateProgram();
	this->linkProgram(t_vertexShader, t_fragmentShader);
}

ShaderProgram::ShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader)
	: ShaderProgram(t_vertexShader, t_fragmentShader, nullptr) { // !!! DEFAULT CAMERA SHOULD BE HERE
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(this->m_programID);
}

/* for debugging purposes
GLuint MyShaderProgram::getProgramID() const {
	return this->mProgramID;
}
*/

void ShaderProgram::use() const {
	glUseProgram(this->m_programID);
}

template<>
void ShaderProgram::setUniform<glm::mat3>(const GLchar* t_name, const glm::mat3& t_matrix) const {
	GLint uniformLocation = glGetUniformLocation(this->m_programID, t_name);
	if (uniformLocation != -1) { // uniform matrix name exists -> location returned
		//printf("[shader program] id %d : set uniform mat3 '%s'\n", this->m_programID, t_name);

		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(t_matrix));
	}
}

template<>
void ShaderProgram::setUniform<glm::mat4>(const GLchar* t_name, const glm::mat4& t_matrix) const {
	GLint uniformLocation = glGetUniformLocation(this->m_programID, t_name);
	if (uniformLocation != -1) { // uniform matrix name exists -> location returned
		//printf("[shader program] id %d : set uniform mat4 '%s'\n", this->m_programID, t_name);

		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(t_matrix));
	}
}

template<>
void ShaderProgram::setUniform<glm::vec3>(const GLchar* t_name, const glm::vec3& t_vector) const {
	GLint uniformLocation = glGetUniformLocation(this->m_programID, t_name);
	if (uniformLocation != -1) { // uniform vector name exists -> location returned
		//printf("[shader program] id %d : set uniform vec3 '%s'\n", this->m_programID, t_name);

		glUniform3fv(uniformLocation, 1, glm::value_ptr(t_vector));
	}
}

template<>
void ShaderProgram::setUniform<float>(const GLchar* t_name, const float& t_value) const {
	GLint uniformLocation = glGetUniformLocation(this->m_programID, t_name);
	if (uniformLocation != -1) { // uniform float name exists -> location returned
		//printf("[shader program] id %d : set uniform float '%s'\n", this->m_programID, t_name);

		glUniform1f(uniformLocation, t_value);
	}
}

/*
void ShaderProgram::setUniform(const GLchar* t_matrixName, const glm::mat4& t_matrix) const {
	GLint matrixID = glGetUniformLocation(this->m_programID, t_matrixName);
	if (matrixID != -1) { // matrixName exists -> matrixID returned
		//printf("[shader program] id %d : set uniform '%s'\n", this->m_programID, t_matrixName);

		glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(t_matrix));
	}
}
*/

void ShaderProgram::followCamera() {
	if (this->Observer<Camera>::needsUpdate()) printf("[shader program] id %d : follow camera\n", this->m_programID);

	this->Observer<Camera>::processAllSubjects();
}

void ShaderProgram::followLight(const glm::mat4& t_modelMatrix) {
	if (this->Observer<Light>::needsUpdate()) {
		printf("[shader program] id %d : follow light\n", this->m_programID);

		// normal matrix as the inverse transpose of the model matrix; 3x3 matrix
		//glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(t_modelMatrix)));
		this->m_normalMatrix = glm::transpose(glm::inverse(glm::mat3(t_modelMatrix)));
	}

	this->Observer<Light>::processAllSubjects();
}

// --- protected ---------------------------------------------------------------
void ShaderProgram::processSubject(Camera* t_camera) {
	printf("[shader program] id %d process subject : camera\n", this->m_programID);

	this->setUniform("viewMatrix", *t_camera->getView());
	this->setUniform("projectionMatrix", *t_camera->getProjection());
}

void ShaderProgram::processSubject(Light* t_light) {
	printf("[shader program] id %d process subject : light\n", this->m_programID);

	this->setUniform("normalMatrix", this->m_normalMatrix);

	this->setUniform("lightPosition", *t_light->getPosition());
	this->setUniform("lightColor", *t_light->getColor());
	this->setUniform("lightIntensity", t_light->getIntensity());
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
