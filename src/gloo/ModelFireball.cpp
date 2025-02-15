#include "ModelFireball.h"
#include "AppMath.h"
#include "Config.h"
#include "TransformationStepScale.h"

// glm
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
ModelFireball::ModelFireball(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count)
	: ModelLightEmitting(t_name, t_shaderProgram, t_vao, t_ibo, t_first, t_count) {
	this->m_power = 0.f;

	this->setState(fireballStateE::STATE_OFF, fireballTypeE::FIREBALL_FIERY);

	// colors
	this->m_diffuseColorTarget  = glm::vec3(0.f);
	this->m_specularColorTarget = glm::vec3(0.f);

	this->m_kDiffuseTarget  = 0.f;
	this->m_kSpecularTarget = 0.f;

	// transition times
	this->m_transitionTimeDiffuseColor  = 0.f;
	this->m_transitionTimeSpecularColor = 0.f;
	this->m_transitionTimeDiffuseIntensity  = 0.f;
	this->m_transitionTimeSpecularIntensity = 0.f;

	this->m_elapsedTimeDiffuseColor  = 0.f;
	this->m_elapsedTimeSpecularColor = 0.f;
	this->m_elapsedTimeDiffuseIntensity  = 0.f;
	this->m_elapsedTimeSpecularIntensity = 0.f;
}

