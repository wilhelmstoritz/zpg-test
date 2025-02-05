#include "AppMath.h"
#include "Config.h"

// standard c++ libraries
#include <cmath>

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//AppMath* AppMath::_instance = nullptr;
std::unique_ptr<AppMath> AppMath::_instance = nullptr;
std::mutex AppMath::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// --- public ------------------------------------------------------------------
AppMath* AppMath::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr)
		//_instance = new AppMath();
		_instance.reset(new AppMath());

	//return _instance;
	return _instance.get();
}

AppMath::~AppMath() { } // ready (for possible) future use

/* for bezier math, use precomputed binomial coefficients instead */
float AppMath::binomialCoefficient(size_t n, size_t i) const {
    //if (i > n) return 0; // binomial coefficient n over i is 0 when i > n; i must be less or equal to n; this is not necessary, because it is always called with i <= n
    if (i == 0 || i == n)
        return 1.f; // binomial coefficient n over 0 or n

    if (i > (n - i))
        i = n - i; // symmetry of the binomial coefficient; n over i = n over (n - i); reduce the number of multiplications

    float coeff = 1.f;
    for (size_t k = 1; k <= i; ++k)
        coeff *= (n - k + 1) / static_cast<float>(k);

    return coeff; // binomial coefficient n over i
}

// bezier curve
/*glm::vec3 AppMath::bezierPoint(const std::vector<glm::vec3>& t_points, float t) const {
    // de casteljau's algorithm; complexity: O(n^2); https://en.wikipedia.org/wiki/De_Casteljau%27s_algorithm
    std::vector<glm::vec3> points = t_points;

    size_t n = points.size() - 1; // number of control points
    for (size_t r = 1; r <= n; ++r)
        for (size_t i = 0; i <= n - r; ++i)
            points[i] = (1 - t) * points[i] + t * points[i + 1];

    return points[0];
}*/

glm::vec3 AppMath::bezierPoint(const std::vector<glm::vec3>& t_points, float t) const {
    // bernstein polynomial form; complexity: O(n); https://en.wikipedia.org/wiki/B%C3%A9zier_curve
    glm::vec3 point(0.f);

    size_t n = t_points.size() - 1; // degree of the bezier curve
    for (size_t i = 0; i <= n; ++i) {
        // bernstein polynomial for the current i-th point
        //float bernstein = this->binomialCoefficient(n, i) * static_cast<float>(std::pow(1 - t, n - i) * std::pow(t, i)); // obsolete; replaced by precomputed binomial coefficients
        //float bernstein = this->m_binomialCoefficients[i] * static_cast<float>(std::pow(1 - t, n - i) * std::pow(t, i)); // not universal; only for fixed degree of the bezier curve
        float bernstein = this->m_allBinomialCoefficients[n][i] * static_cast<float>(std::pow(1 - t, n - i) * std::pow(t, i));

        point += bernstein * t_points[i]; // add the contribution of the point to the final position on the curve
    }

    return point;
}

glm::vec3 AppMath::bezierTangent(const std::vector<glm::vec3>& t_points, float t) const {
    glm::vec3 T(0.f);
    size_t n = t_points.size() - 1;

    for (size_t i = 0; i < n; ++i) {
        float bernstein = this->m_allBinomialCoefficients[n - 1][i] // n - 1; the derivative is one degree lower
            * static_cast<float>(std::pow(1 - t, n - 1 - i) * std::pow(t, i));

        T += bernstein * (t_points[i + 1] - t_points[i]);
    }

	// multiply by n (degree of the curve)
    T *= static_cast<float>(n);

    return T;
}

/*///glm::vec3 AppMath::calculateHermitePoint(float t) const { /// tady je neco blbe...
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

float AppMath::bezierCurveLength(const std::vector<glm::vec3>& t_points) const {
    float length = 0.f;
    glm::vec3 previousPoint = this->bezierPoint(t_points, 0.f); // first point of the curve

    for (size_t i = 1; i <= Config::MATH_NUM_BEZIER_SAMPLES; ++i) {
        float t = static_cast<float>(i) / Config::MATH_NUM_BEZIER_SAMPLES;
        glm::vec3 currentPoint = this->bezierPoint(t_points, t);

        length += glm::length(currentPoint - previousPoint);
        previousPoint = currentPoint;
    }

    return length;
}

// --- private -----------------------------------------------------------------
AppMath::AppMath() {
	//: m_gen(std::random_device{}()) {
	// initialize random number generator
	//this->m_gen = std::mt19937(std::random_device{}());
	std::random_device rd; // seed generator; obtain a random number from hardware
	this->m_gen = std::mt19937(rd()); // seed engine; mersenne_twister_engine seeded with rd()

	// bezier curve
	//this->m_binomialCoefficients  = this->precomputeBinomialCoefficients(2u);                                              // not universal; only for fixed degree of the bezier curve
	this->m_allBinomialCoefficients = this->precomputeAllBinomialCoefficients(Config::ENVIRONMENT_FIREBALL_PATH_COMPLEXITY); // maximum degree of the bezier curve
}

// bezier curve
/* not universal; only for fixed degree of the bezier curve
// precompute binomial coefficients for n-th degree of the bezier curve
std::vector<float> AppMath::precomputeBinomialCoefficients(size_t n) {
    std::vector<float> coefs(n + 1);

    coefs[0] = 1.f; // n over 0 = 1; binomial coefficient for the first point
    for (size_t i = 1; i <= n; ++i)
        coefs[i] = coefs[i - 1] * (n - i + 1) / static_cast<float>(i);

    return coefs;
}*/

// precompute binomial coefficients for all degrees (up to n-th degree) of the bezier curve
std::vector<std::vector<float>> AppMath::precomputeAllBinomialCoefficients(size_t n) {
    std::vector<std::vector<float>> coefs(n + 1, std::vector<float>(n + 1, 0.f));

    for (size_t i = 0; i <= n; ++i) {
        coefs[i][0] = 1.f; // n over 0 = 1; binomial coefficient for the first point
        for (size_t j = 1; j <= i; ++j)
            coefs[i][j] = coefs[i - 1][j - 1] + coefs[i - 1][j]; // pascal's triangle; n over i = (n - 1) over (i - 1) + (n - 1) over i
    }

    return coefs;
}
