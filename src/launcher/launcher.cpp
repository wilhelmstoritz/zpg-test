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

#include "Application.h"

int main(void) {
	Application* myApplication = Application::getInstance();

	myApplication->createShaders(); // vertex + fragment shaders; shader programs
    /*...........................................................................*/
    // ad-hoc and debugging purposes
    float PENTAGON[] = {
        // 1st triangle
         0.0f,     0.0f,    0.0f, // centre
         1.0f,     0.0f,    0.0f, // apex #1
         0.3090f,  0.9511f, 0.0f, // apex #2
        // 2nd triangle
         0.0f,     0.0f,    0.0f, // centre
         0.3090f,  0.9511f, 0.0f, // apex #2
        -0.8090f,  0.5878f, 0.0f, // apex #3
        // 3rd triangle
         0.0f,     0.0f,    0.0f, // centre
        -0.8090f,  0.5878f, 0.0f, // apex #3
        -0.8090f, -0.5878f, 0.0f, // apex #4
        // 4th triangle
         0.0f,     0.0f,    0.0f, // centre
        -0.8090f, -0.5878f, 0.0f, // apex #4
         0.3090f, -0.9511f, 0.0f, // apex #5
        // 5th triangle
         0.0f,     0.0f,    0.0f, // centre
         0.3090f, -0.9511f, 0.0f, // apex #5
         1.0f,     0.0f,    0.0f  // apex #1
    };

    ZPGVBO* zpgVBO = new ZPGVBO(sizeof(PENTAGON), PENTAGON);
    ZPGVAO* zpgVAO = new ZPGVAO();
    zpgVAO->addBuffer(*zpgVBO, 0, 3, 0, NULL);

    myApplication->addVAO("myVAO", zpgVAO);
    myApplication->addRenderingData(myApplication->getShaderProgram("default"), zpgVAO, 0, 15);
    /*...........................................................................*/
	myApplication->createModels(); // VBOs + VAOs
	myApplication->createRenderingData(); // shader program + VAO = data to render

	myApplication->run();
}
