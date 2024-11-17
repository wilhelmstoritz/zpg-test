#version 330 core

uniform mat4 modelMatrix, viewMatrix, projectionMatrix;
uniform mat3 normalMatrix; // (M^-1)^T; for transforming normals

// input variables; from the vertex buffer, must match VBO attributes
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

// output variables; will be passed to the fragment shader
out vec3 worldPosition;
out vec3 worldNormal;

void main() {
	// position and normal in world space
	worldPosition = (modelMatrix * vec4(position, 1.f)).xyz;
	worldNormal = normalMatrix * normal;

	// vertex position in the clip space
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.f);
}
