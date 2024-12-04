/* 3rd task; fragment shader; Lambertian shading, multiple lights */
//#version 460 core // GLSL latest version
#version 430 core // latest version supported by VMware SVGA 3D virtual graphics driver

uniform int numLights; // number of lights
uniform int mode; // rendering mode

uniform vec3 lightPositions[10];

// material properties
uniform vec3 ambientColor;
uniform vec3 diffuseColor;

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
        vec3 L = normalize(lightPositions[i] - worldPosition); // vector from the light to the surface

        // Lambert's cosine law; dot product
        float lambertian = max(dot(N, L), 0.f);

        // add the current light contribution value
        if (mode == 0 || mode == 2) // all components or diffuse only
            tmpColor += kDiffuse * lambertian * diffuseColor;
    }

    if (mode == 0 || mode == 1) // all components or ambient only
        tmpColor += kAmbient * ambientColor;

    fragmentColor = vec4(tmpColor, 1.f);
}
