#pragma once

// standard C++ libraries
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
};

// === template implementation =================================================
#include "AppMath.tpp"
