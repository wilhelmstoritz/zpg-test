#include "ModelLetters.h"
#include "AppUtils.h"
#include "Config.h"

// standard C++ libraries
#include <fstream>

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//ModelLetters* ModelLetters::_instance = nullptr;
std::unique_ptr<ModelLetters> ModelLetters::_instance = nullptr;
std::mutex ModelLetters::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// --- public ------------------------------------------------------------------
const std::vector<float> ModelLetters::LETTER_PIXEL = { // 36 vertices (3+3 floats per vertex; 12 triangles, 6 faces)
//  X{xyz}   normal x    Y{xyz}   normal y    Z{xyz}   normal z
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
const std::vector<std::pair<int, int>> ModelLetters::LETTER_L = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 0}, {2, 0}, {3, 0}, {4, 0} };
const std::vector<std::pair<int, int>> ModelLetters::LETTER_P = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 3}, {1, 6}, {2, 3}, {2, 6}, {3, 3}, {3, 6}, {4, 4}, {4, 5} };
const std::vector<std::pair<int, int>> ModelLetters::LETTER_a = { {0, 1}, {1, 0}, {1, 2}, {1, 4}, {2, 0}, {2, 2}, {2, 4}, {3, 0}, {3, 2}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3} };
const std::vector<std::pair<int, int>> ModelLetters::LETTER_b = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 0}, {1, 3}, {2, 0}, {2, 3}, {3, 0}, {3, 3}, {4, 1}, {4, 2} };
const std::vector<std::pair<int, int>> ModelLetters::LETTER_e = { {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 0}, {2, 2}, {2, 4}, {3, 0}, {3, 2}, {3, 4}, {4, 0}, {4, 2}, {4, 3} };
const std::vector<std::pair<int, int>> ModelLetters::LETTER_h = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 3}, {2, 3}, {3, 3}, {4, 0}, {4, 1}, {4, 2} };
const std::vector<std::pair<int, int>> ModelLetters::LETTER_i = { {1, 0}, {1, 4}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 6}, {3, 0} };
const std::vector<std::pair<int, int>> ModelLetters::LETTER_o = { {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 4}, {2, 0}, {2, 4}, {3, 0}, {3, 4}, {4, 1}, {4, 2}, {4, 3} };
const std::vector<std::pair<int, int>> ModelLetters::LETTER_m = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, { 2, 4 }, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3} };
const std::vector<std::pair<int, int>> ModelLetters::LETTER_n = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3} };
const std::vector<std::pair<int, int>> ModelLetters::LETTER_g = { {0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 0}, {2, 2}, {2, 4}, {3, 0}, {3, 2}, {3, 4}, {4, 1}, {4, 2}, {4, 3} };
const std::vector<std::pair<int, int>> ModelLetters::LETTER_r = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 3}, {2, 4}, {3, 4}, {4, 4} };
const std::vector<std::pair<int, int>> ModelLetters::LETTER_t = { {1, 4}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {3, 0}, {3, 4}, {4, 0} };

const std::vector<float> ModelLetters::getLetter(const std::vector<std::pair<int, int>>& t_letterData) {
	std::vector<float> result;

	// for each "3d pixel" of the letter...
	for (const auto& pos : t_letterData) {
		float offsetX = static_cast<float>(pos.first); // x coord in the grid 8x8
		float offsetY = static_cast<float>(pos.second); // y coord in the grid 8x8

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

const int ModelLetters::getLetterSize(const std::vector<std::pair<int, int>>& t_letterData) {
	return static_cast<int>(t_letterData.size() * LETTER_PIXEL.size() / 6 + 1);
}

ModelLetters* ModelLetters::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr) {
		//_instance = new ModelLetters();
		_instance.reset(new ModelLetters());
	}

	//return _instance;
	return _instance.get();
}

const std::vector<float> ModelLetters::getLetter(const char t_char) {
	std::vector<std::pair<int, int>> letterData = getLetterData(t_char);

	return ModelLetters::getLetter(letterData);
}

const int ModelLetters::getLetterSize(const char t_char) {
	std::vector<std::pair<int, int>> letterData = getLetterData(t_char);

	return ModelLetters::getLetterSize(letterData);
}

// --- private -----------------------------------------------------------------
std::vector<uint8_t> ModelLetters::loadFontData(const std::string& t_fontFilename) {
	std::ifstream file(t_fontFilename, std::ios::binary);

	/*std::vector<uint8_t> fontData;

	if (file.is_open()) {
		file.seekg(0, std::ios::end);
		size_t size = static_cast<size_t>(file.tellg());
		fontData.resize(size);

		file.seekg(0, std::ios::beg);
		file.read(reinterpret_cast<char*>(fontData.data()), size);
		file.close();
	}*/

	if (!file.is_open()) {
		//throw std::runtime_error("error >> failed to open font file: " + t_fontFilename);
		fprintf(stderr, "error >> failed to open font file: %s\n", t_fontFilename.c_str());

		exit(EXIT_FAILURE);
	}

	std::vector<uint8_t> fontData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return fontData;
}

std::vector<uint8_t> ModelLetters::getCharacterData(const std::vector<uint8_t>& t_fontData, const char t_char) {
	int charIndex = static_cast<int>(t_char) - 32; // ASCII code of the first character in the font data; 32 = ' ' (space) i.e. the first character
	int charWidth = 8; // 8x8 grid of pixels
	int charHeight = 8;
	int bytesPerChar = charWidth * charHeight / 8; // 1 bit per pixel

	std::vector<uint8_t> charData(charHeight);
	for (int i = 0; i < charHeight; ++i)
		charData[i] = t_fontData[charIndex * bytesPerChar + i];

	return charData;
}

std::vector<std::pair<int, int>> ModelLetters::getLetterData(const std::vector<uint8_t>& t_charData) {
	std::vector<std::pair<int, int>> letterData;
	for (size_t i = 0; i < t_charData.size(); ++i) {
		uint8_t byte = t_charData[i];

		for (int j = 0; j < 8; ++j) {
			if (byte & (1 << (7 - j))) // if the j-th bit is set
				letterData.emplace_back(i, j); // adds the pixel to the letter data; more efficient than push_back({ i, j }) here
		}
	}

	return letterData;
}

std::vector<std::pair<int, int>> ModelLetters::getLetterData(const char t_char) {
	std::string fontResourcesPath = AppUtils::getInstance()->getResourcesPath() + Config::SYSTEM_RESOURCES_RELPATH_FONTS;

	std::vector<uint8_t> fontData = this->loadFontData(fontResourcesPath + Config::SYSTEM_BITMAP_FONT);
	std::vector<uint8_t> charData = this->getCharacterData(fontData, t_char);

	return this->getLetterData(charData);
}
