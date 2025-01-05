#include "ModelFireball.h"
#include "AppUtils.h"
#include "Config.h"
#include "TransformationStepScale.h"

// GLM
#include <glm/common.hpp>
//#include <glm/glm.hpp>

#define RND_DIFFUSE_MIN .5f
#define RND_DIFFUSE_MAX 1.f
#define RND_SPECULAR_MIN .5f
#define RND_SPECULAR_MAX 1.f

#define RND_TIME_DIFFUSE_MIN .3f
#define RND_TIME_DIFFUSE_MAX .6f
#define RND_TIME_SPECULAR_MIN .03f
#define RND_TIME_SPECULAR_MAX .1f

// --- public ------------------------------------------------------------------
ModelFireball::ModelFireball(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: Model(t_shaderProgram, t_vao, t_first, t_count) {
	fireballT type = fireballT::FIREBALL_FIERY;

	this->m_state = stateT::STATE_NONE;
	this->m_power = 0.f;

	this->m_diffuseColor  = this->generateRandomColor(type);
	this->m_specularColor = this->generateRandomColor(type);
	this->m_diffuseColorTarget  = this->generateRandomColor(type);
	this->m_specularColorTarget = this->generateRandomColor(type);

	this->m_kDiffuse  = AppUtils::getInstance()->randomNumber(RND_DIFFUSE_MIN,  RND_DIFFUSE_MAX);
	this->m_kSpecular = AppUtils::getInstance()->randomNumber(RND_SPECULAR_MIN, RND_SPECULAR_MAX);
	this->m_kDiffuseTarget  = AppUtils::getInstance()->randomNumber(RND_DIFFUSE_MIN,  RND_DIFFUSE_MAX);
	this->m_kSpecularTarget = AppUtils::getInstance()->randomNumber(RND_SPECULAR_MIN, RND_SPECULAR_MAX);

	this->m_transitionTimeDiffuseColor  = AppUtils::getInstance()->randomNumber(RND_TIME_DIFFUSE_MIN,  RND_TIME_DIFFUSE_MAX);
	this->m_transitionTimeSpecularColor = AppUtils::getInstance()->randomNumber(RND_TIME_SPECULAR_MIN, RND_TIME_SPECULAR_MAX);
	this->m_transitionTimeDiffuseIntensity  = AppUtils::getInstance()->randomNumber(RND_TIME_DIFFUSE_MIN,  RND_TIME_DIFFUSE_MAX);
	this->m_transitionTimeSpecularIntensity = AppUtils::getInstance()->randomNumber(RND_TIME_SPECULAR_MIN, RND_TIME_SPECULAR_MAX);
	this->m_elapsedTimeDiffuseColor  = 0.f;
	this->m_elapsedTimeSpecularColor = 0.f;
	this->m_elapsedTimeDiffuseIntensity  = 0.f;
	this->m_elapsedTimeSpecularIntensity = 0.f;
}

bool ModelFireball::animate() {
	fireballT type = fireballT::FIREBALL_NECROMANTIC;

	this->m_deltaTime.update();
	float delta = this->m_deltaTime.getDeltaSeconds();

	if (this->m_state == stateT::STATE_CHARGING) {
		this->m_power += delta;
		if (this->m_power >= Config::ENVIRONMENT_FIREBALL_MAX_POWER) {
			this->m_power = Config::ENVIRONMENT_FIREBALL_MAX_POWER;

			this->m_state = stateT::STATE_THROWN;
		}

		this->getTransformation()->updateScaleStep(
			std::make_shared<TransformationStepScale>(glm::vec3(this->m_power)));
	}

	// time update
	this->m_elapsedTimeDiffuseColor  += delta;
	this->m_elapsedTimeSpecularColor += delta;
	this->m_elapsedTimeDiffuseIntensity  += delta;
	this->m_elapsedTimeSpecularIntensity += delta;

	float timeI; // time interpolation

	// color interpolation
	timeI = glm::clamp(this->m_elapsedTimeDiffuseColor / this->m_transitionTimeDiffuseColor, 0.f, 1.f);
	this->m_diffuseColor = glm::mix(this->m_diffuseColor, this->m_diffuseColorTarget, timeI);
	
	if (timeI >= 1.f) { // color transition is complete; set a new target color
		this->m_diffuseColorTarget = this->generateRandomColor(type);
		this->m_transitionTimeDiffuseColor = AppUtils::getInstance()->randomNumber(RND_TIME_DIFFUSE_MIN, RND_TIME_DIFFUSE_MAX);
		this->m_elapsedTimeDiffuseColor = 0.f;
	}

	timeI = glm::clamp(this->m_elapsedTimeSpecularColor / this->m_transitionTimeSpecularColor, 0.f, 1.f);
	this->m_specularColor = glm::mix(this->m_specularColor, this->m_specularColorTarget, timeI);

	if (timeI >= 1.f) { // color transition is complete; set a new target color
		this->m_specularColorTarget = this->generateRandomColor(type);
		this->m_transitionTimeSpecularColor = AppUtils::getInstance()->randomNumber(RND_TIME_SPECULAR_MIN, RND_TIME_SPECULAR_MAX);
		this->m_elapsedTimeSpecularColor = 0.f;
	}

	// intensity interpolation
	timeI = glm::clamp(this->m_elapsedTimeDiffuseIntensity / this->m_transitionTimeDiffuseIntensity, 0.f, 1.f);
	this->m_kDiffuse = glm::mix(this->m_kDiffuse, this->m_kDiffuseTarget, timeI);
	
	if (timeI >= 1.f) { // intensity transition is complete; set a new target intensity
		this->m_kDiffuseTarget = AppUtils::getInstance()->randomNumber(RND_DIFFUSE_MIN, RND_DIFFUSE_MAX);
		this->m_transitionTimeDiffuseIntensity = AppUtils::getInstance()->randomNumber(RND_TIME_DIFFUSE_MIN, RND_TIME_DIFFUSE_MAX);
		this->m_elapsedTimeDiffuseIntensity = 0.f;
	}

	timeI = glm::clamp(this->m_elapsedTimeSpecularIntensity / this->m_transitionTimeSpecularIntensity, 0.f, 1.f);
	this->m_kSpecular = glm::mix(this->m_kSpecular, this->m_kSpecularTarget, timeI);

	if (timeI >= 1.f) { // intensity transition is complete; set a new target intensity
		this->m_kSpecularTarget = AppUtils::getInstance()->randomNumber(RND_SPECULAR_MIN, RND_SPECULAR_MAX);
		this->m_transitionTimeSpecularIntensity = AppUtils::getInstance()->randomNumber(RND_TIME_SPECULAR_MIN, RND_TIME_SPECULAR_MAX);
		this->m_elapsedTimeSpecularIntensity = 0.f;
	}

	this->notifyObservers(); // notify every time; even if transition does not occur, the color and intensity are updated

	return true;
}

/*const float ModelFireball::getPower() const {
	return this->m_power;
}*/

void ModelFireball::setState(stateT t_state) {
	this->m_state = t_state;
}

// --- private -----------------------------------------------------------------
void ModelFireball::x() {
}

void ModelFireball::y() {
}

glm::vec3 ModelFireball::generateRandomColor(fireballT t_type) const {
	switch (t_type) {
	case ModelFireball::FIREBALL_FIERY: // traditional fiery fireball (orange, red, yellow)
		return glm::vec3(
			AppUtils::getInstance()->randomNumber(0.8f, 1.0f),
			AppUtils::getInstance()->randomNumber(0.3f, 0.8f),
			AppUtils::getInstance()->randomNumber(0.0f, 0.2f)
		);

	case ModelFireball::FIREBALL_ICY: // icy fireball (light blue, cyan, white)
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
