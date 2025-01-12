#pragma once

#include "ModelFireball.h"

class ModelFireballBouncing : public ModelFireball {
public:
	ModelFireballBouncing(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count);
	ModelFireballBouncing(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao,             GLint t_first, GLsizei t_count);
	ModelFireballBouncing(ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count);
	ModelFireballBouncing(ShaderProgram* t_shaderProgram, VAO* t_vao,             GLint t_first, GLsizei t_count);

	virtual void animateContinuous() override;

private:
	glm::vec3 randomPointOnSkybox();
};
