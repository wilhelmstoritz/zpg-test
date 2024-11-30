#include "ShaderProgram.h"

// include GLM
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// --- public ------------------------------------------------------------------
ShaderProgram::ShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader) {
	this->m_shaderProgramID = glCreateProgram();
	this->linkProgram(t_vertexShader, t_fragmentShader);

	// set up shader storage buffer object
	glGenBuffers(1, &this->m_ssboID);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->m_ssboID);
	//glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Light::lightT) * MAX_LIGHTS, NULL, GL_DYNAMIC_DRAW);
	//glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Light::lightT) * MAX_LIGHTS, this->m_lights.data(), GL_DYNAMIC_DRAW);
	//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, this->m_ssboID); // binding point 0; corresponds to the binding in the shader
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind
}

ShaderProgram::ShaderProgram(const char* t_vertexShaderSourceFilename, const char* t_fragmentShaderSourceFilename)
	: ShaderLoader(t_vertexShaderSourceFilename, t_fragmentShaderSourceFilename, &this->shaderProgramID) { } // ShaderLoader constructor needs a ID variable address, so we set it to itself

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(this->m_shaderProgramID);
}

/* debugging purposes only
GLuint MyShaderProgram::getProgramID() const {
	return this->mProgramID;
}
*/

void ShaderProgram::use() const {
	glUseProgram(this->m_shaderProgramID);
}

/*
void ShaderProgram::setUniform(const GLchar* t_name, const glm::mat3& t_matrix) const {
	GLint uniformLocation = glGetUniformLocation(this->m_shaderProgramID, t_name);
	if (uniformLocation != -1) { // uniform matrix name exists -> location returned
		//printf("[shader program] id %d : set uniform mat3 '%s'\n", this->m_shaderProgramID, t_name);

		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(t_matrix));
	}
}
*/

template<>
void ShaderProgram::setUniform<glm::mat3>(const GLchar* t_name, const glm::mat3& t_matrix) const {
	GLint uniformLocation = glGetUniformLocation(this->m_shaderProgramID, t_name);
	if (uniformLocation != -1) { // uniform matrix name exists -> location returned
		//printf("[shader program] id %d : set uniform mat3 '%s'\n", this->m_shaderProgramID, t_name);

		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(t_matrix));
	}
}

template<>
void ShaderProgram::setUniform<glm::mat4>(const GLchar* t_name, const glm::mat4& t_matrix) const {
	GLint uniformLocation = glGetUniformLocation(this->m_shaderProgramID, t_name);
	if (uniformLocation != -1) { // uniform matrix name exists -> location returned
		//printf("[shader program] id %d : set uniform mat4 '%s'\n", this->m_shaderProgramID, t_name);

		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(t_matrix));
	}
}

template<>
void ShaderProgram::setUniform<glm::vec3>(const GLchar* t_name, const glm::vec3& t_vector) const {
	GLint uniformLocation = glGetUniformLocation(this->m_shaderProgramID, t_name);
	if (uniformLocation != -1) { // uniform vector name exists -> location returned
		//printf("[shader program] id %d : set uniform vec3 '%s'\n", this->m_shaderProgramID, t_name);

		glUniform3fv(uniformLocation, 1, glm::value_ptr(t_vector));
	}
}

template<>
void ShaderProgram::setUniform<float>(const GLchar* t_name, const float& t_value) const {
	GLint uniformLocation = glGetUniformLocation(this->m_shaderProgramID, t_name);
	if (uniformLocation != -1) { // uniform float name exists -> location returned
		//printf("[shader program] id %d : set uniform float '%s'\n", this->m_shaderProgramID, t_name);

		glUniform1f(uniformLocation, t_value);
	}
}

template<>
void ShaderProgram::setUniform<int>(const GLchar* t_name, const int& t_value) const {
	GLint uniformLocation = glGetUniformLocation(this->m_shaderProgramID, t_name);
	if (uniformLocation != -1) { // uniform float name exists -> location returned
		//printf("[shader program] id %d : set uniform int '%s'\n", this->m_shaderProgramID, t_name);

		glUniform1i(uniformLocation, t_value);
	}
}

void ShaderProgram::followCamera() {
	if (this->Observer<Camera>::needsUpdate())
		//printf("[shader program] id %d : follow camera\n", this->m_shaderProgramID);

	this->Observer<Camera>::processAllSubjects();
}

void ShaderProgram::followLight() {
//void ShaderProgram::followLight(const glm::mat4& t_modelMatrix) { // debugging purposes only
	if (this->Observer<Light>::needsUpdate())
		//printf("[shader program] id %d : follow light\n", this->m_shaderProgramID);

	this->Observer<Light>::processAllSubjects();
}

// --- protected ---------------------------------------------------------------
void ShaderProgram::processSubject(Camera* t_camera) {
	//printf("[shader program] id %d process subject : camera name '%s'\n", this->m_shaderProgramID, t_camera->getName().c_str());

	this->setUniform("eyePosition", *t_camera->getEye());
	this->setUniform("viewMatrix", *t_camera->getView());
	this->setUniform("projectionMatrix", *t_camera->getProjection());
}

void ShaderProgram::processSubject(Light* t_light) {
	//printf("[shader program] id %d process subject : light name '%s'\n", this->m_shaderProgramID, t_light->getName().c_str());

	// light properties
	std::string indexedLightName = this->getIndexedName("lights", t_light->getID());

	this->setUniform((indexedLightName + ".lightType").c_str(), t_light->getLight().lightType);

	this->setUniform((indexedLightName + ".lightPosition").c_str(), t_light->getLight().lightPosition);
	this->setUniform((indexedLightName + ".lightDirection").c_str(), t_light->getLight().lightDirection);
	this->setUniform((indexedLightName + ".spotCutoff").c_str(), t_light->getLight().spotCutoff); // value of cos(radians)

	// colors
	this->setUniform((indexedLightName + ".diffuseColor").c_str(), t_light->getLight().diffuseColor);
	this->setUniform((indexedLightName + ".specularColor").c_str(), t_light->getLight().specularColor);

	//this->setUniform("lightColor", glm::vec3(1.f, 1.f, 1.f)); // single color shader; hardcoded for now
	this->setUniform("lightIntensity", 1.f); // single color shader; hardcoded for now

	// attenuation coefficients
	this->setUniform((indexedLightName + ".attenuation").c_str(), t_light->getLight().attenuation);

	// common properties
	this->setUniform("numLights", t_light->getNumLights());
	this->setUniform("mode", 0); // 0 = all components, 1 = ambient only, 2 = diffuse only, 3 = specular only

	this->setUniform("ambientColor", glm::vec3(.1f, .1f, .1f)); // hardcoded for now

	// material properties; hardcoded for now
	this->setUniform("kAmbient", 1.f);
	this->setUniform("kDiffuse", 1.f);
	this->setUniform("kSpecular", 1.f);
	this->setUniform("kShininess", 32.f);
}

// --- private -----------------------------------------------------------------
void ShaderProgram::linkProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader) {
	glAttachShader(this->m_shaderProgramID, t_vertexShader.getShaderID());
	glAttachShader(this->m_shaderProgramID, t_fragmentShader.getShaderID());
	glLinkProgram(this->m_shaderProgramID);

	// check for shader program compilation and linking errors
	GLint status;
	glGetProgramiv(this->m_shaderProgramID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(this->m_shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->m_shaderProgramID, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "error >> program linking failed: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

std::string ShaderProgram::getIndexedName(const char* t_name, const int t_index) {
	return std::string(t_name) + "[" + std::to_string(t_index) + "]";
}
