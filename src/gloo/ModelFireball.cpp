#include "ModelFireball.h"
#include "AppUtils.h"

// GLM
#include <glm/common.hpp>
//#include <glm/glm.hpp>

#define RND_DIFFUSE_MIN 0.5f
#define RND_DIFFUSE_MAX 1.f
#define RND_TIME_MIN 0.5f
#define RND_TIME_MAX 1.f

// --- public ------------------------------------------------------------------
ModelFireball::ModelFireball(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: Model(t_shaderProgram, t_vao, t_first, t_count) {
	this->m_diffuseColor = this->generateRandomColor(FIREBALL_FIERY);
	this->m_diffuseColorTarget = this->generateRandomColor(FIREBALL_FIERY);

	this->m_kDiffuse = AppUtils::getInstance()->randomNumber(RND_DIFFUSE_MIN, RND_DIFFUSE_MAX);
	this->m_kDiffuseTarget = AppUtils::getInstance()->randomNumber(RND_DIFFUSE_MIN, RND_DIFFUSE_MAX);

	this->m_transitionTimeColor = AppUtils::getInstance()->randomNumber(RND_TIME_MIN, RND_TIME_MAX);
	this->m_transitionTimeIntensity = AppUtils::getInstance()->randomNumber(RND_TIME_MIN, RND_TIME_MAX);
	this->m_elapsedTimeColor = 0.f;
	this->m_elapsedTimeIntensity = 0.f;
}

bool ModelFireball::animate() {
	this->m_deltaTime.update();
	float delta = this->m_deltaTime.getDeltaSeconds();

	// time update
	this->m_elapsedTimeColor += delta;
	this->m_elapsedTimeIntensity += delta;

	// color interpolation
	float colorT = glm::clamp(this->m_elapsedTimeColor / this->m_transitionTimeColor, 0.f, 1.f);
	this->m_diffuseColor = glm::mix(this->m_diffuseColor, this->m_diffuseColorTarget, colorT);

	// intensity interpolation
	float intensityT = glm::clamp(this->m_elapsedTimeIntensity / this->m_transitionTimeIntensity, 0.f, 1.f);
	this->m_kDiffuse = glm::mix(this->m_kDiffuse, this->m_kDiffuseTarget, intensityT);

	// !!!
	this->m_specularColor = this->m_diffuseColor;
	this->m_kSpecular = this->m_kDiffuse;

	// color transition is complete; set a new target color
	if (colorT >= 1.f) {
		this->m_diffuseColorTarget = this->generateRandomColor(FIREBALL_FIERY);
		this->m_transitionTimeColor = AppUtils::getInstance()->randomNumber(RND_TIME_MIN, RND_TIME_MAX);
		this->m_elapsedTimeColor = 0.f;
	}

	// intensity transition is complete; set a new target intensity
	if (intensityT >= 1.f) {
		this->m_kDiffuseTarget = AppUtils::getInstance()->randomNumber(RND_DIFFUSE_MIN, RND_DIFFUSE_MAX);
		this->m_transitionTimeIntensity = AppUtils::getInstance()->randomNumber(RND_TIME_MIN, RND_TIME_MAX);
		this->m_elapsedTimeIntensity = 0.f;
	}

	return true;
}

// --- private -----------------------------------------------------------------
glm::vec3 ModelFireball::generateRandomColor(fireballT t_type) const {
	switch (t_type) {
	case ModelFireball::FIREBALL_FIERY: // traditional fiery fireball (orange, red, yellow)
		return glm::vec3(
			AppUtils::getInstance()->randomNumber(0.8f, 1.0f),
			AppUtils::getInstance()->randomNumber(0.3f, 0.8f),
			AppUtils::getInstance()->randomNumber(0.0f, 0.2f)
		);

	case ModelFireball::FIREBALL_ICE: // icy fireball (light blue, cyan, white)
		return glm::vec3(
			AppUtils::getInstance()->randomNumber(0.6f, 0.9f),
			AppUtils::getInstance()->randomNumber(0.8f, 1.0f),
			AppUtils::getInstance()->randomNumber(0.9f, 1.0f)
		);

	case ModelFireball::FIREBALL_NECROMANTIC: // dark or necromantic fireball (purple, black, dark red)
		return glm::vec3(
			AppUtils::getInstance()->randomNumber(0.3f, 0.6f),
			AppUtils::getInstance()->randomNumber(0.0f, 0.2f),
			AppUtils::getInstance()->randomNumber(0.3f, 0.7f)
		);

	case ModelFireball::FIREBALL_ELDRITCH: // eldritch fireball (green, neon yellow, dark blue)
		return glm::vec3(
			AppUtils::getInstance()->randomNumber(0.5f, 0.9f),
			AppUtils::getInstance()->randomNumber(0.8f, 1.0f),
			AppUtils::getInstance()->randomNumber(0.2f, 0.5f)
		);

	default: // white color as a fallback
		return glm::vec3(1.0f, 1.0f, 1.0f);
	}
}
