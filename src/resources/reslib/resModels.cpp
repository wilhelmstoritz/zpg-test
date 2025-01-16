#include "resModels.h"

/*** 1st task ***/
// triangle
const std::vector<float> MODEL_TRIANGLE = { // 3 vertices (3 floats per vertex; 1 triangle)
	 0.0f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

const std::vector<float> MODEL_TRIANGLE_COLORDATA = { // 3 vertices (3+3 floats per vertex; 1 triangle)
	// coords           // color
	 0.0f,  0.5f, 0.0f, 1.f, 0.f, 0.f, // red
	 0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f, // green
	-0.5f, -0.5f, 0.0f, 0.f, 0.f, 1.f  // blue
};

// square
const std::vector<float> MODEL_SQUARE = { // 6 vertices (3 floats per vertex; 2 triangles)
	.6f, .6f, 0.f,
	.9f, .6f, 0.f,
	.6f, .9f, 0.f,
	.6f, .9f, 0.f,
	.9f, .6f, 0.f,
	.9f, .9f, 0.f
};
