#include "Application.h"
#include "AppUtils.h"
#include "Config.h"
#include "callbacks.h"
#include "LightFlashlight.h"

// GLM
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// SOIL
#include <SOIL.h>

// standard C++ libraries
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
	// cleanup
	delete this->m_renderer;
	delete this->m_controller;

	for (auto& scene : this->m_scenes)
		delete scene.second;
}

void Application::addScene(const std::string& t_name, Scene* t_scene) {
	this->m_scenes[t_name] = t_scene;

	if (this->m_scene == nullptr) // set the first scene as the current scene
		//this->setScene(t_scene);
		this->m_scene = t_scene;
}

void Application::addScene(Scene* t_scene) {
	this->addScene(t_scene->getName(), t_scene);
}

Scene* Application::getScene(const std::string& t_name) const {
	auto it = this->m_scenes.find(t_name);

	return (it != this->m_scenes.end()) ? it->second : nullptr;
}

void Application::setScene(Scene* t_scene) {
	int width, height;
	glfwGetWindowSize(this->m_window, &width, &height);
	//glfwGetFramebufferSize(this->m_window, &width, &height);

	this->m_scene = t_scene;
	this->m_scene->callbackWindowSize(width, height); // sets the camera projection matrix to the window's aspect ratio
	this->m_scene->setAllCameras();
	this->m_scene->setAllLights();

	this->m_controller->setScene(this->m_scene);
	this->m_renderer->setScene(this->m_scene);
}

void Application::setScene(const std::string& t_name) {
	auto scene = this->getScene(t_name);

	if (scene != nullptr)
		this->setScene(scene);
}

