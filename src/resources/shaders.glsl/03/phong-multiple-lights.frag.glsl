/* 3rd task; fragment shader; Phong shading, multiple lights */
//#version 460 core // GLSL latest version
#version 430 core // latest version supported by VMware SVGA 3D virtual graphics driver

uniform int numLights; // number of lights
uniform int mode; // rendering mode

uniform vec3 eyePosition;
uniform vec3 lightPositions[10];

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
        vec3 L = normalize(lightPositions[i] - worldPosition); // vector from the light to the surface

        // Lambert's cosine law; dot product
        float lambertian = max(dot(N, L), 0.f);

        float specular = 0.f;
        if (lambertian > 0.f) { // specular only if the light hits the front side
            vec3 R = reflect(-L, N); // reflected light vector
            vec3 V = normalize(eyePosition - worldPosition); // vector to viewer

            // specular component (Phong's model)
            //float specularAngle = max(dot(R, V), 0.f);
            //specular = pow(specularAngle, kShininess);
            specular = pow(max(dot(R, V), 0.f), kShininess);
        }

        // add the current light contribution value
        if (mode == 0) // all components
            tmpColor += kDiffuse * lambertian * diffuseColor +
                        kSpecular * specular * specularColor;
        else if (mode == 2) // diffuse only
            tmpColor += kDiffuse * lambertian * diffuseColor;
        else if (mode == 3) // specular only
            tmpColor += kSpecular * specular * specularColor;
    }

    if (mode == 0 || mode == 1) // all components or ambient only
        tmpColor += kAmbient * ambientColor;

    fragmentColor = vec4(tmpColor, 1.f);
}
