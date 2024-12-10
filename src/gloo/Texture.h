#pragma once

// include GLEW
#include <GL/glew.h>

// include GLM
//#include <glm/vec3.hpp> // glm::vec3
//#include <glm/vec4.hpp> // glm::vec4
//#include <glm/mat4x4.hpp> // glm::mat4
//#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
//#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
//#include <glm/glm.hpp>

// include the standard C++ headers
#include <string>
//#include <stdio.h>

class Texture {
public:
	Texture(const std::string& t_name, const std::string& t_filePath);
	Texture(const std::string& t_filePath);
	//std::string getName();
	//GLuint getTextureID();
	//void bind(GLuint t_textureUnit);
	//void unbind();

private:
	std::string m_name;
	GLuint m_ID;
};
