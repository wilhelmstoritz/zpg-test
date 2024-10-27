#pragma once

// include GLM
#include <glm/mat4x4.hpp> // glm::mat4

class ZPGCamera {
public:
	ZPGCamera();

	glm::mat4 getCamera(void);

private:
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
};
