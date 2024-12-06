#include "Application.h"
#include "Config.h"
#include "callbacks.h"

// include GLM
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// include the standard C++ headers
#include <iostream>

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//Application* Application::_instance = nullptr;
std::unique_ptr<Application> Application::_instance = nullptr;
std::mutex Application::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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

Application::~Application() {
	delete this->m_renderer;
	delete this->m_controller;
	delete this->m_scene;
}

void Application::run() {
	glEnable(GL_DEPTH_TEST); // z-buffer; do depth comparisons and update the depth buffer

	this->m_renderer->renderLoop();

	// cleanup and exit
	glfwDestroyWindow(this->m_window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

void Application::callbackDispatcherFramebufferSize(GLFWwindow* t_window, int t_width, int t_height) {
	//printf("[application] callback framebuffer size : width %d, height %d\n", t_width, t_height);

	glViewport(0, 0, t_width, t_height);

	_instance->m_scene->callbackFramebufferSize(t_width, t_height);
}

void Application::callbackDispatcherKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) {
	//printf("[application] callback key : key %d, scancode %d, action %d, mods %d\n", t_key, t_scancode, t_action, t_mods);

	if (t_key == GLFW_KEY_ESCAPE && t_action == GLFW_PRESS) {
		glfwSetWindowShouldClose(t_window, GL_TRUE);
	}

	if (t_key == GLFW_KEY_F && t_action == GLFW_PRESS) {
		GLFWmonitor* monitor = glfwGetWindowMonitor(t_window);
		if (monitor) {
			// is fullscreen
			glfwSetWindowMonitor(t_window, NULL, 0, 0, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, GLFW_DONT_CARE);
			glfwSetWindowPos(t_window, this->m_windowXpos, this->m_windowYpos);
		} else {
			// is windowed
			glfwGetWindowPos(t_window, &this->m_windowXpos, &this->m_windowYpos);

			GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

			glfwSetWindowMonitor(t_window, primaryMonitor, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);
		}

		// update viewport
		int width, height;
		glfwGetFramebufferSize(t_window, &width, &height);

		this->callbackDispatcherFramebufferSize(t_window, width, height);
	}
}

// --- private -----------------------------------------------------------------
Application::Application() {
	this->m_windowXpos = this->m_windowYpos = 100;

	glfwSetErrorCallback(callbackError); // error callback

	// window
	this->initWindow();
	this->versionInfo();

	// scene (camera + shaders + models), controler, renderer
	this->m_scene = SceneBuilder::getInstance()->createScene(this->m_window);
	this->m_controller = new Controller(this->m_window, this->m_scene->getCamera());
	this->m_renderer = new Renderer(this->m_window, this->m_controller, *this->m_scene);

	// callbacks
    glfwSetFramebufferSizeCallback(this->m_window, [](GLFWwindow* t_window, int t_width, int t_height) { // framebuffer (window) resize callback
		_instance->callbackDispatcherFramebufferSize(t_window, t_width, t_height);
    });

	glfwSetKeyCallback(this->m_window, [](GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) { // key callback
		_instance->callbackDispatcherKey(t_window, t_key, t_scancode, t_action, t_mods);
	});
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

	if (Config::WINDOW_FULLSCREEN) {
		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

		this->m_window = glfwCreateWindow(videoMode->width, videoMode->height, Config::WINDOW_TITLE.c_str(), primaryMonitor, NULL);
	} else {
		this->m_window = glfwCreateWindow(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, Config::WINDOW_TITLE.c_str(), NULL, NULL);
	}

	if (!this->m_window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->m_window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// update viewport
	int width, height;
	glfwGetFramebufferSize(this->m_window, &width, &height);

	glViewport(0, 0, width, height);
}

void Application::versionInfo() {
	// version info
	printf("--------------------------------------------------------------------------------\n");
	printf("vendor: %s\n", glGetString(GL_VENDOR));
	printf("renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("using GLEW %s\n", glewGetString(GLEW_VERSION));

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("using GLFW %i.%i.%i\n", major, minor, revision);
	printf("--------------------------------------------------------------------------------\n");

	// other gl parameters
	GLint glInt;

	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &glInt);   printf("GL_MAX_VERTEX_UNIFORM_VECTORS: %i\n", glInt);
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &glInt); printf("GL_MAX_FRAGMENT_UNIFORM_VECTORS: %i\n\n", glInt);

	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &glInt);            printf("GL_MAX_VERTEX_UNIFORM_COMPONENTS: %i\n", glInt);
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &glInt);          printf("GL_MAX_FRAGMENT_UNIFORM_COMPONENTS: %i\n", glInt);
	glGetIntegerv(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS, &glInt);   printf("GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS: %i\n", glInt);
	glGetIntegerv(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS, &glInt); printf("GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS: %i\n\n", glInt);

	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &glInt);   printf("GL_MAX_VERTEX_UNIFORM_BLOCKS: %i\n", glInt);
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &glInt); printf("GL_MAX_FRAGMENT_UNIFORM_BLOCKS: %i\n", glInt);
	glGetIntegerv(GL_MAX_COMBINED_UNIFORM_BLOCKS, &glInt); printf("GL_MAX_COMBINED_UNIFORM_BLOCKS: %i\n", glInt);
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &glInt);      printf("GL_MAX_UNIFORM_BLOCK_SIZE: %i\n\n", glInt);
	
	glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &glInt); printf("GL_MAX_UNIFORM_BUFFER_BINDINGS: %i\n", glInt);
	printf("--------------------------------------------------------------------------------\n");
}
