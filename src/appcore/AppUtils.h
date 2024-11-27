#pragma once

// standard C++ libraries
#include <mutex>
#include <string>
#include <random>
#include <type_traits>

class AppUtils {
public:
	~AppUtils();

	static AppUtils* getInstance();

	std::string getAppPath();

	template <typename T>
	T randomNumber(T t_min, T t_max);

private:
	// private constructor to avoid creating multiple instances
	AppUtils();

	// disable copy constructor and assignment operator
	AppUtils(const AppUtils&) = delete;
	AppUtils& operator=(const AppUtils&) = delete;

	// a singleton instance pointer
	//static AppUtils* _instance;
	static std::unique_ptr<AppUtils> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;

	std::mt19937 m_gen;
};

// === template implementation =================================================
// --- public ------------------------------------------------------------------
template <typename T>
T AppUtils::randomNumber(T t_min, T t_max) {
	// using concepts instead of static_assert would be more elegant;
	// the c++20 standard is not mentioned in the documentation (the default supported is c++17; god bless us at least for this :-)
	static_assert(std::is_arithmetic<T>::value, "error [AppUtils::randomNumber]: T must be an arithmetic type");

	if constexpr (std::is_integral<T>::value) { // integer type
		std::uniform_int_distribution<T> dis(t_min, t_max);

		return dis(this->m_gen);
	}
	else { // floating point type; c++17 constexpr solves (std::is_floating_point<T>::value) issues
		std::uniform_real_distribution<T> dis(t_min, t_max);

		return dis(this->m_gen);
	}
}
