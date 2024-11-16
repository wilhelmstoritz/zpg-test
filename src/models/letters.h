#pragma once

// standard C++ libraries
#include <vector>

extern int LETTER_XSIZE;
extern int LETTER_YSIZE;

extern std::vector<float> LETTER_PIXEL;
extern std::vector<std::pair<int, int>> LETTER_L;
extern std::vector<std::pair<int, int>> LETTER_P;
extern std::vector<std::pair<int, int>> LETTER_a;
extern std::vector<std::pair<int, int>> LETTER_b;
extern std::vector<std::pair<int, int>> LETTER_e;
extern std::vector<std::pair<int, int>> LETTER_h;
extern std::vector<std::pair<int, int>> LETTER_i;
extern std::vector<std::pair<int, int>> LETTER_o;
extern std::vector<std::pair<int, int>> LETTER_m;
extern std::vector<std::pair<int, int>> LETTER_n;
extern std::vector<std::pair<int, int>> LETTER_g;
extern std::vector<std::pair<int, int>> LETTER_r;
extern std::vector<std::pair<int, int>> LETTER_t;

std::vector<float> getLetter(std::vector<std::pair<int, int>>& t_letterData);
int getLetterSize(std::vector<std::pair<int, int>>& t_letterData);
