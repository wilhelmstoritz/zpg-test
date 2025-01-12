#include "ModelFireballBouncing.h"
#include "AppMath.h"
#include "Config.h"
#include "TransformationAnimationBezierCurve.h"

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
    this->setState(fireballStateE::STATE_CHARGED);           // charged; ready to be thrown; power set to the maximum
	this->setState(fireballStateE::STATE_THROWN_CONTINUOUS); // thrown and continuously animated
}

ModelFireballBouncing::ModelFireballBouncing(const std::string& t_name, ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: ModelFireballBouncing(t_name, t_shaderProgram, t_vao, nullptr, t_first, t_count) { }

ModelFireballBouncing::ModelFireballBouncing(ShaderProgram* t_shaderProgram, VAO* t_vao, IBO* t_ibo, GLint t_first, GLsizei t_count)
	: ModelFireballBouncing("@!#?@!", t_shaderProgram, t_vao, t_ibo, t_first, t_count) { }

ModelFireballBouncing::ModelFireballBouncing(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count)
	: ModelFireballBouncing("@!#?@!", t_shaderProgram, t_vao, nullptr, t_first, t_count) { }

void ModelFireballBouncing::animateContinuous() {
    this->getTransformation()->updateTranslateStep(
        std::make_shared<TransformationAnimationBezierCurve>(
			std::vector<glm::vec3>{ // random bezier curve; starting point is the current position of the fireball
		        this->getTransformation()->getTranslateStep()->getTranslation(),
                this->randomPointOnSkybox(),
                this->randomPointOnSkybox() },
            this->getPower() * 10.f)); // 10 times longer duration; power = seconds
}

// --- private -----------------------------------------------------------------
glm::vec3 ModelFireballBouncing::randomPointOnSkybox() {
    // a random wall (0 = -x, 1 = +x, 2 = -y, 3 = +y, 4 = -z, 5 = +z)
    int wall = AppMath::getInstance()->randomNumber(0, 5);

    glm::vec3 point;
	glm::vec3 min = Config::SKYBOX_MIN_VIRTUALWORLD + this->getTransformation()->getScaleStep()->getScale(); // the radius of the sphere; default (non-scaled) radius is 1 unit
    glm::vec3 max = Config::SKYBOX_MAX              - this->getTransformation()->getScaleStep()->getScale();

	// the axis for the fixed coordinate (0 = x, 1 = y, 2 = z)
    int axis = wall / 2;

	// fixed coordinate value (minimum or maximum according to the index parity)
    float fixedValue = (wall % 2 == 0) ? min[axis] : max[axis];

	// random values for the remaining two coordinates
    int axis1 = (axis + 1) % 3;
    int axis2 = (axis + 2) % 3;

    point[axis] = fixedValue;
    point[axis1] = AppMath::getInstance()->randomNumber(min[axis1], max[axis1]);
    point[axis2] = AppMath::getInstance()->randomNumber(min[axis2], max[axis2]);

    return point;
}
