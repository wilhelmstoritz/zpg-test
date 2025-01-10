#include "TextureWarehouse.h"

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//TextureWarehouse* TextureWarehouse::_instance = nullptr;
std::unique_ptr<TextureWarehouse> TextureWarehouse::_instance = nullptr;
std::mutex TextureWarehouse::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// --- public ------------------------------------------------------------------
TextureWarehouse* TextureWarehouse::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr)
		//_instance = new TextureWarehouse();
		_instance.reset(new TextureWarehouse());

	//return _instance;
	return _instance.get();
}

TextureWarehouse::~TextureWarehouse() {
	// cleanup
	//delete this->m_textureFactory;
}

void TextureWarehouse::clearAll() {
	this->m_textures.clear();
}

void TextureWarehouse::addTexture(const std::string& t_name, std::unique_ptr<Texture> t_texture) {
	this->m_textures[t_name] = std::move(t_texture);
}

void TextureWarehouse::removeTexture(const std::string& t_name) {
	this->m_textures.erase(t_name);
}

Texture* TextureWarehouse::getTexture(const std::string& t_name) const {
	auto it = this->m_textures.find(t_name);

	return (it != this->m_textures.end()) ? it->second.get() : nullptr;
}

Texture* TextureWarehouse::loadTexture(const std::string& t_name, const std::string& t_filePath, GLenum t_textureUnit) {
	auto texture = this->getTexture(t_name);
	if (texture == nullptr) {
		this->addTexture(t_name, std::make_unique<Texture>(t_name, t_filePath, t_textureUnit));

		texture = this->getTexture(t_name);
	}

	return texture;
}

Texture* TextureWarehouse::loadTexture(const std::string& t_name,
	const std::string& t_filePath1, const std::string& t_filePath2, const std::string& t_filePath3,
	const std::string& t_filePath4, const std::string& t_filePath5, const std::string& t_filePath6,
	GLenum t_textureUnit) {
	auto texture = this->getTexture(t_name);
	if (texture == nullptr) {
		this->addTexture(t_name, std::make_unique<Texture>(t_name,
			t_filePath1, t_filePath2, t_filePath3, t_filePath4, t_filePath5, t_filePath6,
			t_textureUnit));

		texture = this->getTexture(t_name);
	}

	return texture;
}

/*
const std::unordered_map<std::string, std::unique_ptr<Texture>>* TextureWarehouse::getTextures() const {
	return &this->m_textures;
}
*/

// --- private -----------------------------------------------------------------
TextureWarehouse::TextureWarehouse() {
	//this->m_textureFactory = new TextureFactory();
}
