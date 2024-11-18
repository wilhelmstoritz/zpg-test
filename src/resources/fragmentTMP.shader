/* 3rd task; fragment shader, Phong shading */
#version 330 core

uniform vec3 eyePosition;
uniform vec3 lightPosition;
uniform vec3 spotDirection;
uniform float spotCutoff;

// material properties
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

uniform float kAmbient; // ambient reflection coefficient
uniform float kDiffuse; // diffuse reflection coefficient
uniform float kSpecular; // specular reflection coefficient
uniform float kShininess; // shininess

uniform int mode; // rendering mode

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
    
    float specular = 0.f;
    float spot = 1.f;
    if (lambertian > 0.f) { // specular only if the light hits the front side
        vec3 R = reflect(-L, N); // reflected light vector
        vec3 V = normalize(eyePosition - worldPosition); // vector to viewer
        vec3 S = normalize(spotDirection);

        // specular component (Phong's model)
        //float specularAngle = max(dot(R, V), 0.f);
        //specular = pow(specularAngle, kShininess);
        specular = pow(max(dot(R, V), 0.f), kShininess);

        spot = dot(-L, S);
        if (spot < spotCutoff) {
            lambertian = 0.f;
            specular = 0.f;
        }
        spot = (spot - spotCutoff) / (1 - spotCutoff);
    }

    fragmentColor = vec4(
        kAmbient * ambientColor +
       (kDiffuse * lambertian * diffuseColor +
        kSpecular * specular * specularColor) * spot, 1.f);

    if (mode == 1) // only ambient
        fragmentColor = vec4(kAmbient * ambientColor, 1.f);
    else if (mode == 2) // only diffuse
        fragmentColor = vec4(kDiffuse * lambertian * diffuseColor * spot, 1.f);
    else if (mode == 3) // only specular
        fragmentColor = vec4(kSpecular * specular * specularColor * spot, 1.f);
}
