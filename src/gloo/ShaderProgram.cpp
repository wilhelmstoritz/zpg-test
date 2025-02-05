#include "ShaderProgram.h"
#include "Config.h"
#include "ModelLightEmitting.h"

// glm
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// --- public ------------------------------------------------------------------
ShaderProgram::ShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader)
	: m_name(t_name) {
	this->m_ID = glCreateProgram();
	this->linkProgram(t_vertexShader, t_fragmentShader);

	this->m_ssboLights = 0;

	// to prevent visual studio warnings; value(s) will be set later
	this->m_ssboID = 0;
}

ShaderProgram::ShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader)
	: ShaderProgram("@!#?@!", t_vertexShader, t_fragmentShader) { }

ShaderProgram::ShaderProgram(const std::string& t_name, const char* t_vertexShaderSourceFilename, const char* t_fragmentShaderSourceFilename)
	: m_name(t_name), ShaderLoader(t_vertexShaderSourceFilename, t_fragmentShaderSourceFilename, &this->shaderProgramID) { // ShaderLoader constructor needs a ID variable address, so we set it to itself
	this->m_ssboLights = 0;

	// to prevent visual studio warnings; value(s) will be set later
	this->m_ssboID = 0;
}

ShaderProgram::ShaderProgram(const char* t_vertexShaderSourceFilename, const char* t_fragmentShaderSourceFilename)
	: ShaderProgram("@!#?@!", t_vertexShaderSourceFilename, t_fragmentShaderSourceFilename) {
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(this->m_ID);
}

std::string ShaderProgram::getName() { return this->m_name; }

/* debugging purposes only
GLuint ShaderProgram::getID() const { return this->m_ID; }*/

void ShaderProgram::use() const {
	glUseProgram(this->m_ID);
}

template <>
void ShaderProgram::setUniform<glm::mat3>(const GLchar* t_name, const glm::mat3& t_matrix) const {
	GLint uniformLocation = glGetUniformLocation(this->m_ID, t_name);
	if (uniformLocation != -1) { // uniform matrix name exists -> location returned
		//printf("[shader program] id %d : set uniform mat3 '%s'\n", this->m_ID, t_name);

		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(t_matrix));
	}
}

template <>
void ShaderProgram::setUniform<glm::mat4>(const GLchar* t_name, const glm::mat4& t_matrix) const {
	GLint uniformLocation = glGetUniformLocation(this->m_ID, t_name);
	if (uniformLocation != -1) { // uniform matrix name exists -> location returned
		//printf("[shader program] id %d : set uniform mat4 '%s'\n", this->m_ID, t_name);

		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(t_matrix));
	}
}

template <>
void ShaderProgram::setUniform<glm::vec3>(const GLchar* t_name, const glm::vec3& t_vector) const {
	GLint uniformLocation = glGetUniformLocation(this->m_ID, t_name);
	if (uniformLocation != -1) { // uniform vector name exists -> location returned
		//printf("[shader program] id %d : set uniform vec3 '%s'\n", this->m_ID, t_name);

		glUniform3fv(uniformLocation, 1, glm::value_ptr(t_vector));
	}
}

template <>
void ShaderProgram::setUniform<float>(const GLchar* t_name, const float& t_value) const {
	GLint uniformLocation = glGetUniformLocation(this->m_ID, t_name);
	if (uniformLocation != -1) { // uniform float name exists -> location returned
		//printf("[shader program] id %d : set uniform float '%s'\n", this->m_ID, t_name);

		glUniform1f(uniformLocation, t_value);
	}
}

template <>
void ShaderProgram::setUniform<int>(const GLchar* t_name, const int& t_value) const {
	GLint uniformLocation = glGetUniformLocation(this->m_ID, t_name);
	if (uniformLocation != -1) { // uniform float name exists -> location returned
		//printf("[shader program] id %d : set uniform int '%s'\n", this->m_ID, t_name);

		glUniform1i(uniformLocation, t_value);
	}
}

/* debugging purposes only; template specialization is used in production
template <>
void ShaderProgram::follow<Camera>() {
//void ShaderProgram::follow<Camera>(void* t_anything) { // debugging purposes only
	/ *if (this->Observer<Camera>::needsUpdate())
		printf("[shader program] id %d : follow camera\n", this->m_ID);* /

	this->Observer<Camera>::processAllSubjects();
}

template <>
void ShaderProgram::follow<Light>() {
//void ShaderProgram::follow<Light>(void* t_anything) { // debugging purposes only
	/ *if (this->Observer<Light>::needsUpdate())
		printf("[shader program] id %d : follow light\n", this->m_ID);* /

	this->Observer<Light>::processAllSubjects();
}*/

