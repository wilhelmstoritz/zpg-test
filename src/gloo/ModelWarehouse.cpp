#include "ModelWarehouse.h"

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//ModelWarehouse* ModelWarehouse::_instance = nullptr;
std::unique_ptr<ModelWarehouse> ModelWarehouse::_instance = nullptr;
std::mutex ModelWarehouse::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// --- public ------------------------------------------------------------------
ModelWarehouse* ModelWarehouse::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr) {
		//_instance = new ModelWarehouse();
		_instance.reset(new ModelWarehouse());
	}

	//return _instance;
	return _instance.get();
}

ModelWarehouse::~ModelWarehouse() {}
