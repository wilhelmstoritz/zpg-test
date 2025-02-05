#include "TransformationAnimationBezierCurve.h"
#include "AppMath.h"
#include "Config.h"

// glm
#include <glm/glm.hpp>

// standard c++ libraries
#include <cmath>

// --- public ------------------------------------------------------------------
TransformationAnimationBezierCurve::TransformationAnimationBezierCurve(
    const std::vector<std::vector<glm::vec3>>& t_points, float t_duration)
	: TransformationStepTranslate(t_points[0][0]), // start point; first point of the first curve
    m_points(t_points), m_duration(t_duration) {
	this->m_animationState = animationStateE::ANIMATION_RUNNING;
	this->m_elapsedTime = 0.f;

    this->precomputeSegmentLengths(); // precompute segment lengths and cumulative ratios

    this->m_deltaTime.update(); // reset the timer; construction time is not taken into account
}

TransformationAnimationBezierCurve::TransformationAnimationBezierCurve(
    const std::vector<glm::vec3>& t_points, float t_duration)
    : TransformationAnimationBezierCurve(std::vector<std::vector<glm::vec3>>{ t_points }, t_duration) { }

bool TransformationAnimationBezierCurve::animate() {
	if (this->m_animationState == animationStateE::ANIMATION_FINISHED)
		return false; // do not update the transformation

    this->m_deltaTime.update();
    float delta = this->m_deltaTime.getDeltaSeconds();
    this->m_elapsedTime += delta;

	float t = glm::clamp(this->m_elapsedTime / this->m_duration, 0.f, 1.f); // normalized time; interval <0, 1>

    size_t currentSegment = 0; // current segment according to the cumulative ratios
    while (currentSegment < this->m_cumulativeRatios.size() - 1 && t > this->m_cumulativeRatios[currentSegment + 1])
        ++currentSegment;

    float tSegment = // relative time for the current segment
        (t - this->m_cumulativeRatios[currentSegment]) /
        (this->m_cumulativeRatios[currentSegment + 1] - this->m_cumulativeRatios[currentSegment]);

    glm::vec3 newTranslation = AppMath::getInstance()->bezierPoint(this->m_points[currentSegment], tSegment);
    this->setTranslation(newTranslation);

    if (t == 1.f && this->m_animationState == animationStateE::ANIMATION_RUNNING) // animation is finished when t reaches 1; if t < 1, animation is still running
        this->m_animationState = animationStateE::ANIMATION_FINISHED; // animation is finished

	//return t < 1.f; // animation is finished when t reaches 1; if t < 1, animation is still running; obsolete, replaced by using m_animationState, so the transformation is always updated, even the last one when t = 1
    return true; // update the transformation
}

// --- private -----------------------------------------------------------------
void TransformationAnimationBezierCurve::precomputeSegmentLengths() {
    size_t numSegments = this->m_points.size();
	this->m_segmentLengths.resize(numSegments);       // vector of segment lengths
	this->m_cumulativeRatios.resize(numSegments + 1); // vector of cumulative ratios; including the start and the end (0 and 1)

    // length of each segment
    float totalLength = 0.f;

    for (size_t i = 0; i < numSegments; ++i) {
		float length = AppMath::getInstance()->bezierCurveLength(this->m_points[i]); // length of the i-th bezier segment
        this->m_segmentLengths[i] = length;
        totalLength += length;
    }

	// cumulative ratios of the segments
    float cumulativeLength = 0.f;

    for (size_t i = 0; i < numSegments; ++i) {
        cumulativeLength += this->m_segmentLengths[i];
        this->m_cumulativeRatios[i + 1] = cumulativeLength / totalLength;
    }
}
