/* 3rd task; fragment shader, Phong shading */
#version 330 core

uniform int numLights; // number of lights
uniform int lightType; // 0 = directional light, 1 = point light, 2 = spotlight
uniform int mode; // 0 = all components, 1 = ambient only, 2 = diffuse only, 3 = specular only

uniform vec3 eyePosition;
uniform vec3 lightPositions[10];
uniform vec3 lightDirection; // spot/directional light direction
uniform float spotCutoff;

// material properties
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

uniform float kAmbient; // ambient reflection coefficient
uniform float kDiffuse; // diffuse reflection coefficient
uniform float kSpecular; // specular reflection coefficient
uniform float kShininess; // shininess

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
        if (lightType == 0) { // directional light
            L = normalize(-lightDirection); // vector (direction) to the light source
        } else { // point light / spotlight
            L = normalize(lightPositions[i] - worldPosition); // vector from the light to the surface
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
        if (lightType == 2) { // spotlight
			vec3 S = normalize(lightDirection);

			spot = dot(-L, S);
			if (spot < spotCutoff) {
				lambertian = 0.f;
				specular = 0.f;
			}
			spot = (spot - spotCutoff) / (1 - spotCutoff);
        }

        // add the current light contribution value
        if (mode == 0) // all components
            tmpColor += (kDiffuse * lambertian * diffuseColor +
                         kSpecular * specular * specularColor) * spot;
        else if (mode == 2) // diffuse only
            tmpColor += kDiffuse * lambertian * diffuseColor * spot;
        else if (mode == 3) // specular only
            tmpColor += kSpecular * specular * specularColor * spot;
    }

    if (mode == 0 || mode == 1) // all components or ambient only
        tmpColor += kAmbient * ambientColor;

    fragmentColor = vec4(tmpColor, 1.f);
}
