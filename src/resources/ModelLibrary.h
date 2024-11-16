#pragma once

// standard C++ libraries
#include <vector>

class ModelLibrary {
public:
	/*** 2nd task ***/
	static const std::vector<float> MODEL_SKYBOX;

private:
	static const float rndColorComponent(float t_baseValue);
};
