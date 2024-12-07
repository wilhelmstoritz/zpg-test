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
#include "SceneBuilderPlugin_emptyScene.h"
#include "SceneBuilderPlugin01.h"
#include "SceneBuilderPlugin02a.h"
#include "SceneBuilderPlugin02b.h"
#include "Application.h"

int main(void) {
	//SceneBuilderPlugin* sceneBuilderPlugin = new SceneBuilderPlugin_emptyScene(); // empty scene; testing purposes
	//SceneBuilderPlugin* sceneBuilderPlugin = new SceneBuilderPlugin01(); // task 01; basic geometries
	SceneBuilderPlugin* sceneBuilderPlugin = new SceneBuilderPlugin02a(); // task 02a; zpg models
	//SceneBuilderPlugin* sceneBuilderPlugin = new SceneBuilderPlugin02b(); // task 02b; woods; normals used as colors
	SceneBuilder::getInstance()->setPlugin(sceneBuilderPlugin);

	Application* myApplication = Application::getInstance();
	myApplication->run();

	return(0);
}
