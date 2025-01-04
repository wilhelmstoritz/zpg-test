#include "TransformationAnimationBezierMove.h"
#include <glm/glm.hpp>
#include <cmath>

// --- public ------------------------------------------------------------------
TransformationAnimationBezierMove::TransformationAnimationBezierMove(const glm::vec3& t_start, const glm::vec3& t_end, const std::vector<glm::vec3>& t_controlPoints, float t_duration)
    : TransformationStepTranslate(t_start),
    m_start(t_start), m_end(t_end), m_controlPoints(t_controlPoints), m_duration(t_duration),
    m_elapsedTime(0.f) { }

bool TransformationAnimationBezierMove::animate() {
    this->m_deltaTime.update();
    float delta = this->m_deltaTime.getDeltaSeconds();
    this->m_elapsedTime += delta;

	float t = glm::clamp(this->m_elapsedTime / this->m_duration, 0.f, 1.f); // normalized time; interval <0, 1>
    glm::vec3 newTranslation = this->calculateBezierPoint(t);
    this->setTranslation(newTranslation);

	return t < 1.f; // animation is finished when t reaches 1; if t < 1, animation is still running
}

// --- private -----------------------------------------------------------------
glm::vec3 TransformationAnimationBezierMove::calculateBezierPoint(float t) const {
	// De Casteljau's algorithm for calculating Bezier point; https://en.wikipedia.org/wiki/De_Casteljau%27s_algorithm
    std::vector<glm::vec3> points = this->m_controlPoints;
    points.insert(points.begin(), this->m_start);
    points.push_back(this->m_end);

    int n = points.size() - 1;
    for (int r = 1; r <= n; ++r)
        for (int i = 0; i <= n - r; ++i)
            points[i] = (1 - t) * points[i] + t * points[i + 1];

    return points[0];
}
