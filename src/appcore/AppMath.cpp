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

std::string AppMath::getAppPath() {
	// full path to the executable file
	char charBuffer[MAX_PATH];
	GetModuleFileNameA(nullptr, charBuffer, MAX_PATH); // ANSI character set should suffice; there is no reason to deal with Unicode

	/*
	// get the current working directory; find the last backslash and remove the file name
	std::string fullPath(charBuffer);
	std::string dirPath;
	size_t lastSlashIndex = fullPath.find_last_of("\\/");
	if (lastSlashIndex != std::string::npos) {
		dirPath = fullPath.substr(0, lastSlashIndex);
	}
	*/
	// get the current working directory
	if (_getcwd(charBuffer, MAX_PATH) != nullptr) {}; // prevents warning C6031: return value ignored: '_getcwd'

	return std::string(charBuffer) + "/";
}

std::string AppMath::getResourcesPath() {
	return _instance->getAppPath() + Config::SYSTEM_RESOURCES_PATH;
}

// --- private -----------------------------------------------------------------
AppMath::AppMath() {
	//: m_gen(std::random_device{}()) {
	// initialize random number generator
	//this->m_gen = std::mt19937(std::random_device{}());
	std::random_device rd; // seed generator; obtain a random number from hardware
	this->m_gen = std::mt19937(rd()); // seed engine; mersenne_twister_engine seeded with rd()
}
