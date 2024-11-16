#pragma once

// standard C++ libraries
#include <vector>

class ModelLibrary {
public:
	/*** 2nd task ***/
	const static std::vector<float> MODEL_SKYBOX;

private:
	const static float rndColorComponent(float t_baseValue);
};
