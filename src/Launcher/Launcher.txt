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



// --- callbacks ---------------------------------------------------------------
static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow *window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}



// --- data & shaders definitions ----------------------------------------------
// --- triangle ---
float triangle_points_DEFAULT[] = {
	 0.0f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};
float triangle_points[] = {
	// coords            // color
	 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // red
	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // green
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // blue
};

const char* triangle_vertex_shader_DEFAULT =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"}";
const char* triangle_vertex_shader_DEFAULT_COLORFROMPOSITION =
"#version 330\n"
"layout(location=0) in vec3 vp;\n"
"out vec3 frag_pos;\n"
"void main () {\n"
"     frag_pos = vp;\n"
"     gl_Position = vec4 (vp, 1.0);\n"
"}";
const char* triangle_vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 color;"
"out vec3 frag_color;"
"void main () {"
"     frag_color = color;"
"     gl_Position = vec4 (vp, 1.0);"
"}";

const char* triangle_fragment_shader_DEFAULT =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";
const char* triangle_fragment_shader_DEFAULT_COLORFROMPOSITION =
"#version 330\n"
"in vec3 frag_pos;\n"
"out vec4 frag_colour;\n"
"void main () {\n"
//"     frag_colour = vec4 (frag_pos * 0.5 + 0.5, 1.0);\n"
"     frag_colour = vec4 (frag_pos + 0.5, 1.0);\n"
"}";
const char* triangle_fragment_shader =
"#version 330\n"
"in vec3 frag_color;"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (frag_color, 1.0);"
"}";

// --- square ---
float square_points[] = {
	 0.6f,  0.6f, 0.0f,
	 0.9f,  0.6f, 0.0f,
	 0.6f,  0.9f, 0.0f,
	 0.6f,  0.9f, 0.0f,
	 0.9f,  0.6f, 0.0f,
	 0.9f,  0.9f, 0.0f
};

const char* square_vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;\n"
"void main () {\n"
"     gl_Position = vec4(vp, 1.0);\n"
"}";

const char* square_fragment_shader =
"#version 330\n"
"out vec4 frag_colour;\n"
"void main () {\n"
"     frag_colour = vec4(1.0, 1.0, 0.0, 1.0); // yellow\n"
"}";



int main(void) {
	// --- opengl initialization -----------------------------------------------
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	/* //inicializace konkretni verze
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);  //*/

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

	// --- VBO a VAO pro následné vykreslování modelu --------------------------
	// Vertex Buffer Object (VBO); blok paměti s daty
	// --- triangle ---
	GLuint triangle_VBO = 0;
	glGenBuffers(1, &triangle_VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, triangle_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_points), triangle_points, GL_STATIC_DRAW);

	// --- square ---
	GLuint square_VBO = 0;
	glGenBuffers(1, &square_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, square_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_points), square_points, GL_STATIC_DRAW);

	// Vertex Array Object (VAO)
	// --- triangle ---
	GLuint triangle_VAO = 0;
	glGenVertexArrays(1, &triangle_VAO); //generate the VAO
	glBindVertexArray(triangle_VAO); //bind the VAO

	/*
	// DEFAULT
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, triangle_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	*/

	// WITH COLOR DATA
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, triangle_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// --- square ---
	GLuint square_VAO = 0;
	glGenVertexArrays(1, &square_VAO);
	glBindVertexArray(square_VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, square_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// ---  vertex a fragment shader a následně shader program -----------------
	// create and compile shaders
	// --- triangle ---
	GLuint triangleVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(triangleVertexShader, 1, &triangle_vertex_shader, NULL);
	glCompileShader(triangleVertexShader);

	GLuint triangleFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(triangleFragmentShader, 1, &triangle_fragment_shader, NULL);
	glCompileShader(triangleFragmentShader);

	GLuint triangleShaderProgram = glCreateProgram();
	glAttachShader(triangleShaderProgram, triangleFragmentShader);
	glAttachShader(triangleShaderProgram, triangleVertexShader);
	glLinkProgram(triangleShaderProgram);

	// check for shader program compilation and linking errors
	GLint status;
	glGetProgramiv(triangleShaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(triangleShaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(triangleShaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Triangle shader linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	// --- square ---
	GLuint squareVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(squareVertexShader, 1, &square_vertex_shader, NULL);
	glCompileShader(squareVertexShader);

	GLuint squareFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(squareFragmentShader, 1, &square_fragment_shader, NULL);
	glCompileShader(squareFragmentShader);

	GLuint squareShaderProgram = glCreateProgram();
	glAttachShader(squareShaderProgram, squareVertexShader);
	glAttachShader(squareShaderProgram, squareFragmentShader);
	glLinkProgram(squareShaderProgram);

	// check for shader program compilation and linking errors
	//GLint square_status;
	glGetProgramiv(squareShaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(squareShaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(squareShaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Square shader linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}



	// ---  vykreslovaci smycka ------------------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw the triangle
		glUseProgram(triangleShaderProgram);
		glBindVertexArray(triangle_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // draw triangles // mode,first,count

		// draw the square
		glUseProgram(squareShaderProgram);
		glBindVertexArray(square_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