void Application::run() {
	// set the current scene
	if (this->m_scene == nullptr) {
		//throw std::runtime_error("error >> no scene to render");
		fprintf(stderr, "error >> no scene to render\n");

		exit(EXIT_FAILURE);
	}

	this->setScene(this->m_scene);

	// gl settings
	glEnable(GL_DEPTH_TEST); // z-buffer; do depth comparisons and update the depth buffer

	// main loop; render the scene(s)
	while (!glfwWindowShouldClose(this->m_window)) {
		printf("[application] running scene '%s'\n", this->m_scene->getName().c_str());

		// render the currently set scene
		this->m_renderer->renderLoop();

		// exit code means to load another scene
		if (this->m_exitCode != exitE::EXIT
		|| (this->m_scene->getName() != Config::SYSTEM_MENU && this->getScene(Config::SYSTEM_MENU) != nullptr)) { // do not continue to the menu scene if it does not exist
			glfwSetWindowShouldClose(this->m_window, GL_FALSE); // do not close the window; will continue with another scene

			// load another scene
			if (this->m_exitCode == exitE::EXIT) {   // exit from 'non-menu' scene means...
				this->setScene(Config::SYSTEM_MENU); // ...to load the menu scene
			} else {
				Scene* scene = this->getScene("scene::" + std::to_string(this->m_exitCode));

				if (scene != nullptr)
					this->setScene(scene);
				else
					fprintf(stderr, "[application] warning : scene %d does not exist\n", this->m_exitCode);
			}

			this->m_exitCode = exitE::EXIT_CONTINUE;
		}
	}

	// cleanup and exit
	glfwDestroyWindow(this->m_window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

void Application::callbackDispatcherFramebufferSize(GLFWwindow* t_window, int t_width, int t_height) {
	//printf("[application] callback framebuffer size : width %d, height %d\n", t_width, t_height);

	glViewport(0, 0, t_width, t_height);

	if (this->m_scene != nullptr)
		this->m_scene->callbackWindowSize(t_width, t_height);
}

void Application::callbackDispatcherKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) {
	//printf("[application] callback key : key %d, scancode %d, action %d, mods %d\n", t_key, t_scancode, t_action, t_mods);

	// 'ESC' key to close the window
	if (t_key == GLFW_KEY_ESCAPE && t_action == GLFW_PRESS) {
		this->m_exitCode = exitE::EXIT;

		glfwSetWindowShouldClose(t_window, GL_TRUE);
	}

	// '1' to '9' keys to close the window with the corresponding exit action
	if (t_key >= GLFW_KEY_1 && t_key <= GLFW_KEY_9 && t_action == GLFW_PRESS) {
		if (this->m_scene != nullptr && this->m_scene->getName() == Config::SYSTEM_MENU) {
			this->m_exitCode = static_cast<exitE>(t_key - GLFW_KEY_0);

			glfwSetWindowShouldClose(t_window, GL_TRUE);
		}
	}

	// 'X' key to toggle fullscreen
	if (t_key == GLFW_KEY_X && t_action == GLFW_PRESS) {
		GLFWmonitor* monitor = glfwGetWindowMonitor(t_window);
		if (monitor) {
			// is fullscreen
			glfwSetWindowMonitor(t_window, NULL, 0, 0, Config::WINDOW_SIZE.x, Config::WINDOW_SIZE.y, GLFW_DONT_CARE);
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

	// scene-specific key callbacks
	if (this->m_scene != nullptr)
		this->m_scene->callbackKey(t_window, t_key, t_scancode, t_action, t_mods);
}

// --- private -----------------------------------------------------------------
Application::Application() {
	this->m_windowXpos = this->m_windowYpos = 100;
	this->m_exitCode = exitE::EXIT_CONTINUE;

	glfwSetErrorCallback(callbackError); // error callback

	// window
	this->initWindow();

	this->showVersionInfo();
	this->showSplashScreen();

	// controler, renderer; scene(s) will be added later
	this->m_controller = new Controller(this->m_window);
	this->m_renderer = new Renderer(this->m_window, this->m_controller);

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
		//throw std::runtime_error("error >> could not start GLFW3");
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
	} else
		this->m_window = glfwCreateWindow(Config::WINDOW_SIZE.x, Config::WINDOW_SIZE.y, Config::WINDOW_TITLE.c_str(), NULL, NULL);

	if (!this->m_window) {
		glfwTerminate();

		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->m_window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	this->updateViewport(); // update the viewport to the window size; respecting the framebuffer size
}

void Application::updateViewport() {
	int width, height;
	glfwGetFramebufferSize(this->m_window, &width, &height);

	glViewport(0, 0, width, height);
}

void Application::showVersionInfo() {
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
	glGetIntegerv(GL_MAX_COMBINED_UNIFORM_BLOCKS, &glInt); printf("GL_MAX_COMBINED_UNIFORM_BLOCKS: %i\n\n", glInt);

	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &glInt);      printf("GL_MAX_UNIFORM_BLOCK_SIZE: %i\n", glInt);
	glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &glInt); printf("GL_MAX_UNIFORM_BUFFER_BINDINGS: %i\n\n", glInt);

	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &glInt); printf("GL_MAX_TEXTURE_IMAGE_UNITS: %i\n", glInt);
	printf("--------------------------------------------------------------------------------\n");
}

void Application::showSplashScreen() {
	// load image; texture
	GLuint texture = SOIL_load_OGL_texture(
		(AppUtils::getInstance()->getResourcesPath() + Config::SYSTEM_RESOURCES_RELPATH_TEXTURES + Config::SYSTEM_SPLASH_IMAGE).c_str(),
		SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (!texture) {
		//throw std::runtime_error("error >> could not load splash image: " + SOIL_last_result());
		fprintf(stderr, "error >> could not load splash image: %s\n", SOIL_last_result());

		exit(EXIT_FAILURE);
	}

	// draw a square with the texture
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f); glVertex2f(-1.f, -1.f); // left bottom corner
	glTexCoord2f(1.f, 0.f); glVertex2f( 1.f, -1.f); // right bottom corner
	glTexCoord2f(1.f, 1.f); glVertex2f( 1.f,  1.f); // right top corner
	glTexCoord2f(0.f, 1.f); glVertex2f(-1.f,  1.f); // left top corner
	glEnd();

	glfwSwapBuffers(this->m_window);

	// cleanup; free the texture
	glDeleteTextures(1, &texture);
}
