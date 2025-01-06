#pragma once

#include "Model.h"
#include "DeltaTime.h"

class ModelFireball : public Model {
public:
	enum stateT {
		STATE_NONE = -1,
		STATE_IDLE = 0,
		STATE_CHARGING = 1,
		STATE_THROWN = 2
	};

	ModelFireball(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count);

	virtual bool animate() override;

	//const float getPower() const;
	void setState(stateT t_state);

protected:
	virtual void processSubject(Camera* t_camera) override;

private:
	enum fireballT {
		FIREBALL_FIERY       = 1,
		FIREBALL_ICY         = 2,
		FIREBALL_NECROMANTIC = 3,
		FIREBALL_ELDRITCH    = 4
	};

	stateT m_state;
	float m_power; // power of the fireball; affects the size, brightness, as well as the duration and length of the fireball throw

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

	void x();
	void y();

	glm::vec3 generateRandomColor(fireballT t_type) const;
};
