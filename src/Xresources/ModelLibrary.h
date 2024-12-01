#pragma once

// standard C++ libraries
#include <vector>

class ModelLibrary {
public:
	/*** 2nd task ***/
	static const std::vector<float> MODEL_SKYBOX_RNDCOLORS;
	static const std::vector<float> MODEL_SKYBOX_NORMALS;

	/*** other ***/
	static const std::vector<float> MODEL_BASIC_WALL;

private:
	static const float rndColorComponent(float t_baseValue);
};
