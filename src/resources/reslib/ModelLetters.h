#pragma once

// include GLM
#include <glm/vec2.hpp> // glm::vec2

// standard C++ libraries
#include <mutex>
#include <vector>
#include <string>

class ModelLetters {
public:
	static const int LETTER_XSIZE = 5;
	static const int LETTER_YSIZE = 7;

	static const std::vector<float> LETTER_PIXEL;
	static const std::vector<std::pair<int, int>> LETTER_L; // 5x7 font data; hardcoded (3rd task)
	static const std::vector<std::pair<int, int>> LETTER_P;
	static const std::vector<std::pair<int, int>> LETTER_a;
	static const std::vector<std::pair<int, int>> LETTER_b;
	static const std::vector<std::pair<int, int>> LETTER_e;
	static const std::vector<std::pair<int, int>> LETTER_h;
	static const std::vector<std::pair<int, int>> LETTER_i;
	static const std::vector<std::pair<int, int>> LETTER_o;
	static const std::vector<std::pair<int, int>> LETTER_m;
	static const std::vector<std::pair<int, int>> LETTER_n;
	static const std::vector<std::pair<int, int>> LETTER_g;
	static const std::vector<std::pair<int, int>> LETTER_r;
	static const std::vector<std::pair<int, int>> LETTER_t;

	static const std::vector<float> getLetter(const std::vector<std::pair<int, int>>& t_letterData);
	static const int getLetterSize(const std::vector<std::pair<int, int>>& t_letterData);

	static ModelLetters* getInstance();
	~ModelLetters() = default;

	const std::vector<float> getLetter(const char t_char);
	const std::vector<float> getText(const std::string& t_text);
	const int getLetterSize(const char t_char);
	const glm::uvec2 getFontSize() const;

private:
	// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - -
	// private constructor to avoid creating multiple instances
	ModelLetters();

	// disable copy constructor and assignment operator
	ModelLetters(const ModelLetters&) = delete;
	ModelLetters& operator=(const ModelLetters&) = delete;

	// a singleton instance pointer
	//static ModelLetters* _instance;
	static std::unique_ptr<ModelLetters> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	std::vector<uint8_t> m_fontData;
	glm::uvec2 m_fontSize;

	std::vector<uint8_t> loadFontData(const std::string& t_fontFilename);

	template<typename T>
	std::vector<T> getCharacterData(const char t_char);
	std::vector<std::pair<int, int>> getLetterData(const char t_char);
};
