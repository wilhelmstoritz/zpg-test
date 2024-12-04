/* 3rd task; fragment shader; Lambertian shading, single light */
//#version 460 core // GLSL latest version
#version 430 core // latest version supported by VMware SVGA 3D virtual graphics driver

uniform int mode; // rendering mode

uniform vec3 lightPosition;

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
    vec3 L = normalize(lightPosition - worldPosition); // vector from the light to the surface
    vec3 N = normalize(worldNormal);

    // Lambert's cosine law; dot product
    float lambertian = max(dot(N, L), 0.f);

    fragmentColor = vec4(
        kAmbient * ambientColor +
        kDiffuse * lambertian * diffuseColor, 1.f);

    if (mode == 1) // only ambient
        fragmentColor = vec4(kAmbient * ambientColor, 1.f);
    else if (mode == 2) // only diffuse
        fragmentColor = vec4(kDiffuse * lambertian * diffuseColor, 1.f);
}
