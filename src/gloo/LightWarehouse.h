#pragma once

// standard C++ libraries
#include <mutex>

class LightWarehouse {
public:
	static LightWarehouse* getInstance();
	~LightWarehouse();

private:
	// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - -
	// private constructor to avoid creating multiple instances
	LightWarehouse();

	// disable copy constructor and assignment operator
	LightWarehouse(const LightWarehouse&) = delete;
	LightWarehouse& operator=(const LightWarehouse&) = delete;

	// a singleton instance pointer
	//static LightWarehouse* _instance;
	static std::unique_ptr<LightWarehouse> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
};
