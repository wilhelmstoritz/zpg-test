#pragma once

#include "TransformationStepTranslate.h"
#include "DeltaTime.h"

// standard c++ libraries
#include <vector>

class TransformationAnimationBezierCurve : public TransformationStepTranslate {
public:
    TransformationAnimationBezierCurve(const std::vector<std::vector<glm::vec3>>& t_points, float t_duration);
    TransformationAnimationBezierCurve(const std::vector            <glm::vec3>&  t_points, float t_duration);

    virtual bool animate() override;

private:
	enum class animationStateE {
        ANIMATION_FINISHED = 0,
		ANIMATION_RUNNING  = 1
	};

    std::vector<std::vector<glm::vec3>> m_points;

	std::vector<float> m_segmentLengths;   // length of each bezier segment of the curve
	std::vector<float> m_cumulativeRatios; // cumulative ratios of the bezier segments of the curve

    animationStateE m_animationState;

    float m_duration;
    float m_elapsedTime;

    DeltaTime m_deltaTime;

    void precomputeSegmentLengths();
};
