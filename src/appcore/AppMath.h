#pragma once

// glm
#include <glm/glm.hpp>

// standard c++ libraries
#include <mutex>
#include <memory>
#include <vector>
#include <random>
#include <type_traits>

class AppMath {
public:
	static AppMath* getInstance();
	~AppMath();

	template <typename T>
	T randomNumber(T t_min, T t_max);

	float binomialCoefficient(size_t n, size_t i) const;

	// bezier curve
	glm::vec3 bezierPoint  (const std::vector<glm::vec3>& t_points, float t) const;
	glm::vec3 bezierTangent(const std::vector<glm::vec3>& t_points, float t) const;
	///glm::vec3 calculateHermitePoint(float t) const;
	float bezierCurveLength(const std::vector<glm::vec3>& controlPoints) const;

private:
	// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - -
	// private constructor to avoid creating multiple instances
	AppMath();

	// disable copy constructor and assignment operator
	AppMath(const AppMath&) = delete;
	AppMath& operator=(const AppMath&) = delete;

	// a singleton instance pointer
	//static AppMath* _instance;
	static std::unique_ptr<AppMath> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	std::mt19937 m_gen;

	// bezier curve
	//std::vector<float>            m_binomialCoefficients;    // not universal; only for fixed degree of the bezier curve
	std::vector<std::vector<float>> m_allBinomialCoefficients; // precomputed binomial coefficients for all degrees (up to n-th degree) of the bezier curve

	//std::vector<float>            precomputeBinomialCoefficients(size_t n); // not universal; only for fixed degree of the bezier curve
	std::vector<std::vector<float>> precomputeAllBinomialCoefficients(size_t n);
};

// === template implementation =================================================
#include "AppMath.tpp"
