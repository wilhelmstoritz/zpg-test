#include "TransformationAnimationBezierCurve.h"

// GLM
#include <glm/glm.hpp>

// standard C++ libraries
#include <cmath>

// --- public ------------------------------------------------------------------
TransformationAnimationBezierCurve::TransformationAnimationBezierCurve(
    const std::vector<glm::vec3>& t_points, float t_duration)
	: TransformationStepTranslate(t_points[0]), // start point; the first point of the curve
    m_points(t_points), m_duration(t_duration) {
	this->m_animationState = ANIMATION_RUNNING;
	this->m_elapsedTime = 0.f;

    this->precomputeBinomialCoefficients();
	this->m_deltaTime.update(); // reset the timer; construction time is not taken into account
}

bool TransformationAnimationBezierCurve::animate() {
	if (this->m_animationState == ANIMATION_FINISHED)
		return false; // do not update the transformation

    this->m_deltaTime.update();
    float delta = this->m_deltaTime.getDeltaSeconds();
    this->m_elapsedTime += delta;

	float t = glm::clamp(this->m_elapsedTime / this->m_duration, 0.f, 1.f); // normalized time; interval <0, 1>
    glm::vec3 newTranslation = this->calculateBezierPoint(this->m_points, t);
    this->setTranslation(newTranslation);

    if (t == 1.f && this->m_animationState == ANIMATION_RUNNING) // animation is finished when t reaches 1; if t < 1, animation is still running
        this->m_animationState = ANIMATION_FINISHED; // animation is finished

	//return t < 1.f; // animation is finished when t reaches 1; if t < 1, animation is still running; obsolete, replaced by using m_animationState, so the transformation is always updated, even the last one when t = 1
    return true; // update the transformation
}

// --- private -----------------------------------------------------------------
glm::vec3 TransformationAnimationBezierCurve::calculateBezierPoint(std::vector<glm::vec3> t_points, float t) const {
	// de casteljau's algorithm; complexity: O(n^2); https://en.wikipedia.org/wiki/De_Casteljau%27s_algorithm
    /*std::vector<glm::vec3> points = this->m_controlPoints; // complete list of points: start, control points, and end
    points.insert(points.begin(), this->m_start);
    points.push_back(this->m_end);*/
	std::vector<glm::vec3> points = t_points;

    size_t n = points.size() - 1; // size_t n = this->m_controlPoints.size() + 1;
    for (size_t r = 1; r <= n; ++r)
        for (size_t i = 0; i <= n - r; ++i)
            points[i] = (1 - t) * points[i] + t * points[i + 1];

    return points[0];
}

/*glm::vec3 TransformationAnimationBezierCurve::calculateBezierPoint(float t) const {
	// bernstein polynomial form; complexity: O(n); https://en.wikipedia.org/wiki/B%C3%A9zier_curve
    std::vector<glm::vec3> points = this->m_controlPoints; // complete list of points: start, control points, and end
    points.insert(points.begin(), this->m_start);
    points.push_back(this->m_end);

    glm::vec3 point(0.f);

    size_t n = points.size() - 1; // size_t n = this->m_controlPoints.size() + 1;
    for (size_t i = 0; i <= n; ++i) {
        // bernstein polynomial for the current i-th point; binomial coefficient: n over i
        //float bernstein = this->computeBinomialCoefficient(n, i) * static_cast<float>(std::pow(1 - t, n - i) * std::pow(t, i));
        float bernstein = this->m_binomialCoefficients[i] * static_cast<float>(std::pow(1 - t, n - i) * std::pow(t, i));
		
        point += bernstein * points[i]; // add the contribution of the point to the final position on the curve
    }

    return point;
}*/

/*///glm::vec3 TransformationAnimationBezierCurve::calculateHermitePoint(float t) const {
    size_t n = this->m_controlPoints.size();
    if (n == 0 || m_controlVectors.size() != n)
		return glm::vec3(0.f); // no control points or vectors; return zero vector

    glm::vec3 point(0.f);
    float h00, h10, h01, h11;

	// assumption: linear interpolation between points with control vectors; for simplicity
    for (size_t i = 0; i < n - 1; ++i) {
        float t2 = t * t;
        float t3 = t2 * t;

		// hermite basic functions
        h00 = 2.f * t3 - 3.f * t2 + 1.f;
        h10 = t3 - 2.f * t2 + t;
        h01 = -2.f * t3 + 3.f * t2;
        h11 = t3 - t2;

		point +=
            h00 * m_controlPoints[i]     + // point i
			h10 * m_controlVectors[i]    + // control vector for point i
			h01 * m_controlPoints[i + 1] + // point i + 1
			h11 * m_controlVectors[i + 1]; // control vector for point i + 1
    }

    return point;
}*/

/* replaced by precomputeBinomialCoefficients()
float TransformationAnimationBezierCurve::computeBinomialCoefficient(size_t n, size_t i) const {
    if (i == 0 || i == n)
        return 1.f;

    float coeff = 1.f;
    for (size_t k = 1; k <= i; ++k)
        coeff *= (n - k + 1) / static_cast<float>(k);

    return coeff;
}*/

void TransformationAnimationBezierCurve::precomputeBinomialCoefficients() {
    size_t n = this->m_controlPoints.size() + 1; // number of control points + 1 (start point)
    this->m_binomialCoefficients.resize(n + 1);

	this->m_binomialCoefficients[0] = 1.f; // n over 0; binomial coefficient for the first point
    for (size_t i = 1; i <= n; ++i)
        m_binomialCoefficients[i] = m_binomialCoefficients[i - 1] * (n - i + 1) / static_cast<float>(i);
}
