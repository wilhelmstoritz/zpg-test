#pragma once

#include "Shader.h"
#include "ShaderProgram.h"
#include "Camera.h"

// standard c++ libraries
#include <memory>
#include <string>

class ShaderFactory {
public:
	ShaderFactory() = default;
	~ShaderFactory() = default;

	std::unique_ptr<VertexShader> createVertexShader(const char* t_source);
	std::unique_ptr<FragmentShader> createFragmentShader(const char* t_source);

	std::unique_ptr<ShaderProgram> createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader);
	std::unique_ptr<ShaderProgram> createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader, Camera* t_camera);
	std::unique_ptr<ShaderProgram> createShaderProgram(const std::string& t_name, const char* t_vertexShaderSourceFilename, const char* t_fragmentShaderSourceFilename);
};