ModelFireball::ModelFireball(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: ModelFireball(t_name, t_shaderProgram, t_vao, nullptr, t_first, t_count) { }

ModelFireball::ModelFireball(ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count)
	: ModelFireball("@!#?@!", t_shaderProgram, t_vao, t_ibo, t_first, t_count) { }

ModelFireball::ModelFireball(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: ModelFireball("@!#?@!", t_shaderProgram, t_vao, nullptr, t_first, t_count) { }

float ModelFireball::getPower() const { return this->m_power; }

ModelFireball::fireballTypeE  ModelFireball::getType()  const { return this->m_type; }
ModelFireball::fireballStateE ModelFireball::getState() const { return this->m_state; }

void ModelFireball::setState(fireballStateE t_state, fireballTypeE t_type) {
	this->m_type = t_type;

	this->setState(t_state);
}

void ModelFireball::setState(fireballStateE t_state) {
	this->m_state = t_state;

	switch (this->m_state) {
	case fireballStateE::STATE_OFF:
		this->getTransformation()->updateScaleStep(
			std::make_shared<TransformationStepScale>(glm::vec3(0.f))); // zero size; invisible

		// colors
		this->m_diffuseColor  = glm::vec3(0.f); // black
		this->m_specularColor = glm::vec3(0.f);

		this->m_kDiffuse  = 0.f; // no reflection
		this->m_kSpecular = 0.f;
		break;

	case fireballStateE::STATE_IDLE:
		// colors
		this->m_specularColor = glm::vec3(0.f); // black
		this->m_kSpecular = 0.f; // no reflection
		break;

	case fireballStateE::STATE_CHARGING:
		this->m_power = 0.f; // reset power; start charging from the beginning
		break;

	case fireballStateE::STATE_CHARGED:
		this->m_power = Config::ENVIRONMENT_FIREBALL_MAX_POWER;
		break;

	default:
		//[[unlikely]] break; // requires c++20; not allowed in project
		break;
	}
}

bool ModelFireball::animate() {
	this->m_deltaTime.update();
	float delta = this->m_deltaTime.getDeltaSeconds();

	switch (this->m_state) {
	case fireballStateE::STATE_CHARGING:
		this->m_power += delta / 1.5f; // 1.5 times slower charging; power = seconds
		if (this->m_power >= Config::ENVIRONMENT_FIREBALL_MAX_POWER)
			this->setState(fireballStateE::STATE_CHARGED);

		this->getTransformation()->updateScaleStep(
			std::make_shared<TransformationStepScale>(glm::vec3(this->m_power / 3.f))); // 3 times smaller; power = size; the default diameter of the sphere is 2 units
		break;

	case fireballStateE::STATE_THROWN:
		if (!this->getTransformation()->hasChanged())
			this->setState(fireballStateE::STATE_IDLE); // the fireball has reached its destination
		break;

	case fireballStateE::STATE_THROWN_CONTINUOUS:
		if (!this->getTransformation()->hasChanged())
			this->animateContinuous(); // the fireball has reached its destination; animate it further
		break;

	default:
		//[[unlikely]] break; // requires c++20; not allowed in project
		break;
	}

	if (this->m_state == fireballStateE::STATE_OFF) // do not update color and intensity when the fireball is off
		return true;

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
		this->m_diffuseColorTarget = this->generateRandomColor();
		this->m_transitionTimeDiffuseColor = AppMath::getInstance()->randomNumber(RND_TIME_DIFFUSE_MIN, RND_TIME_DIFFUSE_MAX);
		this->m_elapsedTimeDiffuseColor = 0.f;
	}

	timeI = glm::clamp(this->m_elapsedTimeSpecularColor / this->m_transitionTimeSpecularColor, 0.f, 1.f);
	if (this->m_state != fireballStateE::STATE_IDLE) // no reflection when idle
		this->m_specularColor = glm::mix(this->m_specularColor, this->m_specularColorTarget, timeI);

	if (timeI >= 1.f) { // color transition is complete; set a new target color
		this->m_specularColorTarget = this->generateRandomColor();
		this->m_transitionTimeSpecularColor = AppMath::getInstance()->randomNumber(RND_TIME_SPECULAR_MIN, RND_TIME_SPECULAR_MAX);
		this->m_elapsedTimeSpecularColor = 0.f;
	}

	// intensity interpolation
	timeI = glm::clamp(this->m_elapsedTimeDiffuseIntensity / this->m_transitionTimeDiffuseIntensity, 0.f, 1.f);
	this->m_kDiffuse = glm::mix(this->m_kDiffuse, this->m_kDiffuseTarget, timeI);
	
	if (timeI >= 1.f) { // intensity transition is complete; set a new target intensity
		this->m_kDiffuseTarget = AppMath::getInstance()->randomNumber(RND_DIFFUSE_MIN, RND_DIFFUSE_MAX);
		this->m_transitionTimeDiffuseIntensity = AppMath::getInstance()->randomNumber(RND_TIME_DIFFUSE_MIN, RND_TIME_DIFFUSE_MAX);
		this->m_elapsedTimeDiffuseIntensity = 0.f;
	}

	timeI = glm::clamp(this->m_elapsedTimeSpecularIntensity / this->m_transitionTimeSpecularIntensity, 0.f, 1.f);
	if (this->m_state != fireballStateE::STATE_IDLE) // no reflection when idle
		this->m_kSpecular = glm::mix(this->m_kSpecular, this->m_kSpecularTarget, timeI);

	if (timeI >= 1.f) { // intensity transition is complete; set a new target intensity
		this->m_kSpecularTarget = AppMath::getInstance()->randomNumber(RND_SPECULAR_MIN, RND_SPECULAR_MAX);
		this->m_transitionTimeSpecularIntensity = AppMath::getInstance()->randomNumber(RND_TIME_SPECULAR_MIN, RND_TIME_SPECULAR_MAX);
		this->m_elapsedTimeSpecularIntensity = 0.f;
	}

	this->notifyObservers(); // notify every time; even if transition does not occur, the color and intensity are updated

	return true;
}

void ModelFireball::animateContinuous() {
	this->setState(fireballStateE::STATE_IDLE); // default implementation; the fireball stops when it reaches the destination; no continuous animation
}

template <>
void ModelFireball::follow<Camera>() {
	/*if (this->Observer<Camera>::needsUpdate())
		printf("[model fireball] name %s : follow camera\n", this->getName().c_str());*/

	this->Observer<Camera>::processAllSubjects();
}

// --- protected ---------------------------------------------------------------
void ModelFireball::processSubject(Camera* t_camera) {
	//printf("[model fireball] name '%s' process subject : camera name '%s'\n", this->getName().c_str(), t_camera->getName().c_str());

	// follow the camera
	glm::vec3 direction = t_camera->getDirection();
	if (direction.y < 0.f) {
		// do not throw below the horizon
		direction.y = .001f;
		direction = glm::normalize(direction);
	}

	this->getTransformation()->updateTranslateStep(
		std::make_shared<TransformationStepTranslate>(t_camera->getEye() + direction * Config::ENVIRONMENT_FIREBALL_OFFSET));

	/* translate the model to the camera position and rotate it to the camera direction; exam task (to make it visible, a different model than a sphere was used)
	// translate the model to the camera position
	this->getTransformation()->updateTranslateStep(
		std::make_shared<TransformationStepTranslate>(t_camera->getEye()));

	// rotate the model to the camera direction
	glm::vec3 initial(0.f, 0.f, 1.f); // initial direction of the model; z axis
	glm::vec3 direction = t_camera->getDirection();

	glm::vec3 axis = glm::normalize(glm::cross(initial, direction)); // rotation axis; perpendicular to the initial direction and the direction

	float cosTheta = glm::dot(glm::normalize(initial), glm::normalize(direction));
	float angle = std::acos(glm::clamp(cosTheta, -1.f, 1.f)); // rotation angle; radians; 

	this->getTransformation()->updateRotateStep(
		std::make_shared<TransformationStepRotate>(axis, angle));*/

	//this->notifyObservers(); // in case directly process the subject
}

void ModelFireball::preUpdate() {
	Model::preUpdate();

	// deal with the observer subject
	this->follow<Camera>();
}

// --- private -----------------------------------------------------------------
glm::vec3 ModelFireball::generateRandomColor() const {
	switch (this->m_type) {
	case fireballTypeE::FIREBALL_FIERY: // traditional fiery fireball (orange, red, yellow)
		return glm::vec3(
			AppMath::getInstance()->randomNumber(.8f, 1.f),
			AppMath::getInstance()->randomNumber(.1f,  .6f),
			AppMath::getInstance()->randomNumber(.0f,  .1f));

	case fireballTypeE::FIREBALL_ICY: // icy fireball (light blue, cyan, white)
		return glm::vec3(
			AppMath::getInstance()->randomNumber(.4f,  .7f),
			AppMath::getInstance()->randomNumber(.7f, 1.f),
			AppMath::getInstance()->randomNumber(.9f, 1.f));

	case fireballTypeE::FIREBALL_NECROMANTIC: { // dark or necromantic fireball (purple, black, dark red)
		float brightness = AppMath::getInstance()->randomNumber(0.f, 1.f); // brightness; 0 = black, 1 = full color
		return glm::vec3(
			AppMath::getInstance()->randomNumber(.4f, .7f) * brightness,
			AppMath::getInstance()->randomNumber(.0f, .1f) * brightness,
			AppMath::getInstance()->randomNumber(.4f, .6f) * brightness); }

	case fireballTypeE::FIREBALL_ELDRITCH: // eldritch fireball (green, neon yellow, dark blue)
		return glm::vec3(
			AppMath::getInstance()->randomNumber(.4f,  .8f),
			AppMath::getInstance()->randomNumber(.9f, 1.f),
			AppMath::getInstance()->randomNumber(.1f,  .4f));

	default: // white color as a fallback; should never happen
		return glm::vec3(1.f, 1.f, 1.f);
	}
}
