#include "data.h"

// --- models ------------------------------------------------------------------
/* 1st task */
// triangle
std::vector<float> MODEL_TRIANGLE = {
	 0.0f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

std::vector<float> MODEL_TRIANGLE_COLORDATA = {
	// coords           // color
	 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // red
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // green
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // blue
};

// square
std::vector<float> MODEL_SQUARE = {
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

std::vector<float> MODEL_SKYBOX = {
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
const char* BASIC_VSHADER =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"void main () {"
"	gl_Position = vec4 (vp, 1.0);"
"}";

const char* BASIC_VSHADER_COLORFROMPOSITION =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"out vec3 frag_pos;"
"void main () {"
"	frag_pos = vp;"
"	gl_Position = vec4 (vp, 1.0);"
"}";

const char* BASIC_VSHADER_COLORDATA =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 color;"
"out vec3 frag_color;"
"void main () {"
"	frag_color = color;"
"	gl_Position = vec4 (vp, 1.0);"
"}";

// fragment shaders
const char* BASIC_FSHADER =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";

const char* BASIC_FSHADER_COLORFROMPOSITION =
"#version 330\n"
"in vec3 frag_pos;"
"out vec4 frag_colour;"
"void main () {"
//"	frag_colour = vec4 (frag_pos * 0.5 + 0.5, 1.0);"
"	frag_colour = vec4 (frag_pos + 0.5, 1.0);"
"}";

const char* BASIC_FSHADER_COLORDATA =
"#version 330\n"
"in vec3 frag_color;"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (frag_color, 1.0);"
"}";

const char* BASIC_FSHADER_YELLOW =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (1.0, 1.0, 0.0, 1.0);" // yellow
"}";

/* 2nd task */
const char* VSHADER_VIEW_PROJECTION =
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

const char* FSHADER_VIEW_PROJECTION =
"#version 330\n"
"in vec3 vertexColor;"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (vertexColor, 0.0);"
"}";

/* 3rd task */
const char* VSHADER_VIEW_PROJECTION_NORMAL =
"#version 330 core\n"

// uniforms for transformation matrices
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"uniform mat3 normalMatrix;" // (M^-1)^T; for transforming normals

// input variables; must match VBO attributes
"layout(location = 0) in vec3 in_Position;"
"layout(location = 1) in vec3 in_Normal;"

// output variables; will be passed to the fragment shader
//"out vec4 ex_worldPosition;"
"out vec3 ex_worldPosition;"
"out vec3 ex_worldNormal;"

"void main(void) {"
	// vertex position in the clip space
//"	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(in_Position, 1.0f);"
"	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0f);"

	// position and normal in world space
//"	ex_worldPosition = (modelMatrix * vec4(in_Position, 1.0f)).xyz;" // ex_worldPosition is of type vec3; it is not necessary to explicitly convert vec4 to vec3 with .xyz, only the first three components (x, y, z) are used to assign between vec4 and vec3
"	ex_worldPosition = modelMatrix * vec4(in_Position, 1.0f);"
"	ex_worldNormal = normalMatrix * in_Normal;"
"}";

const char* FSHADER_VIEW_PROJECTION_NORMAL =
"#version 330 core\n"

// input variables from the vertex shader
//"in vec4 ex_worldPosition;"
"in vec3 ex_worldPosition;"
"in vec3 ex_worldNormal;"

// output variable for color
"out vec4 out_Color;"

"void main(void) {"
	// light position in world space
"	vec3 lightPosition = vec3(10.0f, 10.0f, 10.0f);"

	// direction vector from the light to the surface
//"	vec3 lightVector = normalize(lightPosition - ex_worldPosition.xyz);"
"	vec3 lightVector = normalize(lightPosition - ex_worldPosition);"
	// illumination using Lambert's law (dot product)
"	float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0f);"
	// diffuse component (light color * intensity)
"	vec4 diffuse = dot_product * vec4(0.385f, 0.647f, 0.812f, 1.0f);"
	// ambient light component
"	vec4 ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);"
	// a combination of ambient and diffuse lighting
"	out_Color = ambient + diffuse;"
"}";
