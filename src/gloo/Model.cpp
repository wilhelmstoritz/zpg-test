#include "Model.h"

// --- public ------------------------------------------------------------------
Model::Model(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: m_shaderProgram(t_shaderProgram), m_vao(t_vao), m_first(t_first), m_count(t_count), m_transformation() {
	this->calculateNormalMatrix();
}

ShaderProgram* Model::getShaderProgram() { return this->m_shaderProgram; }
Transformation* Model::getTransformation() { return &this->m_transformation; }

void Model::draw() {
	this->m_shaderProgram->use();
	this->m_vao->bind();

	// solve (the necessary) transformations
	this->m_transformation.animate(); // animate the transformation
	this->calculateNormalMatrix(); // calculate normal matrix; only in case the model matrix has changed

	this->m_shaderProgram->setUniform("modelMatrix", this->m_transformation.getModelMatrix());
	this->m_shaderProgram->setUniform("normalMatrix", this->m_normalMatrix);

	this->m_shaderProgram->followCamera();
	this->m_shaderProgram->followLight();
	//this->m_shaderProgram->followLight(this->m_transformation.getTransformation()); // debugging purposes only

	// draw it
	glDrawArrays(GL_TRIANGLES, this->m_first, this->m_count);
}

// --- private -----------------------------------------------------------------
void Model::calculateNormalMatrix() {
	if (this->m_transformation.hasChanged()) {
		// normal matrix as the inverse transpose of the model matrix; 3x3 matrix
		this->m_normalMatrix = glm::transpose(glm::inverse(glm::mat3(this->m_transformation.getModelMatrix())));

		this->m_transformation.clearChanged();
	}
}
