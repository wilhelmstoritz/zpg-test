#pragma once

#include "Texture.h"

// standard c++ libraries
#include <mutex>
#include <memory>
#include <unordered_map>

class TextureWarehouse {
public:
	static TextureWarehouse* getInstance();
	~TextureWarehouse();

	void clearAll();

	/* likely to become private after the end of development/debugging */
	void addTexture(const std::string& t_name, std::unique_ptr<Texture> t_texture);
	/* likely to become private after the end of development/debugging */

	void removeTexture(const std::string& t_name);

	Texture* getTexture(const std::string& t_name) const;
	Texture* loadTexture(const std::string& t_name, const std::string& t_filePath, GLenum t_textureUnit);
	Texture* loadTexture(const std::string& t_name,
		const std::string& t_filePath1, const std::string& t_filePath2, const std::string& t_filePath3,
		const std::string& t_filePath4, const std::string& t_filePath5, const std::string& t_filePath6,
		GLenum t_textureUnit);
	//const std::unordered_map<std::string, std::unique_ptr<Texture>>* getTextures() const;

private:
	// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - -
	// private constructor to avoid creating multiple instances
	TextureWarehouse();

	// disable copy constructor and assignment operator
	TextureWarehouse(const TextureWarehouse&) = delete;
	TextureWarehouse& operator=(const TextureWarehouse&) = delete;

	// a singleton instance pointer
	//static TextureWarehouse* _instance;
	static std::unique_ptr<TextureWarehouse> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
};
