#pragma once

#include "TransformationStepTranslate.h"
#include "DeltaTime.h"

class TransformationAnimationBezierCurve : public TransformationStepTranslate {
public:
    TransformationAnimationBezierCurve(
        const glm::vec3& t_start, const glm::vec3& t_end,
		const std::vector<glm::vec3>& t_controlPoints,
        const std::vector<glm::vec3>& t_controlVectors,
        float t_duration);
    TransformationAnimationBezierCurve(
        const glm::vec3& t_start, const glm::vec3& t_end,
        const std::vector<glm::vec3>& t_controlPoints,
        float t_duration);

    virtual bool animate() override;

private:
	enum animationStateE {
        ANIMATION_NOT_RUNNING = 0,
		ANIMATION_RUNNING     = 1
	};

    animationStateE m_animationState;

    glm::vec3 m_start;
    glm::vec3 m_end;
    std::vector<glm::vec3> m_controlPoints;
	std::vector<glm::vec3> m_controlVectors;

    float m_duration;
    float m_elapsedTime;

    DeltaTime m_deltaTime;

	std::vector<float> m_binomialCoefficients; // precomputed binomial coefficients for the bezier curve; bernstein polynomial

	glm::vec3 calculateBezierPoint(float t) const;
	///glm::vec3 calculateHermitePoint(float t) const;
    //float computeBinomialCoefficient(size_t n, size_t i) const;
    void precomputeBinomialCoefficients();
};
