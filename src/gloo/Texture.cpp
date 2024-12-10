#include "Texture.h"

// include SOIL
#include <SOIL.h>

// --- public ------------------------------------------------------------------
Texture::Texture(const std::string& t_name, const std::string& t_filePath)
	: m_name(t_name) {
	// load the texture
	this->m_ID = SOIL_load_OGL_texture(t_filePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if (this->m_ID == 0) {
		//throw std::runtime_error("Texture loading failed: " + t_filePath);
	}
}

Texture::Texture(const std::string& t_filePath)
	: Texture("@!#?@!", t_filePath) {
}
