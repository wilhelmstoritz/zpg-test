/* tmp fragment shader */
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
    vec3 specularColor;

    // attenuation coefficients
    vec3 attenuation; // x: constant (basic light intensity), y: linear (depends on the range of the light), z: quadratic (larger value ensures faster attenuation)
};

// lights SSBO
layout(std430, binding = 0) buffer LightsBuffer {
    light lights[]; // light source buffer; dynamic size
};

/* replaced by SSBO implementation
uniform light lights[MAX_LIGHTS]; // light sources */
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
        }
        else { // point light / spotlight
            L = normalize(lights[i].lightPosition - worldPosition); // vector from the light to the surface
        }

        // spotlight
        float spot = 1.f;
        if (lights[i].lightType == 2) { // spotlight
            vec3 S = normalize(lights[i].lightDirection);

            spot = dot(-L, S);
            if (spot < lights[i].spotCutoff) {
                //lambertian = 0.f;
                //specular = 0.f;
                continue; // skip this light
            }
            spot = (spot - lights[i].spotCutoff) / (1 - lights[i].spotCutoff);
        }

        // attenuation
        float attenuation = 1.f;
        if (lights[i].lightType == 1 || lights[i].lightType == 2) { // point light or spotlight
            float distance = length(lights[i].lightPosition - worldPosition); // distance from light
            attenuation = 1.f / (lights[i].attenuation.x + // constant (basic light intensity)
                lights[i].attenuation.y * distance + // linear (depends on the range of the light)
                lights[i].attenuation.z * distance * distance); // quadratic (larger value ensures faster attenuation)
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
            //specular = pow(max(dot(R, V), 0.f), kShininess);
            specular = pow(max(dot(R, V), .001f), kShininess); // to ensure numerical stability
        }

        // add the current light contribution value
        if (mode == 0) // all components
            tmpColor += (kDiffuse * lambertian * lights[i].diffuseColor +
                kSpecular * specular * lights[i].specularColor) * attenuation * spot;
        else if (mode == 2) // diffuse only
            tmpColor += kDiffuse * lambertian * lights[i].diffuseColor * attenuation * spot;
        else if (mode == 3) // specular only
            tmpColor += kSpecular * specular * lights[i].specularColor * attenuation * spot;
    }

    if (mode == 0 || mode == 1) // all components or ambient only
        tmpColor += kAmbient * ambientColor;

    //fragmentColor = vec4(tmpColor, 1.f);
    fragmentColor = vec4(clamp(tmpColor, 0.f, 1.f), 1.f);
}
