/* fragment shader; Phong shading */
#version 330 core
#define MAX_LIGHTS 256

struct light {
    int lightType; // 0 = directional light, 1 = point light, 2 = spotlight

    vec3 lightPosition;
    vec3 lightDirection; // spot/directional light direction
    float spotCutoff;

    // color properties
    vec3 diffuseColor;
    vec3 specularColor;
};

uniform light lights[MAX_LIGHTS]; // light sources
uniform int numLights; // number of lights
uniform int mode; // 0 = all components, 1 = ambient only, 2 = diffuse only, 3 = specular only

uniform vec3 eyePosition;
uniform vec3 ambientColor;

// material properties
uniform float kAmbient; // ambient reflection coefficient
uniform float kDiffuse; // diffuse reflection coefficient
uniform float kSpecular; // specular reflection coefficient
uniform float kShininess; // shininess coefficient

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

        // Phong's model; specular reflection; 'R = 2 * (N . L) * N - L'
        float specular = 0.f;
        if (lambertian > 0.f) { // specular only if the light hits the front side
            vec3 R = reflect(-L, N); // reflected light vector
            vec3 V = normalize(eyePosition - worldPosition); // vector to viewer

            // specular component (Phong's model)
            //float specularAngle = max(dot(R, V), 0.f);
            //specular = pow(specularAngle, kShininess);
            specular = pow(max(dot(R, V), 0.f), kShininess);
        }

        // spotlight
        float spot = 1.f;
        if (lights[i].lightType == 2) { // spotlight
			vec3 S = normalize(lights[i].lightDirection);

			spot = dot(-L, S);
			if (spot < lights[i].spotCutoff) {
				lambertian = 0.f;
				specular = 0.f;
			}
			spot = (spot - lights[i].spotCutoff) / (1 - lights[i].spotCutoff);
        }

        // add the current light contribution value
        if (mode == 0) // all components
            tmpColor += (kDiffuse * lambertian * lights[i].diffuseColor +
                         kSpecular * specular * lights[i].specularColor) * spot;
        else if (mode == 2) // diffuse only
            tmpColor += kDiffuse * lambertian * lights[i].diffuseColor * spot;
        else if (mode == 3) // specular only
            tmpColor += kSpecular * specular * lights[i].specularColor * spot;
    }

    if (mode == 0 || mode == 1) // all components or ambient only
        tmpColor += kAmbient * ambientColor;

    fragmentColor = vec4(tmpColor, 1.f);
}
