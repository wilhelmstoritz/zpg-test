#include "Application.h"

// include GLM
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// include the standard C++ headers
#include <iostream>

#include "callbacks.h"
#include "data.h"

// initialization of static class members
//Application* Application::_instance = nullptr;
std::unique_ptr<Application> Application::_instance = nullptr;
std::mutex Application::_mtx;

// --- public ------------------------------------------------------------------
Application* Application::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr) {
		//_instance = new Application();
		_instance.reset(new Application());
	}

	//return _instance;
	return _instance.get();
}

void Application::run() {
	glEnable(GL_DEPTH_TEST); // z-buffer; do depth comparisons and update the depth buffer

	this->m_renderer->renderLoop();

	// cleanup and exit
	glfwDestroyWindow(this->m_window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

// --- private -----------------------------------------------------------------
Application::Application() {
	// error callback
	glfwSetErrorCallback(callbackError);

	// window
	this->initWindow();
	this->versionInfo();

	// callbacks
	glfwSetKeyCallback(this->m_window, callbackKey);

	// scene (camera + shaders + models), controler, renderer
	this->m_scene = SceneBuilder::getInstance()->createScene(this->m_window);
	this->m_controller = new Controller(this->m_window, this->m_scene->getCamera());
	this->m_renderer = new Renderer(this->m_window, this->m_controller, *this->m_scene);
}

Application::~Application() {
	delete this->m_renderer;
	delete this->m_controller;
	delete this->m_scene;
}

void Application::initWindow() {
	// init window
	if (!glfwInit()) {
		fprintf(stderr, "error >> could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	/*// inicializace konkretni verze
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //*/

	// fullscreen
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

	//this->m_window = glfwCreateWindow(videoMode->width, videoMode->height, "myZPG", primaryMonitor, NULL);
	this->m_window = glfwCreateWindow(800, 600, "myZPG", NULL, NULL);
	if (!this->m_window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->m_window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// helpers
	int width, height;
	glfwGetFramebufferSize(this->m_window, &width, &height);
	glViewport(0, 0, width, height);
}

void Application::versionInfo() {
	// version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}
