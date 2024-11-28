#pragma once

#include "Model.h"
#include "DeltaTime.h"

class ModelFirefly : public Model {
public:
	ModelFirefly(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count);

	virtual bool animate() override;

private:
	glm::vec3 m_diffuseColorTarget;
	float m_kDiffuseTarget; // target diffuse reflection coefficient

	float m_elapsedTimeColor;
	float m_elapsedTimeColorIntensity;

	DeltaTime m_deltaTime;

	glm::vec3 generateRandomColor(const float t_min, const float t_max) const;
	float generateRandomTime(const float t_min, const float t_max) const;
};
