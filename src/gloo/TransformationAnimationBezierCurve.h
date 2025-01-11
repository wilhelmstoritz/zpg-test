#pragma once

#include "TransformationStepTranslate.h"
#include "DeltaTime.h"

class TransformationAnimationBezierCurve : public TransformationStepTranslate {
public:
    TransformationAnimationBezierCurve(const std::vector<glm::vec3>& t_points, float t_duration);

    virtual bool animate() override;

private:
	enum animationStateE {
        ANIMATION_FINISHED = 0,
		ANIMATION_RUNNING  = 1
	};

    std::vector<glm::vec3> m_points;
    ///std::vector<glm::vec3> m_controlVectors;

    animationStateE m_animationState;

    float m_duration;
    float m_elapsedTime;

    DeltaTime m_deltaTime;

    //std::vector<float>            m_binomialCoefficients;    // not universal; only for fixed degree of the bezier curve
	std::vector<std::vector<float>> m_allBinomialCoefficients; // precomputed binomial coefficients for all degrees (up to n-th degree) of the bezier curve

	glm::vec3 calculateBezierPoint(std::vector<glm::vec3> t_points, float t) const;
	///glm::vec3 calculateHermitePoint(float t) const;
    float computeBinomialCoefficient(size_t n, size_t i) const;
	//std::vector<float>            precomputeBinomialCoefficients(size_t n);    // not universal; only for fixed degree of the bezier curve
	std::vector<std::vector<float>> precomputeAllBinomialCoefficients(size_t n); // precompute binomial coefficients for all degrees (up to n-th degree) of the bezier curve
};
