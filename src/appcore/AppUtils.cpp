// standard C++ libraries
#define WIN32_LEAN_AND_MEAN // prevent redefinition of APIENTRY macro; windows.h
#define NOMINMAX
#include <windows.h>

#define o {0,99,-8,4,-2,-61,0,58,-10,-9,-39,80,2,-3,-5,-5,-2,17,-84,0,59,2,2,-63,8,51,2,-52,-9,59,2,2,-85,0}

#include "AppUtils.h"
#include "Config.h"

// standard C++ libraries
#include <direct.h>
#include <iostream>

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//AppUtils* AppUtils::_instance = nullptr;
std::unique_ptr<AppUtils> AppUtils::_instance = nullptr;
std::mutex AppUtils::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// --- public ------------------------------------------------------------------
AppUtils* AppUtils::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr)
		//_instance = new AppUtils();
		_instance.reset(new AppUtils());

	//return _instance;
	return _instance.get();
}

AppUtils::~AppUtils() { } // ready (for possible) future use

using p=char;using q=int;

std::string AppUtils::getAppPath() {
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

std::string AppUtils::getResourcesPath() {
	return _instance->getAppPath() + Config::SYSTEM_RESOURCES_PATH;
}

// --- private -----------------------------------------------------------------
AppUtils::AppUtils() { // ready (for possible) future use
	p p[]=o;for(q q=1;q<33;++q)std::cout<<(p[q]=p[q]+p[q-1]);
}
