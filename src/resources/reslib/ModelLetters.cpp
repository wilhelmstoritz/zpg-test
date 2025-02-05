#include "ModelLetters.h"
#include "AppUtils.h"
#include "Config.h"

// standard c++ libraries
#include <cstring>
#include <fstream>
#include <variant>
#include <type_traits>

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//ModelLetters* ModelLetters::_instance = nullptr;
std::unique_ptr<ModelLetters> ModelLetters::_instance = nullptr;
std::mutex ModelLetters::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// --- public ------------------------------------------------------------------
const std::vector<float> ModelLetters::LETTER_PIXEL = { // 36 vertices (3+3 floats per vertex; 12 triangles, 6 faces)
//  a(xyz)   normal a    b(xyz)   normal b    c(xyz)   normal c  // triangle /_\abc
	0, 0, 1, -1, 0, 0,   0, 0, 0, -1, 0, 0,   0, 1, 0, -1, 0, 0, // left side
	0, 0, 1, -1, 0, 0,   0, 1, 1, -1, 0, 0,   0, 1, 0, -1, 0, 0,
	1, 0, 1,  1, 0, 0,   1, 0, 0,  1, 0, 0,   1, 1, 0,  1, 0, 0, // right side
	1, 0, 1,  1, 0, 0,   1, 1, 1,  1, 0, 0,   1, 1, 0,  1, 0, 0,
	0, 0, 1, 0, -1, 0,   1, 0, 1, 0, -1, 0,   1, 0, 0, 0, -1, 0, // bottom side
	0, 0, 1, 0, -1, 0,   0, 0, 0, 0, -1, 0,   1, 0, 0, 0, -1, 0,
	0, 1, 1, 0,  1, 0,   1, 1, 1, 0,  1, 0,   1, 1, 0, 0,  1, 0, // top side
	0, 1, 1, 0,  1, 0,   0, 1, 0, 0,  1, 0,   1, 1, 0, 0,  1, 0,
	0, 0, 0, 0, 0, -1,   1, 0, 0, 0, 0, -1,   1, 1, 0, 0, 0, -1, // back side
	0, 0, 0, 0, 0, -1,   0, 1, 0, 0, 0, -1,   1, 1, 0, 0, 0, -1,
	0, 0, 1, 0, 0,  1,   1, 0, 1, 0, 0,  1,   1, 1, 1, 0, 0,  1, // front side
	0, 0, 1, 0, 0,  1,   0, 1, 1, 0, 0,  1,   1, 1, 1, 0, 0,  1
};

// 5x7 font data; hardcoded (3rd task)
const glm::u8vec2 ModelLetters::LETTER_SIZE = { 5, 7 }; // (x, y) pixels

const std::vector<glm::u8vec2> ModelLetters::LETTER_L = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 0}, {2, 0}, {3, 0}, {4, 0} };
const std::vector<glm::u8vec2> ModelLetters::LETTER_P = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 3}, {1, 6}, {2, 3}, {2, 6}, {3, 3}, {3, 6}, {4, 4}, {4, 5} };
const std::vector<glm::u8vec2> ModelLetters::LETTER_a = { {0, 1}, {1, 0}, {1, 2}, {1, 4}, {2, 0}, {2, 2}, {2, 4}, {3, 0}, {3, 2}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3} };
const std::vector<glm::u8vec2> ModelLetters::LETTER_b = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 0}, {1, 3}, {2, 0}, {2, 3}, {3, 0}, {3, 3}, {4, 1}, {4, 2} };
const std::vector<glm::u8vec2> ModelLetters::LETTER_e = { {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 0}, {2, 2}, {2, 4}, {3, 0}, {3, 2}, {3, 4}, {4, 0}, {4, 2}, {4, 3} };
const std::vector<glm::u8vec2> ModelLetters::LETTER_h = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 3}, {2, 3}, {3, 3}, {4, 0}, {4, 1}, {4, 2} };
const std::vector<glm::u8vec2> ModelLetters::LETTER_i = { {1, 0}, {1, 4}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 6}, {3, 0} };
const std::vector<glm::u8vec2> ModelLetters::LETTER_o = { {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 4}, {2, 0}, {2, 4}, {3, 0}, {3, 4}, {4, 1}, {4, 2}, {4, 3} };
const std::vector<glm::u8vec2> ModelLetters::LETTER_m = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, { 2, 4 }, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3} };
const std::vector<glm::u8vec2> ModelLetters::LETTER_n = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3} };
const std::vector<glm::u8vec2> ModelLetters::LETTER_g = { {0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 0}, {2, 2}, {2, 4}, {3, 0}, {3, 2}, {3, 4}, {4, 1}, {4, 2}, {4, 3} };
const std::vector<glm::u8vec2> ModelLetters::LETTER_r = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 3}, {2, 4}, {3, 4}, {4, 4} };
const std::vector<glm::u8vec2> ModelLetters::LETTER_t = { {1, 4}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {3, 0}, {3, 4}, {4, 0} };

