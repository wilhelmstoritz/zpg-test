#include "Application.h"
#include "AppMath.h"
#include "AppUtils.h"
#include "Config.h"
#include "callbacks.h"
#include "LightFlashlight.h"

// glm
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// soil
// . . win32/64 / macos platform . . . . . . . . . . . . . . . . . . . . . . . .
#if defined(_WIN32) || defined(__APPLE__)
#include <SOIL.h>
// . . linux platform  . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#elif defined(__linux__)
#include <SOIL/SOIL.h>
#endif
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// standard c++ libraries
#include <iostream>
#include <regex>

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//Application* Application::_instance = nullptr;
std::unique_ptr<Application> Application::_instance = nullptr;
std::mutex Application::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// --- public ------------------------------------------------------------------
Application* Application::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr)
		//_instance = new Application();
		_instance.reset(new Application());

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
	glfwSetWindowTitle(this->m_window, t_scene->getTitle().c_str());

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
	// current scene
	if (this->m_scene == nullptr) {
		//throw std::runtime_error("error >> no scene to render");
		fprintf(stderr, "error >> no scene to render\n");

		exit(EXIT_FAILURE);
	}

	this->setScene(this->m_scene);

	// window(s)
	glfwShowWindow(this->m_window);

	if (this->m_splashWindow)
		glfwDestroyWindow(this->m_splashWindow);

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
				Scene* scene = this->getScene("scene::" + std::to_string(static_cast<int>(this->m_exitCode)));

				if (scene != nullptr)
					this->setScene(scene);
				else
					fprintf(stderr, "[application] warning : scene %d does not exist\n", static_cast<int>(this->m_exitCode));
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
			glfwSetWindowPos(t_window, this->m_windowPos.x, this->m_windowPos.y);
		} else {
			// is windowed
			glfwGetWindowPos(t_window, &this->m_windowPos.x, &this->m_windowPos.y);

			GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

			glfwSetWindowMonitor(t_window, primaryMonitor, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);
		}

		// update viewport
		int width, height;
		glfwGetFramebufferSize(t_window, &width, &height);

		this->callbackDispatcherFramebufferSize(t_window, width, height);
	}

	// 'W' key to change polygon mode; wireframe on/off
	if (t_key == GLFW_KEY_W && t_action == GLFW_PRESS) {
		this->m_polygonMode = static_cast<polygonModeE>((static_cast<int>(this->m_polygonMode) + 1) % 2); // POLYGON_FILL, POLYGON_LINE only
		this->glUpdate();
	}

	// '+' and '-' keys to change polygon thickness/size
	if ((t_key == GLFW_KEY_EQUAL || t_key == GLFW_KEY_KP_ADD) && t_action == GLFW_PRESS
		&& this->m_polygonMode != polygonModeE::POLYGON_FILL) {
		this->m_polygonSize = static_cast<float>( (static_cast<int>(this->m_polygonSize)      % 10) + 1); // cycle through {1, 2, 3...10}
		this->glUpdate();
	}

	if ((t_key == GLFW_KEY_MINUS || t_key == GLFW_KEY_KP_SUBTRACT) && t_action == GLFW_PRESS
		&& this->m_polygonMode != polygonModeE::POLYGON_FILL) {
		this->m_polygonSize = static_cast<float>(((static_cast<int>(this->m_polygonSize) + 8) % 10) + 1); // cycle through {10, 9, 8...1}
		this->glUpdate();
	}

	// scene-specific key callbacks
	if (this->m_scene != nullptr)
		this->m_scene->callbackKey(t_window, t_key, t_scancode, t_action, t_mods);
}

