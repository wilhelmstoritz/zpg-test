/* 3rd task; fragment shader, phong */
#version 330 core

// light adjustment uniforms
uniform vec3 viewPosition;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;

// input variables from the vertex shader
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

// output variable for color
out vec4 out_Color;

void main(void) {
// ambient light component
	vec4 ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
	// direction vector from the light to the surface; normalize the normal vector for future use
	vec3 lightVector = normalize(lightPosition - ex_worldPosition.xyz);
	vec3 normal = normalize(ex_worldNormal);
	// illumination using Lambert's law (dot product)
	float dot_product = max(dot(normal, lightVector), 0.0f);
	// diffuse component (light color * intensity)
	vec4 diffuse = dot_product * vec4(lightColor, 1.0f) * lightIntensity;
	// specular component (Phong's model)
	vec4 specular = vec4(0.0f);
	if (dot_product > 0.0f) { // only calculate specular if the light hits the front side
		vec3 viewDir = normalize(viewPosition - ex_worldPosition.xyz);
		vec3 reflectDir = reflect(-lightVector, normal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f); // shininess = 32
		specular = vec4(lightColor * spec * lightIntensity, 1.0f);
	}

	// a combination of ambient, diffuse and specular components
	out_Color = ambient + diffuse + specular;
};
