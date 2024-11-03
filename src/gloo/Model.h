#pragma once

#include "VAO.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class Model {
public:
	Model(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count);

	ShaderProgram* getShaderProgram();
	Transformation* getTransformation();
	void draw();

private:
	ShaderProgram* m_shaderProgram;
	VAO* m_vao;
	GLint m_first;
	GLsizei m_count;

	Transformation m_transformation;
};
