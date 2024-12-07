#pragma once

// standard C++ libraries
#include <mutex>
#include <memory>

class ModelWarehouse {
public:
	static ModelWarehouse* getInstance();
	~ModelWarehouse();

private:
	// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - -
	// private constructor to avoid creating multiple instances
	ModelWarehouse();

	// disable copy constructor and assignment operator
	ModelWarehouse(const ModelWarehouse&) = delete;
	ModelWarehouse& operator=(const ModelWarehouse&) = delete;

	// a singleton instance pointer
	//static ModelWarehouse* _instance;
	static std::unique_ptr<ModelWarehouse> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
};
