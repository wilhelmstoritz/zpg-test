#pragma once

// standard C++ libraries
#include <vector>

class ModelLetters {
public:
	static const int LETTER_XSIZE = 5;
	static const int LETTER_YSIZE = 7;

	static const std::vector<float> LETTER_PIXEL;
	static const std::vector<std::pair<int, int>> LETTER_L;
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
};
