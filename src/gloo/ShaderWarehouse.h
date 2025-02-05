#pragma once

#include "Shader.h"
#include "ShaderProgram.h"
#include "ShaderFactory.h"

// standard c++ libraries
#include <mutex>
#include <memory>
#include <unordered_map>

class ShaderWarehouse {
public:
	static ShaderWarehouse* getInstance();
	~ShaderWarehouse();

	void clearAll();

	/* likely to become private after the end of development/debugging */
	void addShader(const std::string& t_name, std::unique_ptr<Shader> t_shader);
	void addShaderProgram(const std::string& t_name, std::unique_ptr<ShaderProgram> t_program);
	/* likely to become private after the end of development/debugging */

	void removeShader(const std::string& t_name);
	void removeShaderProgram(const std::string& t_name);

	Shader* getShader(const std::string& t_name) const;
	Shader* createVertexShader(const std::string& t_name, const char* t_source);
	Shader* createFragmentShader(const std::string& t_name, const char* t_source);

	ShaderProgram* getShaderProgram(const std::string& t_name) const;
	ShaderProgram* createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader);
	ShaderProgram* createShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader, Camera* t_camera);
	ShaderProgram* createShaderProgram(const std::string& t_name, const char* t_vertexShaderSourceFilename, const char* t_fragmentShaderSourceFilename);
	const std::unordered_map<std::string, std::unique_ptr<ShaderProgram>>* getShaderPrograms() const;

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

	ShaderFactory* m_shaderFactory;
};
