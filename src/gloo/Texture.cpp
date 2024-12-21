#include "Texture.h"

// include SOIL
#include <SOIL.h>

// include the standard C++ headers
#include <iostream>

// --- public ------------------------------------------------------------------
Texture::Texture(const std::string& t_name, const std::string& t_filePath, GLenum t_textureUnit)
	: m_name(t_name) {
	// load the texture
	//glActiveTexture(GL_TEXTURE0);
	glActiveTexture(t_textureUnit);

	//this->m_ID = SOIL_load_OGL_texture(t_filePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	this->m_ID = SOIL_load_OGL_texture(t_filePath.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (this->m_ID == NULL) {
	//if (this->m_ID == 0) {
		//throw std::runtime_error("error >> could not load texture: " + t_filePath);
		fprintf(stderr, "error >> could not load texture: %s\n", t_filePath.c_str());

		exit(EXIT_FAILURE);
	}

	this->bind();
}

Texture::Texture(const std::string& t_filePath, GLenum t_textureUnit)
	: Texture("@!#?@!", t_filePath, t_textureUnit) { }

std::string Texture::getName() { return this->m_name; }

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, this->m_ID);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
