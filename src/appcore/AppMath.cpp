// standard C++ libraries
#define WIN32_LEAN_AND_MEAN // prevent redefinition of APIENTRY macro; windows.h
#define NOMINMAX
#include <windows.h>

#include "AppMath.h"
#include "Config.h"

// standard C++ libraries
#include <direct.h>

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

// --- private -----------------------------------------------------------------
AppMath::AppMath() {
	//: m_gen(std::random_device{}()) {
	// initialize random number generator
	//this->m_gen = std::mt19937(std::random_device{}());
	std::random_device rd; // seed generator; obtain a random number from hardware
	this->m_gen = std::mt19937(rd()); // seed engine; mersenne_twister_engine seeded with rd()
}
