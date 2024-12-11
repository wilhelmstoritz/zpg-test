/* 4th task; fragment shader; single color */
//#version 460 core // GLSL latest version
#version 430 core // latest version supported by VMware SVGA 3D virtual graphics driver

// color properties
uniform vec3 lightColor;
uniform float lightIntensity;

// input variables; from the vertex shader
in vec3 worldPosition; // vertex position; in world space
in vec3 worldNormal; // surface normal; in world space

// output variable for fragment color
out vec4 fragmentColor;

void main() {
    //fragmentColor = vec4(lightColor * lightIntensity, 1.f);
    fragmentColor = vec4(clamp(lightColor * lightIntensity, 0.f, 1.f), 1.f);
}
