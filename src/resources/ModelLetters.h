#pragma once

// standard C++ libraries
#include <vector>

class ModelLetters {
public:
	const static int LETTER_XSIZE = 5;
	const static int LETTER_YSIZE = 7;

	const static std::vector<float> LETTER_PIXEL;
	const static std::vector<std::pair<int, int>> LETTER_L;
	const static std::vector<std::pair<int, int>> LETTER_P;
	const static std::vector<std::pair<int, int>> LETTER_a;
	const static std::vector<std::pair<int, int>> LETTER_b;
	const static std::vector<std::pair<int, int>> LETTER_e;
	const static std::vector<std::pair<int, int>> LETTER_h;
	const static std::vector<std::pair<int, int>> LETTER_i;
	const static std::vector<std::pair<int, int>> LETTER_o;
	const static std::vector<std::pair<int, int>> LETTER_m;
	const static std::vector<std::pair<int, int>> LETTER_n;
	const static std::vector<std::pair<int, int>> LETTER_g;
	const static std::vector<std::pair<int, int>> LETTER_r;
	const static std::vector<std::pair<int, int>> LETTER_t;

	const static std::vector<float> getLetter(const std::vector<std::pair<int, int>>& t_letterData);
	const static int getLetterSize(const std::vector<std::pair<int, int>>& t_letterData);
};
