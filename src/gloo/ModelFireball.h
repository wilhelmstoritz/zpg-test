#pragma once

#include "Model.h"
#include "DeltaTime.h"

class ModelFireball : public Model {
public:
	ModelFireball(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count);

	virtual bool animate() override;

private:
	glm::vec3 m_diffuseColorTarget;
	float m_kDiffuseTarget; // target diffuse reflection coefficient

	float m_transitionTimeColor;
	float m_transitionTimeIntensity;
	float m_elapsedTimeColor;
	float m_elapsedTimeIntensity;

	DeltaTime m_deltaTime;

	glm::vec3 generateRandomColor() const;
};
