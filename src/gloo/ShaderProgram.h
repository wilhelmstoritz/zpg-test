#pragma once

#include "VertexShader.h"
#include "FragmentShader.h"

// include GLM
#include <glm/mat4x4.hpp> // glm::mat4

class Camera; // forward declaration due to cross reference

class ShaderProgram {
public:
	//ShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader, Camera* t_camera);
	ShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader);
	~ShaderProgram();

	/* for debugging purposes
	GLuint getProgramID() const;
	*/
	void use() const;
	void transform(const GLchar* t_matrixName, glm::mat4 t_value) const;
	void followCamera(Camera* t_camera) const;

private:
	GLuint m_programID;
	//Camera* m_camera;

	void linkProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader);
};
