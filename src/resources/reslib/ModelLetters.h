#pragma once

// glm
#include <glm/vec2.hpp> // glm::vec2

// standard c++ libraries
#include <memory>
#include <mutex>
#include <vector>
#include <string>

class ModelLetters {
public:
	static const std::vector<float> LETTER_PIXEL;

	static const glm::u8vec2 LETTER_SIZE; // 5x7 font data; hardcoded (3rd task)
	static const std::vector<glm::u8vec2> LETTER_L;
	static const std::vector<glm::u8vec2> LETTER_P;
	static const std::vector<glm::u8vec2> LETTER_a;
	static const std::vector<glm::u8vec2> LETTER_b;
	static const std::vector<glm::u8vec2> LETTER_e;
	static const std::vector<glm::u8vec2> LETTER_h;
	static const std::vector<glm::u8vec2> LETTER_i;
	static const std::vector<glm::u8vec2> LETTER_o;
	static const std::vector<glm::u8vec2> LETTER_m;
	static const std::vector<glm::u8vec2> LETTER_n;
	static const std::vector<glm::u8vec2> LETTER_g;
	static const std::vector<glm::u8vec2> LETTER_r;
	static const std::vector<glm::u8vec2> LETTER_t;

	static const std::vector<float> getLetter(const std::vector<glm::u8vec2>& t_letterData, const glm::ivec2& t_offset = { 0, 0 });
	static const int getLetterSize(const std::vector<glm::u8vec2>& t_letterData); // int instead of size_t; don't need to cast to (GL)int/GLsizei later

	static ModelLetters* getInstance();
	~ModelLetters() = default;

	const std::vector<float> getText(const std::string& t_text, const glm::ivec2& t_letterOffset);
	const int getLastTextSize() const; // int instead of size_t; don't need to cast to (GL)int/GLsizei later
	const glm::u8vec2 getFontSize() const;

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
	glm::u8vec2 m_fontSize;

	int m_lastTextSize; // int instead of size_t; don't need to cast to (GL)int/GLsizei later

	std::vector<uint8_t> loadFontData(const std::string& t_fontFilename);

	template <typename T>
	std::vector<T> getCharacterData(const char t_char);
	std::vector<glm::u8vec2> getLetterData(const char t_char);
};
