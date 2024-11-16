#pragma once

// standard C++ libraries
#include <vector>

class ModelLetters {
public:
	static int LETTER_XSIZE;
	static int LETTER_YSIZE;

	static std::vector<float> LETTER_PIXEL;
	static std::vector<std::pair<int, int>> LETTER_L;
	static std::vector<std::pair<int, int>> LETTER_P;
	static std::vector<std::pair<int, int>> LETTER_a;
	static std::vector<std::pair<int, int>> LETTER_b;
	static std::vector<std::pair<int, int>> LETTER_e;
	static std::vector<std::pair<int, int>> LETTER_h;
	static std::vector<std::pair<int, int>> LETTER_i;
	static std::vector<std::pair<int, int>> LETTER_o;
	static std::vector<std::pair<int, int>> LETTER_m;
	static std::vector<std::pair<int, int>> LETTER_n;
	static std::vector<std::pair<int, int>> LETTER_g;
	static std::vector<std::pair<int, int>> LETTER_r;
	static std::vector<std::pair<int, int>> LETTER_t;

	static std::vector<float> getLetter(std::vector<std::pair<int, int>>& t_letterData);
	static int getLetterSize(std::vector<std::pair<int, int>>& t_letterData);
};
