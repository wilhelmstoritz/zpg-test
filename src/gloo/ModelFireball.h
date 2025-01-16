#pragma once

#include "ModelLightEmitting.h"
#include "Observer.h"
#include "Camera.h"
#include "DeltaTime.h"

class ModelFireball : public ModelLightEmitting, public Observer<Camera> {
public:
	enum class fireballTypeE {
		FIREBALL_FIERY       = 0,
		FIREBALL_ICY         = 1,
		FIREBALL_NECROMANTIC = 2,
		FIREBALL_ELDRITCH    = 3
	};

	enum class fireballStateE {
		STATE_OFF               = 0,
		STATE_IDLE              = 1,
		STATE_CHARGING          = 2,
		STATE_CHARGED           = 3,
		STATE_THROWN            = 4,
		STATE_THROWN_CONTINUOUS = 5 // thrown and continuously animated; doesn't have to stop if it reaches the destination; for example, a fireball that moves in a circle
	};

	ModelFireball(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count);
	ModelFireball(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao,             GLint t_first, GLsizei t_count);
	ModelFireball(ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count);
	ModelFireball(ShaderProgram* t_shaderProgram, VAO* t_vao,             GLint t_first, GLsizei t_count);

	float getPower() const;
	fireballTypeE  getType()  const;
	fireballStateE getState() const;

	void setState(fireballStateE t_state, fireballTypeE t_type);
	void setState(fireballStateE t_state);

	virtual bool animate() override;
	virtual void animateContinuous();

	template <typename T>
	void follow();

protected:
	virtual void processSubject(Camera* t_camera) override;

	virtual void preUpdate() override;

private:
	float m_power; // power of the fireball; affects the size, brightness, as well as the duration and length of the fireball throw
	fireballTypeE  m_type;
	fireballStateE m_state;

	glm::vec3 m_diffuseColorTarget;
	glm::vec3 m_specularColorTarget;
	float m_kDiffuseTarget; // target reflection coefficients
	float m_kSpecularTarget;

	float m_transitionTimeDiffuseColor;
	float m_transitionTimeSpecularColor;
	float m_transitionTimeDiffuseIntensity;
	float m_transitionTimeSpecularIntensity;

	float m_elapsedTimeDiffuseColor;
	float m_elapsedTimeSpecularColor;
	float m_elapsedTimeDiffuseIntensity;
	float m_elapsedTimeSpecularIntensity;

	DeltaTime m_deltaTime;

	glm::vec3 generateRandomColor() const;
};
