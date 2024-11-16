/* 3rd task; vertex shader, normal */
#version 330 core

// uniforms for transformation matrices
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix; // (M^-1)^T; for transforming normals

// input variables; must match VBO attributes
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

// output variables; will be passed to the fragment shader
out vec4 ex_worldPosition;
out vec3 ex_worldNormal;

void main(void) {
// vertex position in the clip space
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0f);

// position and normal in world space
	ex_worldPosition = modelMatrix * vec4(in_Position, 1.0f);
	ex_worldNormal = normalMatrix * in_Normal;
};
