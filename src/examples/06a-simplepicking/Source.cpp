#define GLM_ENABLE_EXPERIMENTAL
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h> 

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp>

#include <SOIL.h>

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags


#include <iostream>
#include <fstream>
#include <iomanip>   // std::setprecision, std::setw
#include <vector>

#include "ShaderLoader.h"

using namespace std;

//import cube.obj
const float skycube[108] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f, 
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

GLuint shaderProgram=0;
int width, height;
int x, y;

static void window_size_callback(GLFWwindow* window, int w, int h) {
    width = w; height = h;
    glViewport(0, 0, width, height);
}

static void error_callback(int error, const char* description) { 
    fputs(description, stderr); 
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
}

static void cursor_callback(GLFWwindow* window, double cx, double cy) { x = cx; y = cy; }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
    if (action == GLFW_PRESS) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        GLbyte color[4];
        GLfloat depth;
        GLuint index; // identifikace tělesa
        int newy = height - y - 10;
        glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
        printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
    }

}
int main(void)
{
    GLFWwindow* window;
   
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
    
    window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

   
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height; //perspective matrix
    glViewport(0, 0, width, height);
    
    //Vertex Array Object (VAO)
    GLuint VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skycube), &skycube[0], GL_STATIC_DRAW);
    
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //enable vertex attributes
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

    //Create and compile shaders
    new ShaderLoader("PhongVertexShader.glsl", "PhongFragmentShader.glsl", &shaderProgram);
    
    //Textures - Albedo
    glActiveTexture(GL_TEXTURE0);
    GLuint image = SOIL_load_OGL_cubemap("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (image == NULL) {
        std::cout << "An error occurred while loading CubeMap." << std::endl;
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, image);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
   

    glm::mat4 M = glm::mat4(1.0f);
    
    
    glUseProgram(shaderProgram);
    GLint idTexUnit = glGetUniformLocation(shaderProgram, "UISky");
    glUniform1i(idTexUnit, 0);
   
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, button_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
        glBindVertexArray(VAO);
        M = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f));
        M = glm::scale(M, glm::vec3(0.2f, 0.2f, 0.2f));
        GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
        glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        // draw triangles
        glDrawArrays(GL_TRIANGLES, 0, 108); //mode,first,count

        glBindVertexArray(VAO);
        M = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
        M = glm::scale(M, glm::vec3(0.2f, 0.2f, 0.2f));
        idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
        glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
        glStencilFunc(GL_ALWAYS, 2, 0xFF);
        // draw triangles
        glDrawArrays(GL_TRIANGLES, 0, 108); //mode,first,count

        glfwPollEvents();
        glfwSwapBuffers(window);
       
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}