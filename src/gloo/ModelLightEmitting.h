#pragma once

#include "ObserverSubject.h"
#include "Model.h"

class ModelLightEmitting : public ObserverSubject<ModelLightEmitting>, public Model {
public:
	ModelLightEmitting(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count);

	virtual bool animate() override;
};
