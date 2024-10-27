#pragma once

// include GLM
#include <glm/mat4x4.hpp> // glm::mat4

class ZPGShaderProgram; // forward declaration due to cross reference

class ZPGCamera {
public:
	//ZPGCamera(ZPGShaderProgram* t_shaderProgram);
	ZPGCamera();

	glm::mat4 getCamera(void);

private:
	ZPGShaderProgram* m_shaderProgram;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
};
