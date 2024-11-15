#pragma once

// standard C++ libraries
#include <vector>

extern std::vector<float> LETTER_PIXEL;
extern std::vector<std::pair<int, int>> letter_L;
extern std::vector<std::pair<int, int>> letter_P;
extern std::vector<std::pair<int, int>> letter_a;
extern std::vector<std::pair<int, int>> letter_b;
extern std::vector<std::pair<int, int>> letter_e;
extern std::vector<std::pair<int, int>> letter_h;
extern std::vector<std::pair<int, int>> letter_i;
extern std::vector<std::pair<int, int>> letter_o;
extern std::vector<std::pair<int, int>> letter_m;
extern std::vector<std::pair<int, int>> letter_n;
extern std::vector<std::pair<int, int>> letter_g;
extern std::vector<std::pair<int, int>> letter_r;
extern std::vector<std::pair<int, int>> letter_t;

std::vector<float> getLetter(std::vector<std::pair<int, int>>& t_letterData);
int getLetterSize(std::vector<std::pair<int, int>>& t_letterData);
