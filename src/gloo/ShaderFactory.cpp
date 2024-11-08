#include "ShaderFactory.h"
//#include "data.h"

// --- public ------------------------------------------------------------------
void ShaderFactory::addShader(const std::string& t_name, std::unique_ptr<Shader> t_shader) {
    this->m_shaders[t_name] = std::move(t_shader);
}

void ShaderFactory::addShaderProgram(const std::string& t_name, std::unique_ptr<ShaderProgram> t_program) {
    this->m_shaderPrograms[t_name] = std::move(t_program);
}

Shader* ShaderFactory::getShader(const std::string& t_name) const {
    auto it = this->m_shaders.find(t_name);
    return (it != this->m_shaders.end()) ? it->second.get() : nullptr;
}

ShaderProgram* ShaderFactory::getShaderProgram(const std::string& t_name) const {
    auto it = this->m_shaderPrograms.find(t_name);
    return (it != this->m_shaderPrograms.end()) ? it->second.get() : nullptr;
}

void ShaderFactory::createVertexShader(const std::string& t_name, const char* t_source) {
	this->addShader(t_name, std::make_unique<VertexShader>(t_source));
}

void ShaderFactory::createFragmentShader(const std::string& t_name, const char* t_source) {
	this->addShader(t_name, std::make_unique<FragmentShader>(t_source));
}

void ShaderFactory::createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader) {
	this->addShaderProgram(t_name, std::make_unique<ShaderProgram>(t_vertexShader, t_fragmentShader));
}
