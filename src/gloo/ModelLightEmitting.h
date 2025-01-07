#pragma once

#include "Model.h"

class ModelLightEmitting : public Model {
public:
	ModelLightEmitting(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count);

	virtual bool animate() override;
};
