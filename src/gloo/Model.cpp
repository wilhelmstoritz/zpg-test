#include "Model.h"

// --- public ------------------------------------------------------------------
Model::Model(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: m_shaderProgram(t_shaderProgram), m_vao(t_vao), m_first(t_first), m_count(t_count), m_transformation() { }

ShaderProgram* Model::getShaderProgram() { return this->m_shaderProgram; }
Transformation* Model::getTransformation() { return &this->m_transformation; }

void Model::draw() {
	this->m_shaderProgram->use();
	this->m_vao->bind();

	// solve (the necessary) transformations
	this->m_shaderProgram->setUniform("modelMatrix", this->m_transformation.getTransformation());
	this->m_shaderProgram->followCamera();

	// draw it
	glDrawArrays(GL_TRIANGLES, this->m_first, this->m_count);
}

// --- private -----------------------------------------------------------------
