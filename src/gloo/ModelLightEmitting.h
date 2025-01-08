#pragma once

#include "ObserverSubject.h"
#include "Model.h"

class ModelLightEmitting : public ObserverSubject<ModelLightEmitting>, public Model {
public:
	ModelLightEmitting(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count);
	ModelLightEmitting(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao,             GLint t_first, GLsizei t_count);
	ModelLightEmitting(ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count);
	ModelLightEmitting(ShaderProgram* t_shaderProgram, VAO* t_vao,             GLint t_first, GLsizei t_count);

	virtual bool animate() override;
};
