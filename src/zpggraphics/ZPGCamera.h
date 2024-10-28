#pragma once

// include GLM
#include <glm/mat4x4.hpp> // glm::mat4

//class ZPGShaderProgram; // forward declaration due to cross reference

class ZPGCamera {
public:
	//ZPGCamera(ZPGShaderProgram* t_shaderProgram);
	ZPGCamera();

	glm::mat4 getView(void);
	glm::mat4 getProjection(void);

	void moveCamera(float t_distance);
	void strafeCamera(float t_distance);
	void rotateCamera(float t_degreesH, float t_degreesV);

private:
	//ZPGShaderProgram* m_shaderProgram;

	glm::vec3 m_eye;
	glm::vec3 m_direction;
	glm::vec3 m_up;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	void calculateView();
};
