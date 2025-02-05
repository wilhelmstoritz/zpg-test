#pragma once

#include "Observer.h"
#include "Camera.h"
#include "Light.h"
#include "VertexShader.h"
#include "FragmentShader.h"
// 3rd party
#include "ShaderLoader.h"

// glm
#include <glm/mat4x4.hpp> // glm::mat4

class ShaderProgram : public ShaderLoader, public Observer<Camera>, public Observer<Light> {
public:
	ShaderProgram(const std::string& t_name, const Shader& t_vertexShader, const Shader& t_fragmentShader);
	ShaderProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader);
	ShaderProgram(const std::string& t_name, const char* t_vertexShaderSourceFilename, const char* t_fragmentShaderSourceFilename);
	ShaderProgram(const char* t_vertexShaderSourceFilename, const char* t_fragmentShaderSourceFilename);
	~ShaderProgram();

	std::string getName();
	/* debugging purposes only
	GLuint getID() const;*/

	void use() const;

	template <typename T>
	void setUniform(const GLchar* t_name, const T& t_value) const;

	template <typename T>
	void follow();
	//void follow(void* t_anything = nullptr); // debugging purposes only

	//void deleteShader(); // ShaderLoader has this method; apply only to objects created with ShaderLoader; 2do: make it common for all ShaderPrograms

protected:
	virtual void processSubject(Camera* t_camera) override;
	virtual void processSubject(Light* t_light) override;

private:
	enum class shaderModeE {
		ALL_COMPONENTS = 0,
		AMBIENT_ONLY   = 1,
		DIFFUSE_ONLY   = 2,
		SPECULAR_ONLY  = 3
	};

	std::string m_name;
	//GLuint m_ID;
	GLuint& m_ID = this->shaderProgramID; // adapted to the need to use ShaderLoader

	GLuint m_ssboID; // corresponding shader storage buffer object
	size_t m_ssboLights; // number of lights in the SSBO

	void linkProgram(const Shader& t_vertexShader, const Shader& t_fragmentShader);
	void setSSBO(Light* t_light);
	void createSSBO(size_t t_size);

	std::string getIndexedName(const char* t_name, const int t_index);
};

// === template implementation =================================================
#include "ShaderProgram.tpp"
