//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h> 

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp>

#include "ShaderLoader.h"

using namespace std;

const float points [36] = {
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,

    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
};



static void error_callback(int error, const char* description) {
    fputs(description, stderr);
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


    // get version info
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);
    //vertex buffer object (VBO)
    GLuint VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    //Vertex Array Object (VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //enable vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(sizeof(float) * 3));
   


    //Create and compile shaders
    GLuint shaderProgram;
    new ShaderLoader("PhongVertexShader.glsl", "PhongFragmentShader.glsl", &shaderProgram);


    glm::mat4 M = glm::mat4(1.0f);
    float angle = 0;

    glm::vec4 lp = glm::vec4(1.0, 0.0, 0.0, 1.0);
    GLint idLightPos = glGetUniformLocation(shaderProgram, "lights[0].color");
    if (idLightPos < 0) {
        printf("The variable does not exist.");
    }
    else {
        glUseProgram(shaderProgram);
        glUniform4f(idLightPos, lp.x, lp.y, lp.z, lp.w);
        glUseProgram(0);
    }


    lp = glm::vec4(0.0, 1.0, 0.0, 1.0);
    idLightPos = glGetUniformLocation(shaderProgram, "lights[2].color");
    if (idLightPos < 0) {
        printf("The variable does not exist.");
    }
    else {
        glUseProgram(shaderProgram);
        glUniform4f(idLightPos, lp.x, lp.y, lp.z, lp.w);
        glUseProgram(0);
    }


    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glBindVertexArray(VAO);
        M = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
        GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
        glUseProgram(0);
        // draw triangles
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 12); //mode,first,count
        glUseProgram(0);
        // update other events like input handling
        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window);
        angle += 0.01f;
    }
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}