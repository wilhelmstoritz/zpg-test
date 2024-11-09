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

const std::unordered_map<std::string, std::unique_ptr<ShaderProgram>>* ShaderFactory::getShaderPrograms() const {
	return &this->m_shaderPrograms;
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

void ShaderFactory::createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader, Camera* t_camera) {
    this->createShaderProgram(t_name, t_vertexShader, t_fragmentShader);
    /*
    this->getShaderProgram(t_name)->updateObserver(t_camera);
    t_camera->getObserverSubject()->addObserver(this->getShaderProgram(t_name));
    */

    auto shaderProgram = this->getShaderProgram(t_name);
    shaderProgram->updateObserver(t_camera);
    t_camera->getObserverSubject()->addObserver(shaderProgram);
}
