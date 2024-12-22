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
#include "SceneBuilderPluginTest.h"
#include "SceneBuilderPlugin01.h"
#include "SceneBuilderPlugin02a.h"
#include "SceneBuilderPlugin02b.h"
#include "SceneBuilderPlugin03.h"
#include "SceneBuilderPlugin04.h"
#include "SceneBuilderPlugin05a.h"
#include "SceneBuilderPlugin05b.h"
#include "Application.h"

int main(void) {
	SceneBuilder* builder = SceneBuilder::getInstance();

	Application* application = Application::getInstance();

	//application->addScene("empty", builder->createScene(new SceneBuilderPluginEmptyScene)); // empty scene; testing purposes
	//application->addScene("test",  builder->createScene(new SceneBuilderPluginTest)); // test scene
	// zpg tasks
	//application->addScene("01",  builder->createScene(new SceneBuilderPlugin01));   // task 01; basic geometries
	//application->addScene("02a", builder->createScene(new SceneBuilderPlugin02a));  // task 02a; zpg models
	//application->addScene("02b", builder->createScene(new SceneBuilderPlugin02b));  // task 02b; woods; normals used as colors
	//application->addScene("03",  builder->createScene(new SceneBuilderPlugin03));   // task 03; illuminated spheres
	//application->addScene("04",  builder->createScene(new SceneBuilderPlugin04));   // task 04; magic woods
	application->addScene("05a", builder->createScene(new SceneBuilderPlugin05a));  // task 05a; magic woods with textured torches
	//application->addScene("05b", builder->createScene(new SceneBuilderPlugin05b));  // task 05b; dark magic woods with house, grass & zombie

	application->run();

	return(0);
}
