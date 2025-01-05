#pragma once

#include "Model.h"
#include "DeltaTime.h"

class ModelFireball : public Model {
public:
	ModelFireball(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count);

	virtual bool animate() override;

private:
	enum fireballT {
		FIREBALL_FIERY = 1,
		FIREBALL_ICE = 2,
		FIREBALL_NECROMANTIC = 3,
		FIREBALL_ELDRITCH = 4
	};

	glm::vec3 m_diffuseColorTarget;
	glm::vec3 m_specularColorTarget;
	float m_kDiffuseTarget; // target reflection coefficients
	float m_kSpecularTarget;

	float m_transitionTimeColor;
	float m_transitionTimeIntensity;
	float m_elapsedTimeColor;
	float m_elapsedTimeIntensity;

	DeltaTime m_deltaTime;

	glm::vec3 generateRandomColor(fireballT t_type) const;
};
