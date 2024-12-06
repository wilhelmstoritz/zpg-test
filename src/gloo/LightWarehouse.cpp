#include "LightWarehouse.h"

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//LightWarehouse* LightWarehouse::_instance = nullptr;
std::unique_ptr<LightWarehouse> LightWarehouse::_instance = nullptr;
std::mutex LightWarehouse::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// --- public ------------------------------------------------------------------
LightWarehouse* LightWarehouse::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr) {
		//_instance = new LightWarehouse();
		_instance.reset(new LightWarehouse());
	}

	//return _instance;
	return _instance.get();
}

LightWarehouse::~LightWarehouse() {}
