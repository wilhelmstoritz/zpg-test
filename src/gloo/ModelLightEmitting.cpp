#include "ModelLightEmitting.h"

// --- public ------------------------------------------------------------------
ModelLightEmitting::ModelLightEmitting(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: Model(t_shaderProgram, t_vao, t_first, t_count) {
	// color, intensity and transition time; default values
	//this->m_diffuseColor = this->generateRandomColor();
	//this->m_specularColor = glm::vec3(.6f);
	//this->m_specularColor = this->m_diffuseColor;
	

	//this->m_kDiffuse = AppUtils::getInstance()->randomNumber(RND_DIFFUSE_MIN, RND_DIFFUSE_MAX);
}

bool ModelLightEmitting::animate() { return false; } // default implementation; no animation
