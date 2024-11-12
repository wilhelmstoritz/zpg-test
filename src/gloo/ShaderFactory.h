#pragma once

#include "Shader.h"
#include "ShaderProgram.h"
#include "Camera.h"

// include the standard C++ headers
#include <unordered_map>
#include <memory>
#include <string>

class ShaderFactory {
public:
	ShaderFactory() = default;
	//~ShaderFactory() = default;

	void clearAll();

	/* likely to become private after the end of development/debugging */
	void addShader(const std::string& t_name, std::unique_ptr<Shader> t_shader);
	void addShaderProgram(const std::string& t_name, std::unique_ptr<ShaderProgram> t_program);
	/* likely to become private after the end of development/debugging */

	void removeShader(const std::string& t_name);
	void removeShaderProgram(const std::string& t_name);

	Shader* getShader(const std::string& t_name) const;
	ShaderProgram* getShaderProgram(const std::string& t_name) const;
	const std::unordered_map<std::string, std::unique_ptr<ShaderProgram>>* getShaderPrograms() const;

	Shader* createVertexShader(const std::string& t_name, const char* t_source);
	Shader* createFragmentShader(const std::string& t_name, const char* t_source);
	ShaderProgram* createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader);
	ShaderProgram* createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader, Camera* t_camera);

private:
	std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders; // also retention for lifetime management
	std::unordered_map<std::string, std::unique_ptr<ShaderProgram>> m_shaderPrograms;
};
