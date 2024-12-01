/* tmp vertex shader */
//#version 460 core // GLSL latest version
#version 430 core // latest version supported by VMware SVGA 3D virtual graphics driver

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
	//vec4 worldPositionNotNormalized = modelMatrix * vec4(position, 1.f); // in case the modelMatrix contains a projection transformation (e.g. perspective); not normalized homogeneous vector
	//worldPosition = worldPositionNotNormalized.xyz / worldPositionNotNormalized.w; // perspective division
	worldPosition = (modelMatrix * vec4(position, 1.f)).xyz; // in case the modelMatrix contains only affine transformations (rotation, translation, scaling)
	worldNormal = normalMatrix * normal;

	// vertex position in the clip space
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.f);
}
