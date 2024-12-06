#include "ShaderWarehouse.h"

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//ShaderWarehouse* ShaderWarehouse::_instance = nullptr;
std::unique_ptr<ShaderWarehouse> ShaderWarehouse::_instance = nullptr;
std::mutex ShaderWarehouse::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// --- public ------------------------------------------------------------------
ShaderWarehouse* ShaderWarehouse::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr) {
		//_instance = new ShaderWarehouse();
		_instance.reset(new ShaderWarehouse());
	}

	//return _instance;
	return _instance.get();
}

ShaderWarehouse::~ShaderWarehouse() { }
