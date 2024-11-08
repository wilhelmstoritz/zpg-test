#pragma once

#include "Shader.h"
#include "ShaderProgram.h"

// include the standard C++ headers
#include <unordered_map>
#include <memory>
#include <string>

class ShaderFactory {
public:
	ShaderFactory() = default;
	//~ShaderFactory() = default;

	/* will become private after the end of development/debugging */
	void addShader(const std::string& t_name, std::unique_ptr<Shader> t_shader);
	void addShaderProgram(const std::string& t_name, std::unique_ptr<ShaderProgram> t_program);
	/* will become private after the end of development/debugging */

	Shader* getShader(const std::string& t_name) const;
	ShaderProgram* getShaderProgram(const std::string& t_name) const;

	void createVertexShader(const std::string& t_name, const char* t_source);
	void createFragmentShader(const std::string& t_name, const char* t_source);
	void createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader);

private:
	std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders; // also retention for lifetime management
	std::unordered_map<std::string, std::unique_ptr<ShaderProgram>> m_shaderPrograms;
};