// --- private -----------------------------------------------------------------
Application::Application() {
	// GLFW init
	if (!glfwInit()) {
		//throw std::runtime_error("error >> could not start GLFW3");
		fprintf(stderr, "error >> could not start GLFW3\n");

		exit(EXIT_FAILURE);
	}

	/* glfwGetPlatform() is available in GLFW 3.3 and newer; not commonly included in today's linux distributions; use getenv() variant instead
	if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND) { // wayland platform is not supported; GLEW needs x11
		//throw std::runtime_error("error >> wayland platform is not supported; use x11 instead");
		fprintf(stderr, "error >> wayland platform is not supported; use x11 instead\n");

		exit(EXIT_FAILURE);
	}*/

	// . . linux platform  . . . . . . . . . . . . . . . . . . . . . . . . . . .
	#ifdef __linux__
	if (secure_getenv("XDG_SESSION_TYPE") && strcmp(secure_getenv("XDG_SESSION_TYPE"), "wayland") == 0) { // secure_getenv() is a safer version of getenv()
		//throw std::runtime_error("error >> wayland platform is not supported; use x11 instead");
		fprintf(stderr, "error >> wayland platform is not supported; use x11 instead\n");

		exit(EXIT_FAILURE);
	}
	#endif
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	/*// initialization of a specific version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //*/

	glfwSetErrorCallback(callbackError); // error callback

	// application init
	this->m_exitCode = exitE::EXIT_CONTINUE;

	this->m_polygonMode = polygonModeE::POLYGON_FILL;
	this->m_polygonSize = 1.f;

	if (Config::SYSTEM_SPLASH_SHOW)
		this->m_splashWindow = this->splashScreen();
	else
		this->m_splashWindow = nullptr;

	this->m_window = this->initWindow(); // application window
	this->glUpdate();

	this->versionInfo(); // version info; console output
	printf("[application] loading...\n");

	// controler, renderer; scene(s) will be added later
	this->m_scene = nullptr;
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

GLFWwindow* Application::splashScreen() {
	// window
	glm::uvec2 splashSize(600, 600); // splash screen size; hardcoded

	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // no window decorations
	GLFWwindow* window = glfwCreateWindow(splashSize.x, splashSize.y, Config::WINDOW_TITLE.c_str(), NULL, NULL);

	if (!window) {
		//throw std::runtime_error("error >> could not create GLFW3 window; splash screen");
		fprintf(stderr, "error >> could not create GLFW3 window; splash screen\n");
		glfwTerminate();

		exit(EXIT_FAILURE);
	}

	this->initWindowContext(window);

	// window position
	const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	glfwSetWindowPos(window,
		(videoMode->width  - splashSize.x) / 2,
		(videoMode->height - splashSize.y) / 2); // splash screen belongs in the middle of the screen

	// load image; texture
	std::string splashImage = Config::SYSTEM_SPLASH_IMAGE;
	if (Config::SYSTEM_SPLASH_RANDOM) {
		// (.*[\\/])? optional path part ending with / or \
		// ([^\\/]+?) file name without extension and number (non-greedy)
		// (\d+)?     optional number at the end of the file name
		// (\.[^.]+)  file extension
		std::regex pattern(R"((.*[\\/])?([^\\/]+?)(\d+)?(\.[^.]+)$)");

		std::smatch match;
		if (std::regex_match(splashImage, match, pattern))
			// match[1] = file path
			// match[2] = file name without number
			// match[4] = file extension
			splashImage = match[1].str() + match[2].str()
				+ std::to_string(AppMath::getInstance()->randomNumber(static_cast<size_t>(1), Config::SYSTEM_SPLASH_RANDOM_COUNT))
				+ match[4].str();
	}

	GLuint texture = SOIL_load_OGL_texture(
		(AppUtils::getInstance()->getResourcesPath() + Config::SYSTEM_RESOURCES_RELPATH_TEXTURES + splashImage).c_str(),
		SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (!texture) {
		//throw std::runtime_error("error >> could not load splash image: " + splashImage + "; " + SOIL_last_result());
		fprintf(stderr, "error >> could not load splash image: %s; %s\n", splashImage.c_str(), SOIL_last_result());

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

	glfwSwapBuffers(window); // put the stuff we’ve been drawing onto the display

	// cleanup; free the texture
	glDeleteTextures(1, &texture);

	return window;
}

GLFWwindow* Application::initWindow() {
	// window
	GLFWwindow* window;
	glfwWindowHint(GLFW_VISIBLE,   GLFW_FALSE); // hide the window for now
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);  // window decorations; frame, title bar, etc.
	if (Config::WINDOW_FULLSCREEN) {
		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

		window = glfwCreateWindow(videoMode->width,      videoMode->height,     Config::WINDOW_TITLE.c_str(), primaryMonitor, NULL);
	} else
		window = glfwCreateWindow(Config::WINDOW_SIZE.x, Config::WINDOW_SIZE.y, Config::WINDOW_TITLE.c_str(), NULL,           NULL);

	if (!window) {
		//throw std::runtime_error("error >> could not create GLFW3 window; app window");
		fprintf(stderr, "error >> could not create GLFW3 window; app window\n");
		glfwTerminate();

		exit(EXIT_FAILURE);
	}

	this->initWindowContext(window);

	// window position
	const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	this->m_windowPos = glm::ivec2(
		(videoMode->width  - Config::WINDOW_SIZE.x) / 2,
		(videoMode->height - Config::WINDOW_SIZE.y) / 2);

	glfwSetWindowPos(window, this->m_windowPos.x, this->m_windowPos.y); // the middle of the screen

	// GLEW extension handler
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		//throw std::runtime_error("error >> could not start GLEW");
		fprintf(stderr, "error >> could not start GLEW\n");
		glfwTerminate();

		exit(EXIT_FAILURE);
	}

	return window;
}

void Application::initWindowContext(GLFWwindow* t_window) {
	glfwMakeContextCurrent(t_window);
	glfwSwapInterval(1);

	// viewport
	int width, height;
	glfwGetFramebufferSize(t_window, &width, &height);

	glViewport(0, 0, width, height);
}

void Application::glUpdate() {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the color and depth buffers

	glEnable(GL_DEPTH_TEST); // z-buffer; do depth comparisons and update the depth buffer

	switch (this->m_polygonMode) { // polygon mode
	case polygonModeE::POLYGON_FILL:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;

	case polygonModeE::POLYGON_LINE:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(this->m_polygonSize);
		break;

	case polygonModeE::POLYGON_POINT:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glPointSize(this->m_polygonSize);
		break;
	}
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
	glGetIntegerv(GL_MAX_COMBINED_UNIFORM_BLOCKS, &glInt); printf("GL_MAX_COMBINED_UNIFORM_BLOCKS: %i\n\n", glInt);

	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &glInt);      printf("GL_MAX_UNIFORM_BLOCK_SIZE: %i\n", glInt);
	glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &glInt); printf("GL_MAX_UNIFORM_BUFFER_BINDINGS: %i\n\n", glInt);

	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &glInt); printf("GL_MAX_TEXTURE_IMAGE_UNITS: %i\n", glInt);
	printf("--------------------------------------------------------------------------------\n");
}
