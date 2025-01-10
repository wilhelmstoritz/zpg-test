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
	if (_instance == nullptr)
		//_instance = new ShaderWarehouse();
		_instance.reset(new ShaderWarehouse());

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

Shader* ShaderWarehouse::createVertexShader(const std::string& t_name, const char* t_source) {
	auto shader = this->getShader(t_name);
	if (shader == nullptr) {
		this->addShader(t_name, this->m_shaderFactory->createVertexShader(t_source));

		shader = this->getShader(t_name);
	}

	return shader;
}

Shader* ShaderWarehouse::createFragmentShader(const std::string& t_name, const char* t_source) {
	auto shader = this->getShader(t_name);
	if (shader == nullptr) {
		this->addShader(t_name, this->m_shaderFactory->createFragmentShader(t_source));

		shader = this->getShader(t_name);
	}

	return shader;
}

ShaderProgram* ShaderWarehouse::getShaderProgram(const std::string& t_name) const {
	auto it = this->m_shaderPrograms.find(t_name);

	return (it != this->m_shaderPrograms.end()) ? it->second.get() : nullptr;
}

ShaderProgram* ShaderWarehouse::createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader) {
	auto shaderProgram = this->getShaderProgram(t_name);
	if (shaderProgram == nullptr) {
		this->addShaderProgram(t_name, this->m_shaderFactory->createShaderProgram(t_name, t_vertexShader, t_fragmentShader));

		shaderProgram = this->getShaderProgram(t_name);
	}

	return shaderProgram;
}

ShaderProgram* ShaderWarehouse::createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader, Camera* t_camera) {
	auto shaderProgram = this->getShaderProgram(t_name);
	if (shaderProgram == nullptr) {
		this->addShaderProgram(t_name, this->m_shaderFactory->createShaderProgram(t_name, t_vertexShader, t_fragmentShader, t_camera));

		shaderProgram = this->getShaderProgram(t_name);
	}

	return shaderProgram;
}

ShaderProgram* ShaderWarehouse::createShaderProgram(const std::string& t_name, const char* t_vertexShaderSourceFilename, const char* t_fragmentShaderSourceFilename) {
	auto shaderProgram = this->getShaderProgram(t_name);
	if (shaderProgram == nullptr) {
		this->addShaderProgram(t_name, this->m_shaderFactory->createShaderProgram(t_name, t_vertexShaderSourceFilename, t_fragmentShaderSourceFilename));

		shaderProgram = this->getShaderProgram(t_name);
	}

	return shaderProgram;
}

const std::unordered_map<std::string, std::unique_ptr<ShaderProgram>>* ShaderWarehouse::getShaderPrograms() const {
	return &this->m_shaderPrograms;
}

// --- private -----------------------------------------------------------------
ShaderWarehouse::ShaderWarehouse() {
	this->m_shaderFactory = new ShaderFactory();
}
