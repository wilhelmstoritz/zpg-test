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
#include "SceneBuilderPluginEmptyScene.h"
#include "SceneBuilderPlugin01.h"
#include "SceneBuilderPlugin02a.h"
#include "SceneBuilderPlugin02b.h"
#include "SceneBuilderPlugin03.h"
#include "SceneBuilderPlugin04.h"
#include "Application.h"

int main(void) {
	//SceneBuilderPlugin* sceneBuilderPlugin = new SceneBuilderPluginEmptyScene(); // empty scene; testing purposes
	//SceneBuilderPlugin* sceneBuilderPlugin = new SceneBuilderPlugin01(); // task 01; basic geometries
	//SceneBuilderPlugin* sceneBuilderPlugin = new SceneBuilderPlugin02a(); // task 02a; zpg models
	//SceneBuilderPlugin* sceneBuilderPlugin = new SceneBuilderPlugin02b(); // task 02b; woods; normals used as colors
	//SceneBuilderPlugin* sceneBuilderPlugin = new SceneBuilderPlugin03(); // task 03; illuminated spheres
	SceneBuilderPlugin* sceneBuilderPlugin = new SceneBuilderPlugin04(); // task 04; magic woods
	SceneBuilder::getInstance()->setPlugin(sceneBuilderPlugin);

	Application* myApplication = Application::getInstance();
	myApplication->run();

	return(0);
}
