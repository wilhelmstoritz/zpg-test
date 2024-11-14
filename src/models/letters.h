#pragma once

// standard C++ libraries
#include <vector>

extern std::vector<float> LETTER_PIXEL;
extern std::vector<std::pair<int, int>> letterH;
extern std::vector<std::pair<int, int>> letterMOJE;

std::vector<float> getLetter(std::vector<std::pair<int, int>>& t_letterData);
int getLetterSize(std::vector<std::pair<int, int>>& t_letterData);
