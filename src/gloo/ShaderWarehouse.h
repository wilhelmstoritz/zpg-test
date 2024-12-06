#pragma once

#include "Shader.h"
#include "ShaderProgram.h"

// standard C++ libraries
#include <mutex>
#include <unordered_map>

class ShaderWarehouse {
public:
	~ShaderWarehouse();

	static ShaderWarehouse* getInstance();

private:
	// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - -
	// private constructor to avoid creating multiple instances
	ShaderWarehouse();

	// disable copy constructor and assignment operator
	ShaderWarehouse(const ShaderWarehouse&) = delete;
	ShaderWarehouse& operator=(const ShaderWarehouse&) = delete;

	// a singleton instance pointer
	//static ShaderWarehouse* _instance;
	static std::unique_ptr<ShaderWarehouse> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders; // also retention for lifetime management
	std::unordered_map<std::string, std::unique_ptr<ShaderProgram>> m_shaderPrograms;
};
