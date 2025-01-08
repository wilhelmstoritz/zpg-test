#pragma once

#include "ModelLightEmitting.h"
#include "DeltaTime.h"

class ModelFirefly : public ModelLightEmitting {
public:
	ModelFirefly(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count);
	ModelFirefly(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao,             GLint t_first, GLsizei t_count);
	ModelFirefly(ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count);
	ModelFirefly(ShaderProgram* t_shaderProgram, VAO* t_vao,             GLint t_first, GLsizei t_count);

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