const std::vector<float> ModelLetters::getLetter(const std::vector<glm::u8vec2>& t_letterData, const glm::ivec2& t_offset) {
	std::vector<float> result;

	// for each "3d pixel" of the letter...
	for (const auto& pos : t_letterData) { // pixel of the letter; relative coordinates in the letter grid
		float offsetX = static_cast<float>(t_offset.x + pos.x); // relative position of the "3d pixel" in the letter
		float offsetY = static_cast<float>(t_offset.y + pos.y);

		// ...adds a LETTER_PIXEL with an offset for each position
		for (size_t i = 0; i < LETTER_PIXEL.size(); i += 6) {
			result.push_back(LETTER_PIXEL[i]     + offsetX); // x
			result.push_back(LETTER_PIXEL[i + 1] + offsetY); // y
			result.push_back(LETTER_PIXEL[i + 2]);           // z
			result.push_back(LETTER_PIXEL[i + 3]);           // nx
			result.push_back(LETTER_PIXEL[i + 4]);           // ny
			result.push_back(LETTER_PIXEL[i + 5]);           // nz
		}
	}

	return result;
}

const int ModelLetters::getLetterSize(const std::vector<glm::u8vec2>& t_letterData) {
	return static_cast<int>(t_letterData.size() * LETTER_PIXEL.size() / 6);
}

ModelLetters* ModelLetters::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr)
		//_instance = new ModelLetters();
		_instance.reset(new ModelLetters());

	//return _instance;
	return _instance.get();
}

const std::vector<float> ModelLetters::getText(const std::string& t_text, const glm::ivec2& t_letterOffset) {
	std::vector<float> textData;
	this->m_lastTextSize = 0;
	glm::ivec2 letterOffset = { 0, 0 };

	for (const char& c : t_text) {
		std::vector<glm::u8vec2> letterData = getLetterData(c);
		std::vector<float> letter = ModelLetters::getLetter(letterData, letterOffset);
		this->m_lastTextSize     += ModelLetters::getLetterSize(letterData);

		textData.insert(textData.end(), letter.begin(), letter.end());

		letterOffset += t_letterOffset;
	}

	return textData;
}

const int ModelLetters::getLastTextSize() const { return this->m_lastTextSize; }

const glm::u8vec2 ModelLetters::getFontSize() const { return this->m_fontSize; }

// --- private -----------------------------------------------------------------
ModelLetters::ModelLetters() {
	this->m_fontData = this->loadFontData(AppUtils::getInstance()->getResourcesPath()
		+ Config::SYSTEM_RESOURCES_RELPATH_FONTS + Config::SYSTEM_BITMAP_FONT);

	this->m_fontSize = Config::SYSTEM_BITMAP_FONT_SIZE;
}

std::vector<uint8_t> ModelLetters::loadFontData(const std::string& t_fontFilename) {
	std::ifstream file(t_fontFilename, std::ios::binary);
	if (!file.is_open()) {
		//throw std::runtime_error("error >> failed to open font file: " + t_fontFilename);
		fprintf(stderr, "error >> failed to open font file: %s\n", t_fontFilename.c_str());

		exit(EXIT_FAILURE);
	}

	std::vector<uint8_t> fontData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return fontData;
}

template <typename T>
std::vector<T> ModelLetters::getCharacterData(const char t_char) {
	size_t charIndex = static_cast<size_t>(t_char);
	size_t bytesPerChar = static_cast<size_t>(this->m_fontSize.x) * this->m_fontSize.y / 8; // grid of pixels; 1 bit per pixel means 8 pixels per byte

	std::vector<T> charData(bytesPerChar / sizeof(T));
	std::memcpy(charData.data(), this->m_fontData.data() + charIndex * bytesPerChar, bytesPerChar);

	return charData;
}

std::vector<glm::u8vec2> ModelLetters::getLetterData(const char t_char) {
	std::variant<std::vector<uint8_t>, std::vector<uint16_t>> charData;
	if (this->m_fontSize.x == 8)
		charData = this->getCharacterData<uint8_t>(t_char);  // 8xY font
	else
		charData = this->getCharacterData<uint16_t>(t_char); // 16xY font

	std::vector<glm::u8vec2> letterData;
	std::visit([&letterData](auto&& arg) {
		using T = typename std::decay_t<decltype(arg)>::value_type; // the type of the vector elements; uint8_t or uint16_t

		size_t xsize = sizeof(T) * 8; // character width;  8 pixels per byte
		size_t ysize = arg.size();    // character height; number of T elements

		for (size_t i = 0; i < ysize; ++i) {
			T data = arg[i];

			for (size_t bit = 0; bit < xsize; ++bit) {
				if (data & (1 << (xsize - bit - 1))) // if the bit is set...; most significant bit is on the left, least significant bit is on the right; the first 'pixel' is the most significant bit
					letterData.emplace_back(bit, ysize - i - 1); // ...add the 'pixel' to the letter data; more efficient than push_back({ x, y }) here; raw font data (0, 0) is the top-left corner, the letter data (0, 0) is the bottom-left corner
			}
		}
	}, charData);

	return letterData;
}
