#pragma once

// standard C++ libraries
#include <vector>

extern std::vector<float> LETTER_PIXEL;
extern std::vector<std::pair<int, int>> letter_P;
extern std::vector<std::pair<int, int>> letter_h;
extern std::vector<std::pair<int, int>> letter_o;
extern std::vector<std::pair<int, int>> letter_n;
extern std::vector<std::pair<int, int>> letter_g;

std::vector<float> getLetter(std::vector<std::pair<int, int>>& t_letterData);
int getLetterSize(std::vector<std::pair<int, int>>& t_letterData);
