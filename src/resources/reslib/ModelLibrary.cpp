#include "ModelLibrary.h"

// --- public ------------------------------------------------------------------
/*** 2nd task ***/
const std::vector<float> ModelLibrary::MODEL_SKYBOX_RNDCOLORS = { // 36 vertices (3+3 floats per vertex; 12 triangles, 6 faces)
//  (xyz)    color r                   color g                   color b
	0, 0, 0, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // back wall
	1, 0, 0, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	1, 1, 0, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	0, 0, 0, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	0, 1, 0, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	1, 1, 0, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),

	1, 0, 1, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // front wall
	0, 0, 1, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	0, 1, 1, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	1, 0, 1, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	1, 1, 1, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	0, 1, 1, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),

	0, 0, 0, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // left wall
	0, 0, 1, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	0, 1, 1, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	0, 0, 0, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	0, 1, 0, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	0, 1, 1, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),

	1, 0, 1, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f), // right wall
	1, 0, 0, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	1, 1, 0, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	1, 0, 1, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	1, 1, 1, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),
	1, 1, 0, rndColorComponent(0.33f), rndColorComponent(0.55f), rndColorComponent(0.33f),

	1, 0, 1, rndColorComponent(0.36f), rndColorComponent(0.25f), rndColorComponent(0.20f), // ground
	0, 0, 1, rndColorComponent(0.36f), rndColorComponent(0.25f), rndColorComponent(0.20f),
	0, 0, 0, rndColorComponent(0.36f), rndColorComponent(0.25f), rndColorComponent(0.20f),
	1, 0, 1, rndColorComponent(0.36f), rndColorComponent(0.25f), rndColorComponent(0.20f),
	1, 0, 0, rndColorComponent(0.36f), rndColorComponent(0.25f), rndColorComponent(0.20f),
	0, 0, 0, rndColorComponent(0.36f), rndColorComponent(0.25f), rndColorComponent(0.20f),
	
	0, 1, 1, rndColorComponent(0.53f), rndColorComponent(0.81f), rndColorComponent(0.92f), // sky
	1, 1, 1, rndColorComponent(0.53f), rndColorComponent(0.81f), rndColorComponent(0.92f),
	1, 1, 0, rndColorComponent(0.53f), rndColorComponent(0.81f), rndColorComponent(0.92f),
	0, 1, 1, rndColorComponent(0.53f), rndColorComponent(0.81f), rndColorComponent(0.92f),
	0, 1, 0, rndColorComponent(0.53f), rndColorComponent(0.81f), rndColorComponent(0.92f),
	1, 1, 0, rndColorComponent(0.53f), rndColorComponent(0.81f), rndColorComponent(0.92f)
};

const std::vector<float> ModelLibrary::MODEL_SKYBOX_NORMALS = { // 36 vertices (3+3 floats per vertex; 12 triangles, 6 faces)
//  a(xyz)   normal a    b(xyz)   normal b    c(xyz)   normal c  // triangle /_\abc
	0, 0, 1,  1, 0, 0,   0, 0, 0,  1, 0, 0,   0, 1, 0,  1, 0, 0, // left wall
	0, 0, 1,  1, 0, 0,   0, 1, 1,  1, 0, 0,   0, 1, 0,  1, 0, 0,
	1, 0, 1, -1, 0, 0,   1, 0, 0, -1, 0, 0,   1, 1, 0, -1, 0, 0, // right wall
	1, 0, 1, -1, 0, 0,   1, 1, 1, -1, 0, 0,   1, 1, 0, -1, 0, 0,
	0, 0, 1, 0,  1, 0,   1, 0, 1, 0,  1, 0,   1, 0, 0, 0,  1, 0, // ground
	0, 0, 1, 0,  1, 0,   0, 0, 0, 0,  1, 0,   1, 0, 0, 0,  1, 0,
	0, 1, 1, 0, -1, 0,   1, 1, 1, 0, -1, 0,   1, 1, 0, 0, -1, 0, // sky
	0, 1, 1, 0, -1, 0,   0, 1, 0, 0, -1, 0,   1, 1, 0, 0, -1, 0,
	0, 0, 0, 0, 0,  1,   1, 0, 0, 0, 0,  1,   1, 1, 0, 0, 0,  1, // back wall
	0, 0, 0, 0, 0,  1,   0, 1, 0, 0, 0,  1,   1, 1, 0, 0, 0,  1,
	0, 0, 1, 0, 0, -1,   1, 0, 1, 0, 0, -1,   1, 1, 1, 0, 0, -1, // front wall
	0, 0, 1, 0, 0, -1,   0, 1, 1, 0, 0, -1,   1, 1, 1, 0, 0, -1
};

