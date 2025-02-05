#pragma once

// glew
#include <GL/glew.h>

// standard c++ libraries
#include <string>

class Texture {
public:
	Texture(const std::string& t_name, const std::string& t_filePath, GLenum t_textureUnit);
	Texture(const std::string& t_name, // cubemap
		const std::string& t_filePath1, const std::string& t_filePath2, const std::string& t_filePath3,
		const std::string& t_filePath4, const std::string& t_filePath5, const std::string& t_filePath6,
		GLenum t_textureUnit);
	Texture(const std::string& t_filePath, GLenum t_textureUnit);
	Texture(
		const std::string& t_filePath1, const std::string& t_filePath2, const std::string& t_filePath3,
		const std::string& t_filePath4, const std::string& t_filePath5, const std::string& t_filePath6,
		GLenum t_textureUnit);
	
	std::string getName();
	
	void bind();
	void unbind();

private:
	std::string m_name;
	GLuint m_ID;

	GLenum m_type;
};
