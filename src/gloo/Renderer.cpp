#include "Renderer.h"
#include "AppUtils.h"
#include "Config.h"

// standard c++ libraries
#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdio.h>

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
	this->m_controller->updateCursor(); // update cursor position; prevents the first image bounce

	float deltaTextUpdate = 0.f;
	while (!glfwWindowShouldClose(this->m_window)) {
		// delta time
		this->m_deltaTime.update();
		float delta = this->m_deltaTime.getDeltaSeconds();

		deltaTextUpdate += delta;
		if (deltaTextUpdate > Config::WINDOW_TITLE_UPDATE_INTERVAL) {
			glfwSetWindowTitle(this->m_window, std::string(this->m_scene->getTitle() + " | FPS " + std::to_string(1.f / delta)).c_str());
			deltaTextUpdate = 0.f;
		}

		// process the input
		this->m_controller->processInput();

		// scene rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the color and depth buffers

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
	// current time
	std::time_t now = std::time(nullptr);
	std::tm tm_struct { };
	// . . win32/64 platform . . . . . . . . . . . . . . . . . . . . . . . . . .
	#ifdef _WIN32
	localtime_s(&tm_struct, &now);
	// . . macos / linux platform  . . . . . . . . . . . . . . . . . . . . . . .
	#elif defined(__APPLE__) || defined(__linux__)
	localtime_r(&now, &tm_struct);
	#endif
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	// formatting to string
	std::ostringstream oss;
	oss << std::put_time(&tm_struct, "%Y-%m-%d_%H:%M:%S");

	std::string ffmpegParams = "-y -f rawvideo -pixel_format rgb24 -video_size 800x600 -framerate 30 -i - -vf vflip -c:v libx264 -preset fast -crf 23 output." + oss.str() + ".mp4"; // constant rate factor: '-crf 23' vs bitrate: '-b:v 1M'

	// . . win32/64 platform . . . . . . . . . . . . . . . . . . . . . . . . . .
	#ifdef _WIN32
	this->m_capturePipe = _popen(std::string(
		AppUtils::getInstance()->getAppPath() + "/../../3rd/bin/ffmpeg/bin/" +
		"ffmpeg " + ffmpegParams).c_str(), "wb");
	// . . macos / linux platform  . . . . . . . . . . . . . . . . . . . . . . .
	#elif defined(__APPLE__) || defined(__linux__)
	this->m_capturePipe =  popen(std::string(
		"ffmpeg " + ffmpegParams).c_str(), "w");
	#endif
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
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
	// . . win32/64 platform . . . . . . . . . . . . . . . . . . . . . . . . . .
	#ifdef _WIN32
	_pclose(this->m_capturePipe);
	// . . macos / linux platform  . . . . . . . . . . . . . . . . . . . . . . .
	#elif defined(__APPLE__) || defined(__linux__)
	 pclose(this->m_capturePipe);
	#endif
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
}
