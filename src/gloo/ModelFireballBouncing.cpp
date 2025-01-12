#include "ModelFireballBouncing.h"
#include "AppMath.h"
#include "Config.h"

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

glm::vec3 generateRandomPointOnSkybox() {
	// choose a random wall (0 = -x, 1 = +x, 2 = -y, 3 = +y, 4 = -z, 5 = +z)
    int wall = AppMath::getInstance()->randomNumber(0, 5);

    float x, y, z;
	glm::vec3 min = Config::SKYBOX_MIN_VIRTUALWORLD;
	glm::vec3 max = Config::SKYBOX_MAX;

    switch (wall) {
    case 0: // -x wall
        x = min.x;
        y = AppMath::getInstance()->randomNumber(min.y, max.y);
        z = AppMath::getInstance()->randomNumber(min.z, max.z);
        break;
    case 1: // +x wall
        x = max.x;
        y = AppMath::getInstance()->randomNumber(min.y, max.y);
        z = AppMath::getInstance()->randomNumber(min.z, max.z);
        break;
    case 2: // -y wall
        x = AppMath::getInstance()->randomNumber(min.x, max.x);
        y = min.y;
        z = AppMath::getInstance()->randomNumber(min.z, max.z);
        break;
    case 3: // +y wall
        x = AppMath::getInstance()->randomNumber(min.x, max.x);
        y = max.y;
        z = AppMath::getInstance()->randomNumber(min.z, max.z);
        break;
    case 4: // -z wall
        x = AppMath::getInstance()->randomNumber(min.x, max.x);
        y = AppMath::getInstance()->randomNumber(min.y, max.y);
        z = min.z;
        break;
    case 5: // +z wall
        x = AppMath::getInstance()->randomNumber(min.x, max.x);
        y = AppMath::getInstance()->randomNumber(min.y, max.y);
        z = max.z;
        break;
    }

    return glm::vec3(x, y, z);
}
