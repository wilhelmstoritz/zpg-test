#include "resTMP.h"

// --- shaders -----------------------------------------------------------------
const char* VSHADER_TMP =
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

const char* FSHADER_TMP =
"#version 330 core\n"

// light adjustment uniforms
"uniform vec3 viewPosition;"
"uniform vec3 lightPosition;"
"uniform vec3 lightColor;"
"uniform float lightIntensity;"

// input variables from the vertex shader
"in vec4 ex_worldPosition;"
"in vec3 ex_worldNormal;"

// output variable for color
"out vec4 out_Color;"

"void main(void) {"
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
"		vec3 viewDir = normalize(viewPosition - ex_worldPosition.xyz);"
"		vec3 reflectDir = reflect(-lightVector, normal);"
"		float spec = pow(max(dot(viewDir, reflectDir), 0.f), 32.f);" // shininess = 32
"		specular = vec4(lightColor * spec * lightIntensity, 1.f);"
"	}"

	// a combination of ambient, diffuse and specular components
"	out_Color = ambient + diffuse + specular;"
"}";
