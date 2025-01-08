#include "ModelLightEmitting.h"

// --- public ------------------------------------------------------------------
ModelLightEmitting::ModelLightEmitting(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count)
	: Model(t_name, t_shaderProgram, t_vao, t_ibo, t_first, t_count) {
	// color and reflection coefficient
	this->m_specularColor = glm::vec3(1.f); // white
	this->m_kSpecular = 1.f; // maximum reflection
}

ModelLightEmitting::ModelLightEmitting(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: ModelLightEmitting(t_name, t_shaderProgram, t_vao, nullptr, t_first, t_count) { }

ModelLightEmitting::ModelLightEmitting(ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count)
	: ModelLightEmitting("@!#?@!", t_shaderProgram, t_vao, t_ibo, t_first, t_count) { }

ModelLightEmitting::ModelLightEmitting(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: ModelLightEmitting("@!#?@!", t_shaderProgram, t_vao, nullptr, t_first, t_count) { }

glm::vec3 ModelLightEmitting::getSpecularColor() { return this->m_specularColor; }
float ModelLightEmitting::getKSpecular() { return this->m_kSpecular; }

void ModelLightEmitting::setSpecularColor(const glm::vec3& t_specularColor) { this->m_specularColor = t_specularColor; }
void ModelLightEmitting::setKSpecular(float t_kSpecular) { this->m_kSpecular = t_kSpecular; }

bool ModelLightEmitting::animate() { return false; } // default implementation; no animation

// --- protected ---------------------------------------------------------------
void ModelLightEmitting::postUpdate() {
	bool hasChanged = this->getTransformation()->hasChanged(); // base implementation should be called first; but it clears the changed flag

	Model::postUpdate();

	if (hasChanged)
		this->notifyObservers();
}
