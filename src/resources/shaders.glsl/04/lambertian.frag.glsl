/* 4th task; fragment shader; Lambertian shading */
//#version 460 core // GLSL latest version
#version 430 core // latest version supported by VMware SVGA 3D virtual graphics driver

/* replaced by SSBO implementation
#define MAX_LIGHTS 256 */

struct light {
    int lightType; // 0 = directional light, 1 = point light, 2 = spotlight

    vec3 lightPosition;
    vec3 lightDirection; // spot/directional light direction
    float spotCutoff; // value of cos(radians)

    // colors
    vec3 diffuseColor;

    /* SSBO implementation; the light data structure must be the same */
    vec3 unused1; // specular color
    vec3 unused2; // attenuation
    /* SSBO implementation */
};

// lights SSBO
layout(std430, binding = 0) buffer LightsBuffer {
	light lights[]; // light source buffer; dynamic size
};

/* replaced by SSBO implementation
uniform light lights[MAX_LIGHTS]; // light sources */
uniform int numLights; // number of lights
uniform int mode; // 0 = all components, 1 = ambient only, 2 = diffuse only

uniform vec3 ambientColor;

// material properties
uniform float kAmbient; // ambient reflection coefficient
uniform float kDiffuse; // diffuse reflection coefficient

// input variables; from the vertex shader
in vec3 worldPosition; // vertex position; in world space
in vec3 worldNormal; // surface normal; in world space

// output variable for fragment color
out vec4 fragmentColor;

void main() {
    vec3 tmpColor = vec3(0.f);
    vec3 N = normalize(worldNormal);

    for (int i = 0; i < numLights; i++) {
        vec3 L; // light vector
        if (lights[i].lightType == 0) { // directional light
            L = normalize(-lights[i].lightDirection); // vector (direction) to the light source
        } else { // point light / spotlight
            L = normalize(lights[i].lightPosition - worldPosition); // vector from the light to the surface
        }

        // Lambert's cosine law; dot product
        float lambertian = max(dot(N, L), 0.f);

        // spotlight
        float spot = 1.f;
        if (lights[i].lightType == 2) { // spotlight
			vec3 S = normalize(lights[i].lightDirection);

			spot = dot(-L, S);
			if (spot < lights[i].spotCutoff) {
				lambertian = 0.f;
			}
			spot = (spot - lights[i].spotCutoff) / (1 - lights[i].spotCutoff);
        }

        // add the current light contribution value
        if (mode == 0 || mode == 2) // all components or diffuse only
            tmpColor += kDiffuse * lambertian * lights[i].diffuseColor * spot;
    }

    if (mode == 0 || mode == 1) // all components or ambient only
        tmpColor += kAmbient * ambientColor;

    fragmentColor = vec4(tmpColor, 1.f);
}
