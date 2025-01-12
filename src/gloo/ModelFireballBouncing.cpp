#include "ModelFireballBouncing.h"

#define RND_DIFFUSE_MIN .5f
#define RND_DIFFUSE_MAX 1.f
#define RND_SPECULAR_MIN .5f
#define RND_SPECULAR_MAX 1.f

#define RND_TIME_DIFFUSE_MIN .3f
#define RND_TIME_DIFFUSE_MAX .6f
#define RND_TIME_SPECULAR_MIN .03f
#define RND_TIME_SPECULAR_MAX .1f

// --- public ------------------------------------------------------------------
ModelFireballBouncing::ModelFireballBouncing(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count)
	: ModelFireball(t_name, t_shaderProgram, t_vao, t_ibo, t_first, t_count) {
}

ModelFireballBouncing::ModelFireballBouncing(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: ModelFireballBouncing(t_name, t_shaderProgram, t_vao, nullptr, t_first, t_count) { }

ModelFireballBouncing::ModelFireballBouncing(ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count)
	: ModelFireballBouncing("@!#?@!", t_shaderProgram, t_vao, t_ibo, t_first, t_count) { }

ModelFireballBouncing::ModelFireballBouncing(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: ModelFireballBouncing("@!#?@!", t_shaderProgram, t_vao, nullptr, t_first, t_count) { }

void ModelFireballBouncing::animateContinuous() {
	this->setState(fireballStateE::STATE_IDLE); // default implementation; the fireball stops when it reaches the destination; no continuous animation
}

// --- private -----------------------------------------------------------------
glm::vec3 ModelFireballBouncing::getPointOnSkyboxWall() {
	glm::vec3 point;
	return point;
}
