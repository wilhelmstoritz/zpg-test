/* 5th task; vertex shader; cubemap texture (from position) */
//#version 460 core // GLSL latest version
#version 430 core // latest version supported by VMware SVGA 3D virtual graphics driver

uniform mat4 modelMatrix, viewMatrix, projectionMatrix;

// input variables; from the vertex buffer, must match VBO attributes
layout(location = 0) in vec3 position;

// output variables; will be passed to the fragment shader
out vec2 textureCoord;

void main() {
	float minCoord = -100.f;
	float maxCoord =  100.f;
	textureCoord = (position.xz - minCoord) / (maxCoord - minCoord);

	// vertex position in the clip space
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.f);
}
