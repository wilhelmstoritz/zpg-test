#pragma once

#include "TransformationStepTranslate.h"
#include "DeltaTime.h"

class TransformationAnimationBezierMove : public TransformationStepTranslate {
public:
    TransformationAnimationBezierMove(const glm::vec3& t_start, const glm::vec3& t_end, const std::vector<glm::vec3>& t_controlPoints, float t_duration);

    virtual bool animate() override;

private:
    glm::vec3 m_start;
    glm::vec3 m_end;
    std::vector<glm::vec3> m_controlPoints;

    float m_duration;
    float m_elapsedTime;

    DeltaTime m_deltaTime;

	std::vector<float> m_binomialCoefficients; // precomputed binomial coefficients for the bezier curve; bernstein polynomial

    glm::vec3 calculateBezierPoint(float t) const;
    //float computeBinomialCoefficient(int n, int i) const;
    void precomputeBinomialCoefficients();
};
