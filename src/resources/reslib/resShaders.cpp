#include "resShaders.h"

/*** 1st task ***/
// vertex shaders
const char* VSHADER_BASIC =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"void main () {"
"	gl_Position = vec4 (vp, 1.f);"
"}";

const char* VSHADER_COLORFROMPOSITION =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"out vec3 frag_pos;"
"void main () {"
"	frag_pos = vp;"
"	gl_Position = vec4 (vp, 1.f);"
"}";

const char* VSHADER_COLORDATA =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 color;"
"out vec3 frag_color;"
"void main () {"
"	frag_color = color;"
"	gl_Position = vec4 (vp, 1.f);"
"}";

// fragment shaders
const char* FSHADER_BASIC =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (.5f, 0.f, .5f, 1.f);"
"}";

const char* FSHADER_COLORFROMPOSITION =
"#version 330\n"
"in vec3 frag_pos;"
"out vec4 frag_colour;"
"void main () {"
//"	frag_colour = vec4 (frag_pos * .5f + .5f, 1.f);"
"	frag_colour = vec4 (frag_pos + .5f, 1.f);"
"}";

const char* FSHADER_COLORDATA =
"#version 330\n"
"in vec3 frag_color;"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (frag_color, 1.f);"
"}";

const char* FSHADER_YELLOW =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (1.f, 1.f, 0.f, 1.f);" // yellow
"}";

/*** 2nd task ***/
const char* VSHADER_VIEW_PROJECTION_MATRIX =
"#version 330\n"
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 color;"
"out vec3 vertexColor;"
"void main () {"
"	vertexColor = color;"
//"	gl_Position = modelMatrix * vec4 (vp, 1.f);"
"	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.f);"
"}";

const char* FSHADER_VIEW_PROJECTION_MATRIX =
"#version 330\n"
"in vec3 vertexColor;"
"out vec4 frag_colour;"
"void main () {"
"	frag_colour = vec4 (vertexColor, 0.f);"
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
"	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.f);"

	// position and normal in world space
"	ex_worldPosition = modelMatrix * vec4(in_Position, 1.f);"
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
//"	vec3 lightPosition = vec3(10.f, 10.f, 10.f);"
//"	vec3 lightPosition = vec3(0.f, 0.f, 0.f);"

	// direction vector from the light to the surface
	"	vec3 lightVector = normalize(lightPosition - ex_worldPosition.xyz);"
	// illumination using Lambert's law (dot product)
	"	float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.f);"
	// diffuse component (light color * intensity)
//"	vec4 diffuse = dot_product * vec4(.385f, .647f, .812f, 1.f);"
"	vec4 diffuse = dot_product * vec4(lightColor, 1.f) * lightIntensity;"
	// ambient light component
"	vec4 ambient = vec4(.1f, .1f, .1f, 1.f);"

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
"	vec4 ambient = vec4(.1f, .1f, .1f, 1.f);"
	// direction vector from the light to the surface; normalize the normal vector for future use
"	vec3 lightVector = normalize(lightPosition - ex_worldPosition.xyz);"
"	vec3 normal = normalize(ex_worldNormal);"
	// illumination using Lambert's law (dot product)
"	float dot_product = max(dot(normal, lightVector), 0.f);"
	// diffuse component (light color * intensity)
"	vec4 diffuse = dot_product * vec4(lightColor, 1.f) * lightIntensity;"
	// specular component (Phong's model)
"	vec4 specular = vec4(0.f);"
"	if (dot_product > 0.f) {" // only calculate specular if the light hits the front side
"		vec3 viewDir = normalize(eyePosition - ex_worldPosition.xyz);"
"		vec3 reflectDir = reflect(-lightVector, normal);"
"		float spec = pow(max(dot(viewDir, reflectDir), 0.f), 32.f);" // shininess = 32
"		specular = vec4(lightColor * spec * lightIntensity, 1.f);"
"	}"

	// a combination of ambient, diffuse and specular components
"	out_Color = ambient + diffuse + specular;"
"}";
