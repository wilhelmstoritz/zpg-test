#include "ModelLibrary.h"
#include "AppMath.h"

// --- public ------------------------------------------------------------------
/*** 2nd task ***/
glm::vec3 wallColor   = { .33f, .55f, .33f }; // green
glm::vec3 groundColor = { .36f, .25f, .20f }; // brown
glm::vec3 skyColor    = { .53f, .81f, .92f }; // light blue

const std::vector<float> ModelLibrary::MODEL_SKYBOX_RNDCOLORS = { // 36 vertices (3+3 floats per vertex; 12 triangles, 6 faces)
//  (xyz)    r                      g                      b                    // (rgb) color components
	0, 0, 0, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z), // back wall
	1, 0, 0, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	1, 1, 0, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	0, 0, 0, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	0, 1, 0, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	1, 1, 0, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),

	1, 0, 1, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z), // front wall
	0, 0, 1, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	0, 1, 1, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	1, 0, 1, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	1, 1, 1, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	0, 1, 1, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),

	0, 0, 0, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z), // left wall
	0, 0, 1, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	0, 1, 1, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	0, 0, 0, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	0, 1, 0, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	0, 1, 1, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),

	1, 0, 1, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z), // right wall
	1, 0, 0, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	1, 1, 0, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	1, 0, 1, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	1, 1, 1, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),
	1, 1, 0, randCC(wallColor.x),   randCC(wallColor.y),   randCC(wallColor.z),

	1, 0, 1, randCC(groundColor.x), randCC(groundColor.y), randCC(groundColor.z), // ground
	0, 0, 1, randCC(groundColor.x), randCC(groundColor.y), randCC(groundColor.z),
	0, 0, 0, randCC(groundColor.x), randCC(groundColor.y), randCC(groundColor.z),
	1, 0, 1, randCC(groundColor.x), randCC(groundColor.y), randCC(groundColor.z),
	1, 0, 0, randCC(groundColor.x), randCC(groundColor.y), randCC(groundColor.z),
	0, 0, 0, randCC(groundColor.x), randCC(groundColor.y), randCC(groundColor.z),
	
	0, 1, 1, randCC(skyColor.x),    randCC(skyColor.y),    randCC(skyColor.z), // sky
	1, 1, 1, randCC(skyColor.x),    randCC(skyColor.y),    randCC(skyColor.z),
	1, 1, 0, randCC(skyColor.x),    randCC(skyColor.y),    randCC(skyColor.z),
	0, 1, 1, randCC(skyColor.x),    randCC(skyColor.y),    randCC(skyColor.z),
	0, 1, 0, randCC(skyColor.x),    randCC(skyColor.y),    randCC(skyColor.z),
	1, 1, 0, randCC(skyColor.x),    randCC(skyColor.y),    randCC(skyColor.z)
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
//  a(xyz)     normal a a(uv)   b(xyz)     normal b b(uv)   c(xyz)   normal c c(uv) // triangle /_\abc
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
//  a(xyz)   normal a  a(uv)   b(xyz)   normal b  b(uv)   c(xyz)   normal c  c(uv) // triangle /_\abc
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
const float ModelLibrary::randCC(float t_baseValue) {
	return t_baseValue + AppMath::getInstance()->randomNumber(-.06f, .06f); // random color component; slightly different from the base value by +/-0.06
}
