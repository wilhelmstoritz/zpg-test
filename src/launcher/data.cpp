#include "data.h"

// --- models ------------------------------------------------------------------
/* 1st task */
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

/* 2nd task */
// skybox
float randomEnvironment(float baseValue) { return baseValue + (static_cast<float>(rand()) / RAND_MAX) * 0.1f - 0.05f; }

std::vector<float> SKYBOX = {
	// --- walls
	// back; 1st triangle
	-1.f, 1.f, -1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // left up
	-1.f, 0.f, -1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // left bottom
	 1.f, 0.f, -1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // right bottom
	// back; 2nd triangle
	 1.f, 0.f, -1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // right bottom
	 1.f, 1.f, -1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // right up
	-1.f, 1.f, -1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // left up

	// front; 1st triangle
	-1.f, 1.f,  1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // left up
	-1.f, 0.f,  1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // left bottom
	 1.f, 0.f,  1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // right bottom
	// front; 2nd triangle
	 1.f, 0.f,  1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // right bottom
	 1.f, 1.f,  1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // right up
	-1.f, 1.f,  1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // left up

	// left; 1st triangle
	-1.f, 1.f,  1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // front up
	-1.f, 0.f,  1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // front bottom
	-1.f, 0.f, -1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // back bottom
	// left; 2nd triangle
	-1.f, 0.f, -1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // back bottom
	-1.f, 1.f, -1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // back up
	-1.f, 1.f,  1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // front up

	// right; 1st triangle
	 1.f, 1.f,  1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // front up
	 1.f, 0.f,  1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // front bottom
	 1.f, 0.f, -1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // back bottom
	// right; 2nd triangle
	 1.f, 0.f, -1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // back bottom
	 1.f, 1.f, -1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // back up
	 1.f, 1.f,  1.f, randomEnvironment(0.33f), randomEnvironment(0.55f), randomEnvironment(0.33f), // front up

	// sky
	// 1st triangle
	-1.f, 1.f, -1.f, randomEnvironment(0.53f), randomEnvironment(0.81f), randomEnvironment(0.92f), // left back
	-1.f, 1.f,  1.f, randomEnvironment(0.53f), randomEnvironment(0.81f), randomEnvironment(0.92f), // left front
	 1.f, 1.f,  1.f, randomEnvironment(0.53f), randomEnvironment(0.81f), randomEnvironment(0.92f), // right front

	// 2nd triangle
	 1.f, 1.f,  1.f, randomEnvironment(0.53f), randomEnvironment(0.81f), randomEnvironment(0.92f), // right front
	 1.f, 1.f, -1.f, randomEnvironment(0.53f), randomEnvironment(0.81f), randomEnvironment(0.92f), // right back
	-1.f, 1.f, -1.f, randomEnvironment(0.53f), randomEnvironment(0.81f), randomEnvironment(0.92f), // left back

	// ground
	// 1st triangle
    -1.f, 0.f, -1.f, randomEnvironment(0.36f), randomEnvironment(0.25f), randomEnvironment(0.20f), // left back
    -1.f, 0.f,  1.f, randomEnvironment(0.36f), randomEnvironment(0.25f), randomEnvironment(0.20f), // left front
	 1.f, 0.f,  1.f, randomEnvironment(0.36f), randomEnvironment(0.25f), randomEnvironment(0.20f), // right front

	// 2nd triangle
	 1.f, 0.f,  1.f, randomEnvironment(0.36f), randomEnvironment(0.25f), randomEnvironment(0.20f), // right front
	 1.f, 0.f, -1.f, randomEnvironment(0.36f), randomEnvironment(0.25f), randomEnvironment(0.20f), // right back
    -1.f, 0.f, -1.f, randomEnvironment(0.36f), randomEnvironment(0.25f), randomEnvironment(0.20f)  // left back
};

// --- shaders -----------------------------------------------------------------
/* 1st task */
// vertex shaders
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

// fragment shaders
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

/* 2nd task */
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

const char* TRANSFORMING_FRAGMENT_SHADER_NORMALDATA =
"#version 330\n"
"in vec3 vertexColor;"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (vertexColor, 0.0);"
"}";
