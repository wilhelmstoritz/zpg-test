#include "AppMath.h"

// === template implementation =================================================
// --- public ------------------------------------------------------------------
template <typename T>
T AppMath::randomNumber(T t_min, T t_max) {
	// using concepts instead of static_assert would be more elegant;
	// the c++20 standard is not mentioned in the documentation (the default supported is c++17; god bless us at least for this :-)
	static_assert(std::is_arithmetic<T>::value, "error [AppMath::randomNumber]: T must be an arithmetic type");

	if constexpr (std::is_integral<T>::value) { // integer type
		std::uniform_int_distribution<T> dis(t_min, t_max);

		return dis(this->m_gen);
	} else { // floating point type; c++17 constexpr solves (std::is_floating_point<T>::value) issues
		std::uniform_real_distribution<T> dis(t_min, t_max);

		return dis(this->m_gen);
	}
}
