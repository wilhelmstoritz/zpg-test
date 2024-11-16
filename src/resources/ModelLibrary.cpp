#include "ModelLibrary.h"

// --- public ------------------------------------------------------------------
/*** 2nd task ***/
std::vector<float> ModelLibrary::MODEL_SKYBOX = {
	// --- walls
	// back; 1st triangle
	-1.f, 1.f, -1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // left up
	-1.f, 0.f, -1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // left bottom
	 1.f, 0.f, -1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // right bottom
	// back; 2nd triangle
	 1.f, 0.f, -1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // right bottom
	 1.f, 1.f, -1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // right up
	-1.f, 1.f, -1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // left up

	// front; 1st triangle
	-1.f, 1.f,  1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // left up
	-1.f, 0.f,  1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // left bottom
	 1.f, 0.f,  1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // right bottom
	// front; 2nd triangle
	 1.f, 0.f,  1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // right bottom
	 1.f, 1.f,  1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // right up
	-1.f, 1.f,  1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // left up

	// left; 1st triangle
	-1.f, 1.f,  1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // front up
	-1.f, 0.f,  1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // front bottom
	-1.f, 0.f, -1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // back bottom
	// left; 2nd triangle
	-1.f, 0.f, -1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // back bottom
	-1.f, 1.f, -1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // back up
	-1.f, 1.f,  1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // front up

	// right; 1st triangle
	 1.f, 1.f,  1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // front up
	 1.f, 0.f,  1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // front bottom
	 1.f, 0.f, -1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // back bottom
	// right; 2nd triangle
	 1.f, 0.f, -1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // back bottom
	 1.f, 1.f, -1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // back up
	 1.f, 1.f,  1.f, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // front up

	// sky
	// 1st triangle
	-1.f, 1.f, -1.f, rndColorComponent(0.53f), rndColorComponent(0.81f), rndColorComponent(0.92f), // left back
	-1.f, 1.f,  1.f, rndColorComponent(0.53f), rndColorComponent(0.81f), rndColorComponent(0.92f), // left front
	 1.f, 1.f,  1.f, rndColorComponent(0.53f), rndColorComponent(0.81f), rndColorComponent(0.92f), // right front

	// 2nd triangle
	 1.f, 1.f,  1.f, rndColorComponent(0.53f), rndColorComponent(0.81f), rndColorComponent(0.92f), // right front
	 1.f, 1.f, -1.f, rndColorComponent(0.53f), rndColorComponent(0.81f), rndColorComponent(0.92f), // right back
	-1.f, 1.f, -1.f, rndColorComponent(0.53f), rndColorComponent(0.81f), rndColorComponent(0.92f), // left back

	// ground
	// 1st triangle
	-1.f, 0.f, -1.f, rndColorComponent(0.36f), rndColorComponent(0.25f), rndColorComponent(0.20f), // left back
	-1.f, 0.f,  1.f, rndColorComponent(0.36f), rndColorComponent(0.25f), rndColorComponent(0.20f), // left front
	 1.f, 0.f,  1.f, rndColorComponent(0.36f), rndColorComponent(0.25f), rndColorComponent(0.20f), // right front

	// 2nd triangle
	 1.f, 0.f,  1.f, rndColorComponent(0.36f), rndColorComponent(0.25f), rndColorComponent(0.20f), // right front
	 1.f, 0.f, -1.f, rndColorComponent(0.36f), rndColorComponent(0.25f), rndColorComponent(0.20f), // right back
	-1.f, 0.f, -1.f, rndColorComponent(0.36f), rndColorComponent(0.25f), rndColorComponent(0.20f)  // left back
};

// --- private -----------------------------------------------------------------
float ModelLibrary::rndColorComponent(float t_baseColor) {
	return t_baseColor + (static_cast<float>(rand()) / RAND_MAX) * 0.1f - 0.05f;
}
