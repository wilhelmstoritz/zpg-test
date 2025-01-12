#pragma once

// standard C++ libraries
#include <mutex>
#include <memory>
#include <string>
#include <random>
#include <type_traits>

class AppUtils {
public:
	static AppUtils* getInstance();
	~AppUtils();

	std::string getAppPath();
	std::string getResourcesPath();

	template <typename T>
	T randomNumberX(T t_min, T t_max);

private:
	// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - -
	// private constructor to avoid creating multiple instances
	AppUtils();

	// disable copy constructor and assignment operator
	AppUtils(const AppUtils&) = delete;
	AppUtils& operator=(const AppUtils&) = delete;

	// a singleton instance pointer
	//static AppUtils* _instance;
	static std::unique_ptr<AppUtils> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	std::mt19937 m_gen;
};

// === template implementation =================================================
#include "AppUtils.tpp"
