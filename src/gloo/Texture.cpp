#include "Texture.h"

// soil
// . . win32/64 / macos platform . . . . . . . . . . . . . . . . . . . . . . . .
#if defined(_WIN32) || defined(__APPLE__)
#include <SOIL.h>
// . . linux platform  . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#elif defined(__linux__)
#include <SOIL/SOIL.h>
#endif
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// standard c++ libraries
#include <iostream>

// --- public ------------------------------------------------------------------
Texture::Texture(const std::string& t_name, const std::string& t_filePath, GLenum t_textureUnit)
	: m_name(t_name)
{
	this->m_type = GL_TEXTURE_2D;

	// load the texture
	glActiveTexture(t_textureUnit);

	//this->m_ID = SOIL_load_OGL_texture(t_filePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	this->m_ID = SOIL_load_OGL_texture(t_filePath.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (this->m_ID == 0) {
		//throw std::runtime_error("error >> could not load texture: " + t_filePath + "; " + SOIL_last_result());
		fprintf(stderr, "error >> could not load texture: %s; %s\n", t_filePath.c_str(), SOIL_last_result());

		exit(EXIT_FAILURE);
	}

	this->bind();
}

Texture::Texture(const std::string& t_name, // cubemap
	const std::string& t_filePath1, const std::string& t_filePath2, const std::string& t_filePath3,
	const std::string& t_filePath4, const std::string& t_filePath5, const std::string& t_filePath6,
	GLenum t_textureUnit)
	: m_name(t_name)
{
	this->m_type = GL_TEXTURE_CUBE_MAP;

	// load the texture
	glActiveTexture(t_textureUnit);

	//this->m_ID = SOIL_load_OGL_cubemap(t_filePath1.c_str(), t_filePath2.c_str(), t_filePath3.c_str(), t_filePath4.c_str(), t_filePath5.c_str(), t_filePath6.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	this->m_ID = SOIL_load_OGL_cubemap(t_filePath1.c_str(), t_filePath2.c_str(), t_filePath3.c_str(), t_filePath4.c_str(), t_filePath5.c_str(), t_filePath6.c_str(), SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (this->m_ID == 0) {
		//throw std::runtime_error("error >> could not load texture: " + t_filePath1 + ", " + t_filePath2 + ", " + t_filePath3 + ", " + t_filePath4 + ", " + t_filePath5 + ", " + t_filePath6);
		fprintf(stderr, "error >> could not load texture: %s, %s, %s, %s, %s, %s\n", t_filePath1.c_str(), t_filePath2.c_str(), t_filePath3.c_str(), t_filePath4.c_str(), t_filePath5.c_str(), t_filePath6.c_str());

		exit(EXIT_FAILURE);
	}

	this->bind();
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS); // smooth connection
}

Texture::Texture(const std::string& t_filePath, GLenum t_textureUnit)
	: Texture("@!#?@!", t_filePath, t_textureUnit) { }

Texture::Texture(
	const std::string& t_filePath1, const std::string& t_filePath2, const std::string& t_filePath3,
	const std::string& t_filePath4, const std::string& t_filePath5, const std::string& t_filePath6,
	GLenum t_textureUnit)
	: Texture("@!#?@!", t_filePath1, t_filePath2, t_filePath3, t_filePath4, t_filePath5, t_filePath6, t_textureUnit) { }

std::string Texture::getName() { return this->m_name; }

void Texture::bind() {
	glBindTexture(this->m_type, this->m_ID);
}

void Texture::unbind() {
	glBindTexture(this->m_type, 0);
}
