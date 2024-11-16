/* 3rd task; fragment shader, lambertian */
#version 330 core

// light adjustment uniforms
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;

// input variables from the vertex shader
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

// output variable for color
out vec4 out_Color;

void main(void) {
// light position in world space
	//vec3 lightPosition = vec3(10.0f, 10.0f, 10.0f);
	//vec3 lightPosition = vec3(0.0f, 0.0f, 0.0f);

	// direction vector from the light to the surface
	vec3 lightVector = normalize(lightPosition - ex_worldPosition.xyz);
	// illumination using Lambert's law (dot product)
	float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0f);
	// diffuse component (light color * intensity)
	//vec4 diffuse = dot_product * vec4(0.385f, 0.647f, 0.812f, 1.0f);
	vec4 diffuse = dot_product * vec4(lightColor, 1.0f) * lightIntensity;
	// ambient light component
	vec4 ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);

	// a combination of ambient and diffuse lighting
	out_Color = ambient + diffuse;
};