/*** 5th task ***/
const std::vector<float> ModelLibrary::MODEL_SKYCUBE = { // 36 vertices (3 floats per vertex; 12 triangles, 6 faces)
//  a(xyz)        b(xyz)        c(xyz)      // triangle /_\abc
	-1, -1, -1,   -1, -1,  1,   -1,  1,  1,
	 1,  1, -1,   -1, -1, -1,   -1,  1, -1,
	 1, -1,  1,   -1, -1, -1,    1, -1, -1,
	 1,  1, -1,    1, -1, -1,   -1, -1, -1,
	-1, -1, -1,   -1,  1,  1,   -1,  1, -1,
	 1, -1,  1,   -1, -1,  1,   -1, -1, -1,
	-1,  1,  1,   -1, -1,  1,    1, -1,  1,
	 1,  1,  1,    1, -1, -1,    1,  1, -1,
	 1, -1, -1,    1,  1,  1,    1, -1,  1,
	 1,  1,  1,    1,  1, -1,   -1,  1, -1,
	 1,  1,  1,   -1,  1, -1,   -1,  1,  1,
	 1,  1,  1,   -1,  1,  1,    1, -1,  1
};

/*** other ***/
const std::vector<float> ModelLibrary::MODEL_SURFACE = { // 6 vertices (3+3 floats per vertex)
//  a(xyz)     normal a   b(xyz)     normal b   c(xyz)   normal c // triangle /_\abc
	-1, -1, 0, 0, 0, 1,    1, -1, 0, 0, 0, 1,   1, 1, 0, 0, 0, 1, // 1st triangle
	-1, -1, 0, 0, 0, 1,   -1,  1, 0, 0, 0, 1,   1, 1, 0, 0, 0, 1  // 2nd triangle
};

const std::vector<float> ModelLibrary::MODEL_SURFACE_TEXTURE = { // 6 vertices (3+3+2 floats per vertex)
//  a(xyz)     normal a (uv)    b(xyz)     normal b (uv)    c(xyz)   normal c (uv)  // triangle /_\abc
	-1, -1, 0, 0, 0, 1, 0, 1,    1, -1, 0, 0, 0, 1, 1, 1,   1, 1, 0, 0, 0, 1, 1, 0, // 1st triangle
	-1, -1, 0, 0, 0, 1, 0, 1,   -1,  1, 0, 0, 0, 1, 0, 0,   1, 1, 0, 0, 0, 1, 1, 0  // 2nd triangle
};

