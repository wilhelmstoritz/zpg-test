#pragma once

// standard C++ libraries
#include <vector>

class ModelLibrary {
public:
	/*** 2nd task ***/
	static std::vector<float> MODEL_SKYBOX;

private:
	static float rndColorComponent(float t_baseValue);
};
