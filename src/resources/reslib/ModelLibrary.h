#pragma once

// standard c++ libraries
#include <vector>

class ModelLibrary {
public:
	/*** 2nd task ***/
	static const std::vector<float> MODEL_SKYBOX_RNDCOLORS;
	static const std::vector<float> MODEL_SKYBOX_NORMALS;

	/*** 5th task ***/
	static const std::vector<float> MODEL_SKYCUBE;

	/*** other ***/
	static const std::vector<float> MODEL_SURFACE;
	static const std::vector<float> MODEL_SURFACE_TEXTURE;

	static const std::vector<float> MODEL_CUBE;
	static const std::vector<float> MODEL_CUBE_TEXTURE;

private:
	static const float randCC(float t_baseValue); // random color component
};
