/* 5th task; fragment shader; cubemap texture (from position) */
//#version 460 core // GLSL latest version
#version 430 core // latest version supported by VMware SVGA 3D virtual graphics driver

uniform samplerCube textureUnit;

// input variables; from the vertex shader
in vec3 textureCoord; // texture coordinates

// output variable for fragment color
out vec4 fragmentColor;

void main() {
    fragmentColor = texture(textureUnit, textureCoord); // texture color
}
