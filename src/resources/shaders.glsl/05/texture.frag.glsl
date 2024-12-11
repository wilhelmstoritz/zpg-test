/* 5th task; fragment shader; texture */
//#version 460 core // GLSL latest version
#version 430 core // latest version supported by VMware SVGA 3D virtual graphics driver

uniform sampler2D textureUnitID;

// input variables; from the vertex shader
in vec2 texCoord; // texture coordinates

// output variable for fragment color
out vec4 fragmentColor;

void main() {
	//vec3 tmpColor = vec3(texture(textureUnitID, texCoord)); // texture color
    vec3 tmpColor = texture(textureUnitID, texCoord); // texture color

    //fragmentColor = vec4(tmpColor, 1.f);
    fragmentColor = vec4(clamp(tmpColor, 0.f, 1.f), 1.f);
}
