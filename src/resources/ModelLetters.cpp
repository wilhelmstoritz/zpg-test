#include "ModelLetters.h"

// --- public ------------------------------------------------------------------
int ModelLetters::LETTER_XSIZE = 5;
int ModelLetters::LETTER_YSIZE = 7;

std::vector<float> ModelLetters::LETTER_PIXEL = {
//  X{xyz}   normal x    Y{xyz}   normal y    Z{xyz}   normal z
	0, 0, 1, -1, 0, 0,   0, 0, 0, -1, 0, 0,   0, 1, 0, -1, 0, 0, // left
	0, 0, 1, -1, 0, 0,   0, 1, 1, -1, 0, 0,   0, 1, 0, -1, 0, 0,
	1, 0, 1,  1, 0, 0,   1, 0, 0,  1, 0, 0,   1, 1, 0,  1, 0, 0, // right
	1, 0, 1,  1, 0, 0,   1, 1, 1,  1, 0, 0,   1, 1, 0,  1, 0, 0,
	0, 0, 1, 0, -1, 0,   1, 0, 1, 0, -1, 0,   1, 0, 0, 0, -1, 0, // bottom
	0, 0, 1, 0, -1, 0,   0, 0, 0, 0, -1, 0,   1, 0, 0, 0, -1, 0,
	0, 1, 1, 0,  1, 0,   1, 1, 1, 0,  1, 0,   1, 1, 0, 0,  1, 0, // top
	0, 1, 1, 0,  1, 0,   0, 1, 0, 0,  1, 0,   1, 1, 0, 0,  1, 0,
	0, 0, 0, 0, 0, -1,   1, 0, 0, 0, 0, -1,   1, 1, 0, 0, 0, -1, // back
	0, 0, 0, 0, 0, -1,   0, 1, 0, 0, 0, -1,   1, 1, 0, 0, 0, -1,
	0, 0, 1, 0, 0,  1,   1, 0, 1, 0, 0,  1,   1, 1, 1, 0, 0,  1, // front
	0, 0, 1, 0, 0,  1,   0, 1, 1, 0, 0,  1,   1, 1, 1, 0, 0,  1
};

std::vector<std::pair<int, int>> ModelLetters::LETTER_L = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 0}, {2, 0}, {3, 0}, {4, 0} };
std::vector<std::pair<int, int>> ModelLetters::LETTER_P = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 3}, {1, 6}, {2, 3}, {2, 6}, {3, 3}, {3, 6}, {4, 4}, {4, 5} };
std::vector<std::pair<int, int>> ModelLetters::LETTER_a = { {0, 1}, {1, 0}, {1, 2}, {1, 4}, {2, 0}, {2, 2}, {2, 4}, {3, 0}, {3, 2}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3} };
std::vector<std::pair<int, int>> ModelLetters::LETTER_b = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 0}, {1, 3}, {2, 0}, {2, 3}, {3, 0}, {3, 3}, {4, 1}, {4, 2} };
std::vector<std::pair<int, int>> ModelLetters::LETTER_e = { {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 0}, {2, 2}, {2, 4}, {3, 0}, {3, 2}, {3, 4}, {4, 0}, {4, 2}, {4, 3} };
std::vector<std::pair<int, int>> ModelLetters::LETTER_h = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 3}, {2, 3}, {3, 3}, {4, 0}, {4, 1}, {4, 2} };
std::vector<std::pair<int, int>> ModelLetters::LETTER_i = { {1, 0}, {1, 4}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 6}, {3, 0} };
std::vector<std::pair<int, int>> ModelLetters::LETTER_o = { {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 4}, {2, 0}, {2, 4}, {3, 0}, {3, 4}, {4, 1}, {4, 2}, {4, 3} };
std::vector<std::pair<int, int>> ModelLetters::LETTER_m = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, { 2, 4 }, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3} };
std::vector<std::pair<int, int>> ModelLetters::LETTER_n = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3} };
std::vector<std::pair<int, int>> ModelLetters::LETTER_g = { {0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 0}, {2, 2}, {2, 4}, {3, 0}, {3, 2}, {3, 4}, {4, 1}, {4, 2}, {4, 3} };
std::vector<std::pair<int, int>> ModelLetters::LETTER_r = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 3}, {2, 4}, {3, 4}, {4, 4} };
std::vector<std::pair<int, int>> ModelLetters::LETTER_t = { {1, 4}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {3, 0}, {3, 4}, {4, 0} };

std::vector<float> ModelLetters::getLetter(std::vector<std::pair<int, int>>& t_letterData) {
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

int ModelLetters::getLetterSize(std::vector<std::pair<int, int>>& t_letterData) {
	return t_letterData.size() * LETTER_PIXEL.size() / 6 + 1;
}
