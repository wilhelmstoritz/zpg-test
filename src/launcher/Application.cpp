#include "Application.h"
#include "callbacks.h"
#include "data.h"

// include GLM
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// include the standard C++ headers
#include <iostream>

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
	// --- xtra
	float alpha = 0.f;
	glm::mat4 M = glm::mat4(1.f);

	glEnable(GL_DEPTH_TEST); // z-buffer; do depth comparisons and update the depth buffer
	// --- xtra controls
	int sizeX, sizeY;
	glfwGetWindowSize(this->m_window, &sizeX, &sizeY);

	const double centerX = sizeX / 2;
	const double centerY = sizeY / 2;
	glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide the cursor and lock it in the window
	glfwSetCursorPos(this->m_window, centerX, centerY); // set the cursor to the center of the window
	// --- xtra

	// --- ffmpeg; ffmpeg as an external process
	//FILE* ffmpeg = _popen("c:/ffmpeg/bin/ffmpeg -y -f rawvideo -pixel_format rgb24 -video_size 800x600 -framerate 30 -i - -vf vflip -c:v libx264 -preset fast -crf 23 -b:v 1M output.mp4", "wb");
	//if (!ffmpeg) std::cerr << "error: failed to open ffmpeg" << std::endl;

	//std::vector<uint8_t> pixels(sizeX * sizeY * 3); // buffer for saving images
	// --- ffmpeg

	// rendering loop
	while (!glfwWindowShouldClose(this->m_window)) {
		// --- xtra
		alpha += 0.01f;
		// --- xtra

		// --- controls --------------------------------------------------------------
		// +++ procedural solution; will be replaced by object approach (the 'Control' class)
		// keyboard control
		if (glfwGetKey(this->m_window, GLFW_KEY_UP)    == GLFW_PRESS) { this->m_camera->moveCamera( .1f); }
		if (glfwGetKey(this->m_window, GLFW_KEY_DOWN)  == GLFW_PRESS) { this->m_camera->moveCamera(-.1f); }
		if (glfwGetKey(this->m_window, GLFW_KEY_RIGHT) == GLFW_PRESS) { this->m_camera->strafeCamera( .1f, 0.f); }
		if (glfwGetKey(this->m_window, GLFW_KEY_LEFT)  == GLFW_PRESS) { this->m_camera->strafeCamera(-.1f, 0.f); }

		// mouse control
		double xpos, ypos;
		glfwGetCursorPos(this->m_window, &xpos, &ypos); // get the current position of the mouse cursor

		// calculate deltaX and deltaY relative to the center of the window
		double deltaX = xpos - centerX;
		double deltaY = ypos - centerY;

		if (glfwGetMouseButton(this->m_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
			this->m_camera->strafeCamera(static_cast<float>(deltaX / 20), static_cast<float>(-deltaY / 20));
		} else {
			this->m_camera->rotateCamera(static_cast<float>(-deltaX / 20), static_cast<float>(-deltaY / 20));
		}

		glfwSetCursorPos(this->m_window, centerX, centerY); // reset the cursor to the center of the window

		// --- scene rendering -------------------------------------------------------
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// iterate thru draw data
		for (size_t i = 0; i < this->m_renderingData.size(); ++i) {
			ModelVault::renderingDataT renderingData = this->m_renderingData[i];
			renderingData.shaderProgram->use();
			renderingData.VAO->bind();

			// --- xtra
			// +++ procedural solution; will be replaced by object approach (the 'Model' class with its own life cycle; rustling leaves, setting/rising sun etc.)
			//M = glm::rotate(glm::mat4(1.f), alpha, glm::vec3(0.f, 0.f, 1.f));
			if (i == this->m_renderingData.size() - 1)
				M = glm::rotate(glm::mat4(1.f), alpha, glm::vec3(0.f, 1.f, 0.f));
			else
				M = glm::rotate(glm::mat4(1.f), 0.f, glm::vec3(0.f, 0.f, 1.f));
			renderingData.shaderProgram->transform("modelMatrix", M);

			//this->m_camera->moveCamera(-0.01f);
			//this->m_camera->rotateCamera(1.f, 0.f);
			renderingData.shaderProgram->followCamera(this->m_camera);
			// --- xtra

			glDrawArrays(GL_TRIANGLES, renderingData.first, renderingData.count);
		}

		// --- ffmpeg; save
		//glReadPixels(0, 0, sizeX, sizeY, GL_RGB, GL_UNSIGNED_BYTE, pixels.data()); // read the screen into the pixel buffer
		//fwrite(pixels.data(), sizeof(uint8_t), pixels.size(), ffmpeg); // write data to FFmpeg
		// --- ffmpeg

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(this->m_window);
	}

	// --- ffmpeg; free resources
	//_pclose(ffmpeg);
	// --- ffmpeg

	glfwDestroyWindow(this->m_window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

//ZPGCamera* Application::getCamera() { return this->m_camera; }

// --- private -----------------------------------------------------------------
Application::Application() {
	this->init();
}

Application::~Application() {
	delete this->m_camera;
}

void Application::init() {
	// error callback
	glfwSetErrorCallback(callbackError);

	// window
	this->initWindow();

	// callbacks
	glfwSetKeyCallback(this->m_window, callbackKey);

	// scene (camera, shaders, models)
	this->m_camera = new ZPGCamera();
	this->m_renderingData = *ModelVault::getInstance()->getRenderingData();

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

	float ratio = width / (float)height;
}



/*
void Application::addVertexShader(const std::string t_name, const char* t_source) {
	MyShader* shader = new MyVertexShader(t_source);
	this->m_shaders[t_name] = shader;
}

void Application::addFragmentShader(const std::string t_name, const char* t_source) {
	MyShader* shader = new MyFragmentShader(t_source);
	this->m_shaders[t_name] = shader;
}
*/
