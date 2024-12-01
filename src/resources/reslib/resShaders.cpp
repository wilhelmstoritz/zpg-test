#include "resShaders.h"

/*** 1st task ***/
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

/*** 2nd task ***/
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

/*** 3rd task ***/
const char* VSHADER_NORMAL =
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
"out vec4 ex_worldPosition;"
"out vec3 ex_worldNormal;"

"void main(void) {"
	// vertex position in the clip space
"	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0f);"

	// position and normal in world space
"	ex_worldPosition = modelMatrix * vec4(in_Position, 1.0f);"
"	ex_worldNormal = normalMatrix * in_Normal;"
"}";

const char* FSHADER_LAMBERTIAN =
"#version 330 core\n"

// light adjustment uniforms
"uniform vec3 lightPosition;"
"uniform vec3 diffuseColor;" // diffuse color used as light color
"uniform float kDiffuse;" // diffuse coeficient used as light intensity

// input variables from the vertex shader
"in vec4 ex_worldPosition;"
"in vec3 ex_worldNormal;"

// output variable for color
"out vec4 out_Color;"

"void main(void) {"
	// light color/intensity uses the diffuse color/coeficient; backward code compatibility
"	vec3 lightColor = diffuseColor;"
"	float lightIntensity = kDiffuse;"

	// light position in world space
//"	vec3 lightPosition = vec3(10.0f, 10.0f, 10.0f);"
//"	vec3 lightPosition = vec3(0.0f, 0.0f, 0.0f);"

	// direction vector from the light to the surface
	"	vec3 lightVector = normalize(lightPosition - ex_worldPosition.xyz);"
	// illumination using Lambert's law (dot product)
	"	float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0f);"
	// diffuse component (light color * intensity)
//"	vec4 diffuse = dot_product * vec4(0.385f, 0.647f, 0.812f, 1.0f);"
"	vec4 diffuse = dot_product * vec4(lightColor, 1.0f) * lightIntensity;"
	// ambient light component
"	vec4 ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);"

	// a combination of ambient and diffuse lighting
"	out_Color = ambient + diffuse;"
"}";

const char* FSHADER_PHONG =
"#version 330 core\n"

// light adjustment uniforms
"uniform vec3 eyePosition;"
"uniform vec3 lightPosition;"
"uniform vec3 diffuseColor;" // diffuse color used as light color
"uniform float kDiffuse;" // diffuse coeficient used as light intensity

// input variables from the vertex shader
"in vec4 ex_worldPosition;"
"in vec3 ex_worldNormal;"

// output variable for color
"out vec4 out_Color;"

"void main(void) {"
	// light color/intensity uses the diffuse color/coeficient; backward code compatibility
"	vec3 lightColor = diffuseColor;"
"	float lightIntensity = kDiffuse;"

	// ambient light component
"	vec4 ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);"
	// direction vector from the light to the surface; normalize the normal vector for future use
"	vec3 lightVector = normalize(lightPosition - ex_worldPosition.xyz);"
"	vec3 normal = normalize(ex_worldNormal);"
	// illumination using Lambert's law (dot product)
"	float dot_product = max(dot(normal, lightVector), 0.0f);"
	// diffuse component (light color * intensity)
"	vec4 diffuse = dot_product * vec4(lightColor, 1.0f) * lightIntensity;"
	// specular component (Phong's model)
"	vec4 specular = vec4(0.0f);"
"	if (dot_product > 0.0f) {" // only calculate specular if the light hits the front side
"		vec3 viewDir = normalize(eyePosition - ex_worldPosition.xyz);"
"		vec3 reflectDir = reflect(-lightVector, normal);"
"		float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);" // shininess = 32
"		specular = vec4(lightColor * spec * lightIntensity, 1.0f);"
"	}"

	// a combination of ambient, diffuse and specular components
"	out_Color = ambient + diffuse + specular;"
"}";