// --- protected ---------------------------------------------------------------
void ShaderProgram::processSubject(Camera* t_camera) {
	//printf("[shader program] id %d process subject : camera name '%s'\n", this->m_ID, t_camera->getName().c_str());

	this->setUniform("eyePosition",      t_camera->getEye());
	this->setUniform("viewMatrix",       t_camera->getView());
	this->setUniform("projectionMatrix", t_camera->getProjection());
}

void ShaderProgram::processSubject(Light* t_light) {
	//printf("[shader program] id %d process subject : light name '%s'\n", this->m_ID, t_light->getName().c_str());

	// deal with the observer subjects
	t_light->follow<Camera>();
	t_light->follow<ModelLightEmitting>();

	// light properties
	/* replaced by SSBO implementation
	std::string indexedLightName = this->getIndexedName("lights", t_light->getID());

	this->setUniform((indexedLightName + ".lightType").c_str(), t_light->getLight().type);

	this->setUniform((indexedLightName + ".lightPosition").c_str(), t_light->getLight().position);
	this->setUniform((indexedLightName + ".lightDirection").c_str(), t_light->getLight().direction);
	this->setUniform((indexedLightName + ".spotCutoff").c_str(), t_light->getLight().spotCutoff); // value of cos(radians)

	// colors
	this->setUniform((indexedLightName + ".diffuseColor").c_str(), t_light->getLight().diffuseColor);
	this->setUniform((indexedLightName + ".specularColor").c_str(), t_light->getLight().specularColor);

	// attenuation coefficients
	this->setUniform((indexedLightName + ".attenuation").c_str(), t_light->getLight().attenuation); */

	// SSBO implementation; set/update light data in shader storage buffer object
	this->setSSBO(t_light);

	// light properties; single color shader
	//this->setUniform("lightColor", glm::vec3(1.f, 1.f, 1.f)); // hardcoded for now
	this->setUniform("lightIntensity", 1.f); // hardcoded for now

	// common properties
	this->setUniform("numLights", t_light->getNumLights());
	this->setUniform("mode", static_cast<int>(shaderModeE::ALL_COMPONENTS)); // 0 = all components, 1 = ambient only, 2 = diffuse only, 3 = specular only

	this->setUniform("ambientColor", glm::vec3(.03f, .03f, .03f)); // hardcoded for now

	// material properties; hardcoded for now
	this->setUniform("kAmbient", 1.f);
	this->setUniform("kDiffuse", 1.f);
	this->setUniform("kSpecular", 1.f);
	this->setUniform("kShininess", 32.f);
}

// --- private -----------------------------------------------------------------
void ShaderProgram::linkProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader) {
	glAttachShader(this->m_ID, t_vertexShader.getID());
	glAttachShader(this->m_ID, t_fragmentShader.getID());
	glLinkProgram(this->m_ID);

	// check for shader program compilation and linking errors
	GLint status;
	glGetProgramiv(this->m_ID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(this->m_ID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->m_ID, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "error >> program linking failed: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void ShaderProgram::setSSBO(Light* t_light) {
	size_t ssboLights = t_light->getNumLights();

	if (ssboLights < this->m_ssboLights) {
		// light deleted; whole new buffer
		glDeleteBuffers(1, &this->m_ssboID); // delete old buffer

		this->createSSBO(ssboLights); // create new buffer

		this->m_ssboLights = ssboLights;
	} else if (ssboLights > this->m_ssboLights) {
		// light added; increase buffer and copy old data
		GLuint ssboID = this->m_ssboID;

		this->createSSBO(ssboLights); // create new buffer

		glBindBuffer(GL_COPY_READ_BUFFER, ssboID); // bind old buffer
		glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_SHADER_STORAGE_BUFFER, 0, 0, this->m_ssboLights * sizeof(Light::lightT)); // copy old data to new buffer
		glBindBuffer(GL_COPY_READ_BUFFER, 0); // unbind old buffer
		glDeleteBuffers(1, &ssboID); // delete old buffer

		this->m_ssboLights = ssboLights;
	}

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->m_ssboID);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, this->m_ssboID); // binding point 0; corresponds to the binding in the shader
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, t_light->getID() * sizeof(Light::lightT), sizeof(Light::lightT), &t_light->getLight());
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind buffer
}

void ShaderProgram::createSSBO(size_t t_size) {
	glGenBuffers(1, &this->m_ssboID); // create new buffer
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->m_ssboID); // bind new buffer
	glBufferData(GL_SHADER_STORAGE_BUFFER, t_size * sizeof(Light::lightT), NULL, GL_DYNAMIC_DRAW); // allocate memory for the new buffer
	//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, this->m_ssboID); // binding point 0; corresponds to the binding in the shader
}

std::string ShaderProgram::getIndexedName(const char* t_name, const int t_index) {
	return std::string(t_name) + "[" + std::to_string(t_index) + "]";
}
