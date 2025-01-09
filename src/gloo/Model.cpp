#include "Model.h"

// --- public ------------------------------------------------------------------
Model::Model(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count)
	: m_name(t_name), m_shaderProgram(t_shaderProgram), m_vao(t_vao), m_ibo(t_ibo), m_first(t_first), m_count(t_count), m_transformation() {
	// color and reflection coefficient
	this->m_diffuseColor = glm::vec3(1.f); // white
	this->m_kDiffuse = 1.f; // maximum reflection

	// to prevent visual studio warnings; value(s) will be set later
	this->m_textureID = 0; // first texture unit

	this->updateAndNotify();
}

Model::Model(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: Model(t_name, t_shaderProgram, t_vao, nullptr, t_first, t_count) { }

Model::Model(ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count)
	: Model("@!#?@!", t_shaderProgram, t_vao, t_ibo, t_first, t_count) { }

Model::Model(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: Model("@!#?@!", t_shaderProgram, t_vao, nullptr, t_first, t_count) { }

std::string Model::getName() { return this->m_name; }

ShaderProgram* Model::getShaderProgram() { return this->m_shaderProgram; }
Transformation* Model::getTransformation() { return &this->m_transformation; }

glm::vec3 Model::getDiffuseColor() { return this->m_diffuseColor; }
float Model::getKDiffuse() { return this->m_kDiffuse; }

GLint Model::getTextureID() { return this->m_textureID; }

void Model::setDiffuseColor(const glm::vec3& t_diffuseColor) { this->m_diffuseColor = t_diffuseColor; }
void Model::setKDiffuse(float t_kDiffuse) { this->m_kDiffuse = t_kDiffuse; }

void Model::setTextureID(const GLuint t_textureID) { this->m_textureID = t_textureID; }

bool Model::animate() { return false; } // default implementation; no animation

void Model::draw() {
	this->m_shaderProgram->use();
	this->m_vao->bind();

	// update (solve the necessary transformations) and notify (if necessary)
	this->updateAndNotify();

	// shader uniforms
	this->m_shaderProgram->setUniform("modelMatrix", this->m_transformation.getModelMatrix());
	this->m_shaderProgram->setUniform("normalMatrix", this->m_normalMatrix);

	this->m_shaderProgram->setUniform("lightColor", this->getDiffuseColor()); // single color shader

	this->m_shaderProgram->setUniform("textureUnit", this->getTextureID());

	// deal with the observer subjects
	this->m_shaderProgram->follow<Camera>();
	this->m_shaderProgram->follow<Light>();
	/* debugging purposes only
	auto tmpObj = this->m_transformation.getModelMatrix();
	this->m_shaderProgram->follow<Light>(&tmpObj); */

	// draw it
	if (this->m_ibo != nullptr) {
		this->m_ibo->bind();
		glDrawElements(GL_TRIANGLES, this->m_count, GL_UNSIGNED_INT, nullptr); // draw the model using the index buffer object
	} else
		glDrawArrays(GL_TRIANGLES, this->m_first, this->m_count); // draw the model using the vertex array object
}

// --- protected ---------------------------------------------------------------
void Model::preUpdate()  { } // default implementation; do nothing

void Model::postUpdate() {
	if (this->m_transformation.hasChanged()) { // only in case the model matrix has changed
		// calculate the normal matrix; as the inverse transpose of the model matrix; 3x3 matrix
		this->m_normalMatrix = glm::transpose(glm::inverse(glm::mat3(this->m_transformation.getModelMatrix())));

		this->m_transformation.clearChanged();
	}
}

// --- private -----------------------------------------------------------------
void Model::updateAndNotify() {
	this->preUpdate();

	// animate
	this->m_transformation.animate(); // animate the transformation (in case it makes sense)
	this->animate(); // animate the model (in case it makes sense)

	this->postUpdate();
}