const std::vector<float> ModelLibrary::MODEL_CUBE = { // 36 vertices (3+3 floats per vertex; 12 triangles, 6 faces)
//  a(xyz)   normal a    b(xyz)   normal b    c(xyz)   normal c  // triangle /_\abc
	0, 0, 1, -1, 0, 0,   0, 0, 0, -1, 0, 0,   0, 1, 0, -1, 0, 0, // left side
	0, 0, 1, -1, 0, 0,   0, 1, 1, -1, 0, 0,   0, 1, 0, -1, 0, 0,
	1, 0, 1,  1, 0, 0,   1, 0, 0,  1, 0, 0,   1, 1, 0,  1, 0, 0, // right side
	1, 0, 1,  1, 0, 0,   1, 1, 1,  1, 0, 0,   1, 1, 0,  1, 0, 0,
	0, 0, 1, 0, -1, 0,   1, 0, 1, 0, -1, 0,   1, 0, 0, 0, -1, 0, // bottom side
	0, 0, 1, 0, -1, 0,   0, 0, 0, 0, -1, 0,   1, 0, 0, 0, -1, 0,
	0, 1, 1, 0,  1, 0,   1, 1, 1, 0,  1, 0,   1, 1, 0, 0,  1, 0, // top side
	0, 1, 1, 0,  1, 0,   0, 1, 0, 0,  1, 0,   1, 1, 0, 0,  1, 0,
	0, 0, 0, 0, 0, -1,   1, 0, 0, 0, 0, -1,   1, 1, 0, 0, 0, -1, // back side
	0, 0, 0, 0, 0, -1,   0, 1, 0, 0, 0, -1,   1, 1, 0, 0, 0, -1,
	0, 0, 1, 0, 0,  1,   1, 0, 1, 0, 0,  1,   1, 1, 1, 0, 0,  1, // front side
	0, 0, 1, 0, 0,  1,   0, 1, 1, 0, 0,  1,   1, 1, 1, 0, 0,  1
};

const std::vector<float> ModelLibrary::MODEL_CUBE_TEXTURE = { // 36 vertices (3+3+2 floats per vertex; 12 triangles, 6 faces)
//  X{xyz}   normal x (u, v)   Y{xyz}   normal y (u, v)   Z{xyz}   normal z (u, v)
	0, 0, 1, -1, 0, 0, 1, 1,   0, 0, 0, -1, 0, 0, 0, 1,   0, 1, 0, -1, 0, 0, 0, 0, // left side
	0, 0, 1, -1, 0, 0, 1, 1,   0, 1, 1, -1, 0, 0, 1, 0,   0, 1, 0, -1, 0, 0, 0, 0,
	1, 0, 1,  1, 0, 0, 0, 1,   1, 0, 0,  1, 0, 0, 1, 1,   1, 1, 0,  1, 0, 0, 1, 0, // right side
	1, 0, 1,  1, 0, 0, 0, 1,   1, 1, 1,  1, 0, 0, 0, 0,   1, 1, 0,  1, 0, 0, 1, 0,
	0, 0, 1, 0, -1, 0, 1, 1,   1, 0, 1, 0, -1, 0, 0, 1,   1, 0, 0, 0, -1, 0, 0, 0, // bottom side
	0, 0, 1, 0, -1, 0, 1, 1,   0, 0, 0, 0, -1, 0, 1, 0,   1, 0, 0, 0, -1, 0, 0, 0,
	0, 1, 1, 0,  1, 0, 0, 1,   1, 1, 1, 0,  1, 0, 1, 1,   1, 1, 0, 0,  1, 0, 1, 0, // top side
	0, 1, 1, 0,  1, 0, 0, 1,   0, 1, 0, 0,  1, 0, 0, 0,   1, 1, 0, 0,  1, 0, 1, 0,
	0, 0, 0, 0, 0, -1, 1, 1,   1, 0, 0, 0, 0, -1, 0, 1,   1, 1, 0, 0, 0, -1, 0, 0, // back side
	0, 0, 0, 0, 0, -1, 1, 1,   0, 1, 0, 0, 0, -1, 1, 0,   1, 1, 0, 0, 0, -1, 0, 0,
	0, 0, 1, 0, 0,  1, 0, 1,   1, 0, 1, 0, 0,  1, 1, 1,   1, 1, 1, 0, 0,  1, 1, 0, // front side
	0, 0, 1, 0, 0,  1, 0, 1,   0, 1, 1, 0, 0,  1, 0, 0,   1, 1, 1, 0, 0,  1, 1, 0
};

// --- private -----------------------------------------------------------------
const float ModelLibrary::rndColorComponent(float t_baseColor) {
	return t_baseColor + (static_cast<float>(rand()) / RAND_MAX) * 0.1f - 0.05f;
}
