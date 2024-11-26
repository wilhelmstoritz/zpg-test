#pragma once

#include "VertexShader.h"
#include "FragmentShader.h"
#include "Camera.h"
#include "Light.h"
#include "Observer.h"
// 3rd party
#include "ShaderLoader.h"

// include GLM
#include <glm/mat4x4.hpp> // glm::mat4

class ShaderProgram : public Observer<Camera>, public Observer<Light>, public ShaderLoader {
public:
	ShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader);
	ShaderProgram(const char* t_vertexShaderSourceFilename, const char* t_fragmentShaderSourceFilename);
	~ShaderProgram();

	/* for debugging purposes
	GLuint getProgramID() const;
	*/

	void use() const;

	//void setUniform(const GLchar* t_name, const glm::mat3& t_matrix) const;
	template<typename T>
	void setUniform(const GLchar* t_name, const T& t_value) const;

	void followCamera();
	void followLight();
	//void followLight(const glm::mat4& t_modelMatrix); // debugging purposes only

	//void deleteShader(); // ShaderLoader has this method; apply only to objects created with ShaderLoader; 2do: make it common for all ShaderPrograms

protected:
	virtual void processSubject(Camera* t_camera) override;
	virtual void processSubject(Light* t_light) override;

private:
	//GLuint m_shaderProgramID;
	GLuint& m_shaderProgramID = this->shaderProgramID; // adapted to the need to use ShaderLoader

	void linkProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader);

	std::string getIndexedName(const char* t_name, const int t_index);
};
