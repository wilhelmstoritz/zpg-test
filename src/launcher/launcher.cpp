/*
// include GLEW
#include <GL/glew.h>
// include GLFW
#include <GLFW/glfw3.h>

// include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>
*/

#include "SceneBuilder.h"
#include "SceneBuilderPlugin_scene01.h"
#include "Application.h"

int main(void) {
	SceneBuilderPlugin* sceneBuilderPlugin = new SceneBuilderPlugin_scene01();
	SceneBuilder::getInstance()->setPlugin(sceneBuilderPlugin);

	Application* myApplication = Application::getInstance();
	myApplication->run();

	return(0);
}
