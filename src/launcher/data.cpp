#include "data.h"

// --- models ------------------------------------------------------------------
// triangle
std::vector<float> TRIANGLE_POINTS = {
	 0.0f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

std::vector<float> TRIANGLE_POINTS_COLORDATA = {
	// coords           // color
	 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // red
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // green
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // blue
};

// square
std::vector<float> SQUARE_POINTS = {
	0.6f, 0.6f, 0.0f,
	0.9f, 0.6f, 0.0f,
	0.6f, 0.9f, 0.0f,
	0.6f, 0.9f, 0.0f,
	0.9f, 0.6f, 0.0f,
	0.9f, 0.9f, 0.0f
};

// skybox
float randomEnvironment(float baseValue) { return baseValue + (static_cast<float>(rand()) / RAND_MAX) * 0.1f - 0.05f; }

float skyboxSideLength = 200.0f; // x: -100..100; y: -0.1..100; z: -100..100
float skyUnit = skyboxSideLength / 2.f;
std::vector<float> SKYBOX = {
	// --- walls
	// back; 1st triangle
	-skyUnit, skyUnit, -skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // left up
	-skyUnit,   -0.1f, -skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // left bottom
	 skyUnit,   -0.1f, -skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // right bottom
	// back; 2nd triangle
	 skyUnit,   -0.1f, -skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // right bottom
	 skyUnit, skyUnit, -skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // right up
	-skyUnit, skyUnit, -skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // left up

	// front; 1st triangle
	-skyUnit, skyUnit,  skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // left up
	-skyUnit,   -0.1f,  skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // left bottom
	 skyUnit,   -0.1f,  skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // right bottom
	// front; 2nd triangle
	 skyUnit,   -0.1f,  skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // right bottom
	 skyUnit, skyUnit,  skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // right up
	-skyUnit, skyUnit,  skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // left up

	// left; 1st triangle
	-skyUnit, skyUnit,  skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // front up
	-skyUnit,   -0.1f,  skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // front bottom
	-skyUnit,   -0.1f, -skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // back bottom
	// left; 2nd triangle
	-skyUnit,   -0.1f, -skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // back bottom
	-skyUnit, skyUnit, -skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // back up
	-skyUnit, skyUnit,  skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // front up

	// right; 1st triangle
	 skyUnit, skyUnit,  skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // front up
	 skyUnit,   -0.1f,  skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // front bottom
	 skyUnit,   -0.1f, -skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // back bottom
	// right; 2nd triangle
	 skyUnit,   -0.1f, -skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // back bottom
	 skyUnit, skyUnit, -skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // back up
	 skyUnit, skyUnit,  skyUnit, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // front up

	// sky
	// 1st triangle
	-skyUnit, skyUnit, -skyUnit, randomEnvironment(0.53f), randomEnvironment(0.81f), randomEnvironment(0.92f), // left back
	-skyUnit, skyUnit,  skyUnit, randomEnvironment(0.53f), randomEnvironment(0.81f), randomEnvironment(0.92f), // left front
	 skyUnit, skyUnit,  skyUnit, randomEnvironment(0.53f), randomEnvironment(0.81f), randomEnvironment(0.92f), // right front

	// 2nd triangle
	 skyUnit, skyUnit,  skyUnit, randomEnvironment(0.53f), randomEnvironment(0.81f), randomEnvironment(0.92f), // right front
	 skyUnit, skyUnit, -skyUnit, randomEnvironment(0.53f), randomEnvironment(0.81f), randomEnvironment(0.92f), // right back
	-skyUnit, skyUnit, -skyUnit, randomEnvironment(0.53f), randomEnvironment(0.81f), randomEnvironment(0.92f), // left back

	// ground
	// 1st triangle
    -skyUnit,   -0.1f, -skyUnit, randomEnvironment(0.36f), randomEnvironment(0.25f), randomEnvironment(0.20f), // left back
    -skyUnit,   -0.1f,  skyUnit, randomEnvironment(0.36f), randomEnvironment(0.25f), randomEnvironment(0.20f), // left front
	 skyUnit,   -0.1f,  skyUnit, randomEnvironment(0.36f), randomEnvironment(0.25f), randomEnvironment(0.20f), // right front

	// 2nd triangle
	 skyUnit,   -0.1f,  skyUnit, randomEnvironment(0.36f), randomEnvironment(0.25f), randomEnvironment(0.20f), // right front
	 skyUnit,   -0.1f, -skyUnit, randomEnvironment(0.36f), randomEnvironment(0.25f), randomEnvironment(0.20f), // right back
    -skyUnit,   -0.1f, -skyUnit, randomEnvironment(0.36f), randomEnvironment(0.25f), randomEnvironment(0.20f)  // left back
};

// --- shaders -----------------------------------------------------------------
// vertex shaders
// --- default
const char* DEFAULT_VERTEX_SHADER =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"void main () {"
"	gl_Position = vec4 (vp, 1.0);"
"}";

const char* DEFAULT_VERTEX_SHADER_COLORFROMPOSITION =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"out vec3 frag_pos;"
"void main () {"
"	frag_pos = vp;"
"	gl_Position = vec4 (vp, 1.0);"
"}";

const char* DEFAULT_VERTEX_SHADER_COLORDATA =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 color;"
"out vec3 frag_color;"
"void main () {"
"	frag_color = color;"
"	gl_Position = vec4 (vp, 1.0);"
"}";

// --- transforming
const char* TRANSFORMING_VERTEX_SHADER_NORMALDATA =
"#version 330\n"
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 color;"
"out vec3 vertexColor;"
"void main () {"
"	vertexColor = color;"
//"	gl_Position = modelMatrix * vec4 (vp, 1.0);"
"	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);"
"}";

// fragment shaders
// --- default
const char* DEFAULT_FRAGMENT_SHADER =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";

const char* DEFAULT_FRAGMENT_SHADER_COLORFROMPOSITION =
"#version 330\n"
"in vec3 frag_pos;"
"out vec4 frag_colour;"
"void main () {"
//"	frag_colour = vec4 (frag_pos * 0.5 + 0.5, 1.0);"
"	frag_colour = vec4 (frag_pos + 0.5, 1.0);"
"}";

const char* DEFAULT_FRAGMENT_SHADER_COLORDATA =
"#version 330\n"
"in vec3 frag_color;"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (frag_color, 1.0);"
"}";

const char* YELLOW_FRAGMENT_SHADER =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (1.0, 1.0, 0.0, 1.0);" // yellow
"}";

// --- transforming
const char* TRANSFORMING_FRAGMENT_SHADER_NORMALDATA =
"#version 330\n"
"in vec3 vertexColor;"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (vertexColor, 0.0);"
"}";
