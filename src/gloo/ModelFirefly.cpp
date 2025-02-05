#include "ModelFirefly.h"
#include "AppMath.h"

// glm
#include <glm/common.hpp>
//#include <glm/glm.hpp>

#define RND_DIFFUSE_MIN 0.5f
#define RND_DIFFUSE_MAX 1.f
#define RND_TIME_MIN 0.5f
#define RND_TIME_MAX 1.f

// --- public ------------------------------------------------------------------
ModelFirefly::ModelFirefly(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count)
	: ModelLightEmitting(t_name, t_shaderProgram, t_vao, t_ibo, t_first, t_count) {
	// color, intensity and transition time; default values
	this->m_diffuseColor  = this->generateRandomColor();
	this->m_specularColor = glm::vec3(.6f);
	//this->m_specularColor = this->m_diffuseColor;
	this->m_diffuseColorTarget = this->generateRandomColor();

	this->m_kDiffuse = AppMath::getInstance()->randomNumber(RND_DIFFUSE_MIN, RND_DIFFUSE_MAX);
	this->m_kDiffuseTarget = AppMath::getInstance()->randomNumber(RND_DIFFUSE_MIN, RND_DIFFUSE_MAX);

	this->m_transitionTimeColor = AppMath::getInstance()->randomNumber(RND_TIME_MIN, RND_TIME_MAX);
	this->m_transitionTimeIntensity = AppMath::getInstance()->randomNumber(RND_TIME_MIN, RND_TIME_MAX);
	this->m_elapsedTimeColor = 0.f;
	this->m_elapsedTimeIntensity = 0.f;
}

ModelFirefly::ModelFirefly(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: ModelFirefly(t_name, t_shaderProgram, t_vao, nullptr, t_first, t_count) { }

ModelFirefly::ModelFirefly(ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count)
	: ModelFirefly("@!#?@!", t_shaderProgram, t_vao, t_ibo, t_first, t_count) { }

ModelFirefly::ModelFirefly(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: ModelFirefly("@!#?@!", t_shaderProgram, t_vao, nullptr, t_first, t_count) { }

bool ModelFirefly::animate() {
	this->m_deltaTime.update();
	float delta = this->m_deltaTime.getDeltaSeconds();

	// time update
	this->m_elapsedTimeColor += delta;
	this->m_elapsedTimeIntensity += delta;

	float timeI; // time interpolation

	// color interpolation
	timeI = glm::clamp(this->m_elapsedTimeColor / this->m_transitionTimeColor, 0.f, 1.f);
	this->m_diffuseColor = glm::mix(this->m_diffuseColor, this->m_diffuseColorTarget, timeI);
	//this->m_specularColor = this->m_diffuseColor;

	if (timeI >= 1.f) { // color transition is complete; set a new target color
		this->m_diffuseColorTarget = this->generateRandomColor();
		this->m_transitionTimeColor = AppMath::getInstance()->randomNumber(RND_TIME_MIN, RND_TIME_MAX);
		this->m_elapsedTimeColor = 0.f;
	}

	// intensity interpolation
	timeI = glm::clamp(this->m_elapsedTimeIntensity / this->m_transitionTimeIntensity, 0.f, 1.f);
	this->m_kDiffuse = glm::mix(this->m_kDiffuse, this->m_kDiffuseTarget, timeI);
	this->m_kSpecular = this->m_kDiffuse;

	if (timeI >= 1.f) { // intensity transition is complete; set a new target intensity
		this->m_kDiffuseTarget = AppMath::getInstance()->randomNumber(RND_DIFFUSE_MIN, RND_DIFFUSE_MAX);
		this->m_transitionTimeIntensity = AppMath::getInstance()->randomNumber(RND_TIME_MIN, RND_TIME_MAX);
		this->m_elapsedTimeIntensity = 0.f;
	}

	return true;
}

// --- private -----------------------------------------------------------------
glm::vec3 ModelFirefly::generateRandomColor() const {
	return glm::vec3(
		// white/yellow/orange color range
		AppMath::getInstance()->randomNumber(.8f, 1.f),
		AppMath::getInstance()->randomNumber(.7f, 1.f),
		AppMath::getInstance()->randomNumber(.0f,  .3f));
}
