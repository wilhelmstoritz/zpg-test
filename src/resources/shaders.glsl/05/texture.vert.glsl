/* 5th task; vertex shader; texture */
//#version 460 core // GLSL latest version
#version 430 core // latest version supported by VMware SVGA 3D virtual graphics driver

uniform mat4 modelMatrix, viewMatrix, projectionMatrix;

// input variables; from the vertex buffer, must match VBO attributes
layout(location = 0) in vec3 position;
layout(location = 2) in vec2 textureUV;

// output variables; will be passed to the fragment shader
out vec2 textureCoord;

void main() {
	textureCoord = textureUV;

	// vertex position in the clip space
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.f);
}
