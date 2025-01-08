#pragma once

#include "Model.h"
#include "ObserverSubject.h"

class ModelLightEmitting : public Model, public ObserverSubject<ModelLightEmitting> {
public:
	ModelLightEmitting(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count);
	ModelLightEmitting(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao,             GLint t_first, GLsizei t_count);
	ModelLightEmitting(ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count);
	ModelLightEmitting(ShaderProgram* t_shaderProgram, VAO* t_vao,             GLint t_first, GLsizei t_count);

	glm::vec3 getSpecularColor();
	float getKSpecular();

	void setSpecularColor(const glm::vec3& t_specularColor);
	void setKSpecular(float t_kSpecular);

	virtual bool animate() override;

protected:
	glm::vec3 m_specularColor;
	float m_kSpecular; // specular reflection coefficient

	virtual void postUpdate() override;
};
