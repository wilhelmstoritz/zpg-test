#include "ShaderFactory.h"

// --- public ------------------------------------------------------------------
std::unique_ptr<VertexShader> ShaderFactory::createVertexShader(const char* t_source) {
	return std::make_unique<VertexShader>(t_source);
}

std::unique_ptr<FragmentShader> ShaderFactory::createFragmentShader(const char* t_source) {
	return std::make_unique<FragmentShader>(t_source);
}

std::unique_ptr<ShaderProgram> ShaderFactory::createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader) {
	return std::make_unique<ShaderProgram>(t_name, t_vertexShader, t_fragmentShader);
}

std::unique_ptr<ShaderProgram> ShaderFactory::createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader, Camera* t_camera) {
	auto shaderProgram = this->createShaderProgram(t_name, t_vertexShader, t_fragmentShader);
	t_camera->addObserver(shaderProgram.get());

	return shaderProgram;
}

std::unique_ptr<ShaderProgram> ShaderFactory::createShaderProgram(const std::string& t_name, const char* t_vertexShaderSourceFilename, const char* t_fragmentShaderSourceFilename) {
	return std::make_unique<ShaderProgram>(t_name, t_vertexShaderSourceFilename, t_fragmentShaderSourceFilename);
}
