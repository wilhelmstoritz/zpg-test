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
const char* TRANSFORMING_VERTEX_SHADER_COLORDATA =
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
const char* TRANSFORMING_FRAGMENT_SHADER_COLORDATA =
"#version 330\n"
"in vec3 vertexColor;"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (vertexColor, 0.0);"
"}";
