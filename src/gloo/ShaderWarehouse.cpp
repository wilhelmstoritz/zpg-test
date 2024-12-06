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

ShaderWarehouse::~ShaderWarehouse() {
	// cleanup
	delete this->m_shaderFactory;
}

void ShaderWarehouse::clearAll() {
	this->m_shaderPrograms.clear();
	this->m_shaders.clear();
}

void ShaderWarehouse::addShader(const std::string& t_name, std::unique_ptr<Shader> t_shader) {
	this->m_shaders[t_name] = std::move(t_shader);
}

void ShaderWarehouse::addShaderProgram(const std::string& t_name, std::unique_ptr<ShaderProgram> t_program) {
	this->m_shaderPrograms[t_name] = std::move(t_program);
}

void ShaderWarehouse::removeShader(const std::string& t_name) {
	this->m_shaders.erase(t_name);
}

void ShaderWarehouse::removeShaderProgram(const std::string& t_name) {
	this->m_shaderPrograms.erase(t_name);
}

Shader* ShaderWarehouse::getShader(const std::string& t_name) const {
	auto it = this->m_shaders.find(t_name);
	return (it != this->m_shaders.end()) ? it->second.get() : nullptr;
}

ShaderProgram* ShaderWarehouse::getShaderProgram(const std::string& t_name) const {
	auto it = this->m_shaderPrograms.find(t_name);
	return (it != this->m_shaderPrograms.end()) ? it->second.get() : nullptr;
}

const std::unordered_map<std::string, std::unique_ptr<ShaderProgram>>* ShaderWarehouse::getShaderPrograms() const {
	return &this->m_shaderPrograms;
}

// --- private -----------------------------------------------------------------
ShaderWarehouse::ShaderWarehouse() {
	this->m_shaderFactory = new ShaderFactory();
}
