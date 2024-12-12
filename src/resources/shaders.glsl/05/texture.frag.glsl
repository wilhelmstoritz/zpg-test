/* 5th task; fragment shader; texture */
//#version 460 core // GLSL latest version
#version 430 core // latest version supported by VMware SVGA 3D virtual graphics driver

uniform sampler2D textureUnit;

// input variables; from the vertex shader
in vec2 textureCoord; // texture coordinates

// output variable for fragment color
out vec4 fragmentColor;

void main() {
    fragmentColor = texture(textureUnit, textureCoord); // texture color
}
