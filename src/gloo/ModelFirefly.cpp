#include "ModelFirefly.h"
#include "AppUtils.h"

// --- public ------------------------------------------------------------------
ModelFirefly::ModelFirefly(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: Model(t_shaderProgram, t_vao, t_first, t_count) {
	//this->generateRandomColor();
}

bool ModelFirefly::animate() {
	return true;
}

// --- private -----------------------------------------------------------------
glm::vec3 ModelFirefly::generateRandomColor(const float t_min, const float t_max) const {
	return glm::vec3(
		AppUtils::getInstance()->randomNumber(t_min, t_max),
		AppUtils::getInstance()->randomNumber(t_min, t_max),
		AppUtils::getInstance()->randomNumber(t_min, t_max));
}

float ModelFirefly::generateRandomTime(const float t_min, const float t_max) const {
	return AppUtils::getInstance()->randomNumber(t_min, t_max);
}
