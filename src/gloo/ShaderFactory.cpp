#include "ShaderFactory.h"

// --- public ------------------------------------------------------------------
void ShaderFactory::clearAll() {
	this->m_shaderPrograms.clear();
    this->m_shaders.clear();
}

void ShaderFactory::addShader(const std::string& t_name, std::unique_ptr<Shader> t_shader) {
    this->m_shaders[t_name] = std::move(t_shader);
}

void ShaderFactory::addShaderProgram(const std::string& t_name, std::unique_ptr<ShaderProgram> t_program) {
    this->m_shaderPrograms[t_name] = std::move(t_program);
}

void ShaderFactory::removeShader(const std::string& t_name) {
	this->m_shaders.erase(t_name);
}

void ShaderFactory::removeShaderProgram(const std::string& t_name) {
	this->m_shaderPrograms.erase(t_name);
}

Shader* ShaderFactory::getShader(const std::string& t_name) const {
    auto it = this->m_shaders.find(t_name);
    return (it != this->m_shaders.end()) ? it->second.get() : nullptr;
}

ShaderProgram* ShaderFactory::getShaderProgram(const std::string& t_name) const {
    auto it = this->m_shaderPrograms.find(t_name);
    return (it != this->m_shaderPrograms.end()) ? it->second.get() : nullptr;
}

const std::unordered_map<std::string, std::unique_ptr<ShaderProgram>>* ShaderFactory::getShaderPrograms() const {
	return &this->m_shaderPrograms;
}

Shader* ShaderFactory::createVertexShader(const std::string& t_name, const char* t_source) {
	this->addShader(t_name, std::make_unique<VertexShader>(t_source));

    return this->getShader(t_name);
}

std::unique_ptr<VertexShader> ShaderFactory::createVertexShader(const char* t_source) {
	return std::make_unique<VertexShader>(t_source);
}

Shader* ShaderFactory::createFragmentShader(const std::string& t_name, const char* t_source) {
	this->addShader(t_name, std::make_unique<FragmentShader>(t_source));

	return this->getShader(t_name);
}

std::unique_ptr<FragmentShader> ShaderFactory::createFragmentShader(const char* t_source) {
	return std::make_unique<FragmentShader>(t_source);
}

ShaderProgram* ShaderFactory::createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader) {
	this->addShaderProgram(t_name, std::make_unique<ShaderProgram>(t_vertexShader, t_fragmentShader));
    
	return this->getShaderProgram(t_name);
}

std::unique_ptr<ShaderProgram> ShaderFactory::createShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader) {
	return std::make_unique<ShaderProgram>(t_vertexShader, t_fragmentShader);
}

ShaderProgram* ShaderFactory::createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader, Camera* t_camera) {
    this->createShaderProgram(t_name, t_vertexShader, t_fragmentShader);

    auto shaderProgram = this->getShaderProgram(t_name);
    t_camera->addObserver(shaderProgram);

    return shaderProgram;
}

std::unique_ptr<ShaderProgram> ShaderFactory::createShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader, Camera* t_camera) {
	auto shaderProgram = this->createShaderProgram(t_vertexShader, t_fragmentShader);
	t_camera->addObserver(shaderProgram.get());
	return shaderProgram;
}

ShaderProgram* ShaderFactory::createShaderProgram(const std::string& t_name, const char* t_vertexShaderSourceFilename, const char* t_fragmentShaderSourceFilename) {
	this->addShaderProgram(t_name, std::make_unique<ShaderProgram>(t_vertexShaderSourceFilename, t_fragmentShaderSourceFilename));

	return this->getShaderProgram(t_name);
}

std::unique_ptr<ShaderProgram> ShaderFactory::createShaderProgram(const char* t_vertexShaderSourceFilename, const char* t_fragmentShaderSourceFilename) {
	return std::make_unique<ShaderProgram>(t_vertexShaderSourceFilename, t_fragmentShaderSourceFilename);
}
