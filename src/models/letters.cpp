#include "letters.h"

std::vector<float> LETTER_PIXEL = {
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

std::vector<std::pair<int, int>> letter_P = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 1}, {4, 2}, {4, 3}};
std::vector<std::pair<int, int>> letter_h = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 3}, {2, 3}, {3, 3}, {4, 4}, {4, 5}, {4, 6}};
std::vector<std::pair<int, int>> letter_o = {{1, 2}, {2, 2}, {3, 2}, {0, 3}, {4, 3}, {0, 4}, {4, 4}, {1, 5}, {2, 5}, {3, 5}};
std::vector<std::pair<int, int>> letter_n = {{0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 3}, {2, 3}, {3, 3}, {4, 4}, {4, 5}, {4, 6}};
std::vector<std::pair<int, int>> letter_g = {{1, 2}, {2, 2}, {3, 2}, {0, 3}, {4, 3}, {0, 4}, {4, 4}, {4, 5}, {1, 5}, {2, 5}, {3, 5}, {3, 4}};

std::vector<float> getLetter(std::vector<std::pair<int, int>>& t_letterData) {
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

int getLetterSize(std::vector<std::pair<int, int>>& t_letterData) {
	return t_letterData.size() * LETTER_PIXEL.size() / 6 + 1;
}
