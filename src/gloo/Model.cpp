#include "Model.h"

// --- public ------------------------------------------------------------------
Model::Model(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: m_shaderProgram(t_shaderProgram), m_vao(t_vao), m_first(t_first), m_count(t_count), m_transformation() {
	// default values; hardcoded for now
	this->m_diffuseColor = glm::vec3(1.f); // default color is white
	this->m_kDiffuse = 1.f; // default diffuse reflection coefficient is 1

	this->updateAndNotify();
}

ShaderProgram* Model::getShaderProgram() { return this->m_shaderProgram; }
Transformation* Model::getTransformation() { return &this->m_transformation; }

glm::vec3 Model::getDiffuseColor() { return this->m_diffuseColor; }
float Model::getKDiffuse() { return this->m_kDiffuse; }

void Model::setDiffuseColor(const glm::vec3& t_diffuseColor) { this->m_diffuseColor = t_diffuseColor; }
void Model::setKDiffuse(float t_kDiffuse) { this->m_kDiffuse = t_kDiffuse; }

bool Model::animate() { return false; } // default implementation; no animation

void Model::draw() {
	this->m_shaderProgram->use();
	this->m_vao->bind();

	// update (solve the necessary transformations) and notify (if necessary)
	this->updateAndNotify();

	this->m_shaderProgram->setUniform("modelMatrix", this->m_transformation.getModelMatrix());
	this->m_shaderProgram->setUniform("normalMatrix", this->m_normalMatrix);

	this->m_shaderProgram->setUniform("lightColor", this->getDiffuseColor()); // single color shader

	this->m_shaderProgram->follow<Camera>();
	this->m_shaderProgram->follow<Light>();
	//this->m_shaderProgram->followLight(this->m_transformation.getTransformation()); // debugging purposes only

	// draw it
	glDrawArrays(GL_TRIANGLES, this->m_first, this->m_count);
}

// --- private -----------------------------------------------------------------
void Model::updateAndNotify() {
	this->animate(); // animate the model (in case it makes sense)
	this->m_transformation.animate(); // animate the transformation (in case it makes sense)

	if (this->m_transformation.hasChanged()) { // only in case the model matrix has changed
		// calculate the normal matrix; as the inverse transpose of the model matrix; 3x3 matrix
		this->m_normalMatrix = glm::transpose(glm::inverse(glm::mat3(this->m_transformation.getModelMatrix())));

		// notify the observers
		this->notifyObservers();

		this->m_transformation.clearChanged();
	}
}
