// standard C++ libraries
#define WIN32_LEAN_AND_MEAN // prevent redefinition of APIENTRY macro; windows.h
#define NOMINMAX
#include <windows.h>

#include "Renderer.h"
#include "AppUtils.h"
#include "Config.h"

// standard C++ libraries
#include <string>
#include <iostream>
#include <direct.h>

// --- public ------------------------------------------------------------------
Renderer::Renderer(GLFWwindow* t_window, Controller* t_controller)
	: m_window(t_window), m_controller(t_controller) {
	// to prevent visual studio warnings; value(s) will be set later
	this->m_scene = nullptr;
}

void Renderer::setScene(Scene* t_scene) {
	this->m_scene = t_scene;
}

void Renderer::renderLoop() {
	// pre-loop processing
	if (Config::SYSTEM_XTRA_RENDER_PROCESSING)
		this->preLoopProcessing();

	// rendering loop
	std::string windowTitle = glfwGetWindowTitle(this->m_window);
	float deltaTextUpdate = 0.f;

	this->m_controller->resetCursor(); // reset the cursor to the center of the window; prevents the first image bounce

	while (!glfwWindowShouldClose(this->m_window)) {
		// delta time
		this->m_deltaTime.update();
		float delta = this->m_deltaTime.getDeltaSeconds();

		deltaTextUpdate += delta;
		if (deltaTextUpdate > Config::WINDOW_TITLE_UPDATE_INTERVAL) {
			glfwSetWindowTitle(this->m_window, std::string(windowTitle + " | FPS " + std::to_string(1.f / delta)).c_str());
			deltaTextUpdate = 0.f;
		}

		// process the input
		this->m_controller->processInput();

		// scene rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth buffer

		// render the models
		for (const auto& pair : this->m_scene->getModels())
			pair.second->draw();

		// on-loop processing
		if (Config::SYSTEM_XTRA_RENDER_PROCESSING)
			this->onLoopProcessing();

		glfwPollEvents(); // update other events like input handling
		glfwSwapBuffers(this->m_window); // put the stuff we’ve been drawing onto the display
	}

	// post-loop processing
	if (Config::SYSTEM_XTRA_RENDER_PROCESSING)
		this->postLoopProcessing();
}

// --- private -----------------------------------------------------------------
void Renderer::preLoopProcessing() {
	// video capturing; ffmpeg as an external process to create capture pipe
	this->m_capturePipe = _popen(std::string(AppUtils::getInstance()->getAppPath() + "/../../3rd/bin/ffmpeg/bin/ffmpeg -y -f rawvideo -pixel_format rgb24 -video_size 800x600 -framerate 30 -i - -vf vflip -c:v libx264 -preset fast -crf 23 output.mp4").c_str(), "wb"); // constant rate factor: '-crf 23' vs bitrate: '-b:v 1M'
	if (!this->m_capturePipe)
		std::cerr << "error: failed to open ffmpeg capture pipe" << std::endl;

	glfwGetWindowSize(this->m_window, &this->m_captureXsize, &this->m_captureYsize);

	this->m_capturePixels.resize(this->m_captureXsize * this->m_captureYsize * 3); // buffer for saving images
}

void Renderer::onLoopProcessing() {
	// video capturing; save the frame to the video
	glReadPixels(0, 0, this->m_captureXsize, this->m_captureYsize, GL_RGB, GL_UNSIGNED_BYTE, this->m_capturePixels.data()); // read the screen into the pixel buffer
	fwrite(this->m_capturePixels.data(), sizeof(uint8_t), this->m_capturePixels.size(), this->m_capturePipe); // write data to capture pipe
}

void Renderer::postLoopProcessing() {
	// video capturing; free resources
	_pclose(this->m_capturePipe);
}
