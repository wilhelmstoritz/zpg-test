#define WIN32_LEAN_AND_MEAN // prevent redefinition of APIENTRY macro; windows.h
#define NOMINMAX
#include <windows.h>

#include "Renderer.h"

// include the standard C++ headers
#include <string>
#include <iostream>
#include <direct.h>

// --- public ------------------------------------------------------------------
Renderer::Renderer(GLFWwindow* t_window, Controller* t_controller, const Scene& t_scene)
	: m_window(t_window), m_controller(t_controller), m_scene(t_scene) { }

void Renderer::renderLoop() {
	// pre-loop processing
	//this->preLoopProcessing();

	// rendering loop
	this->m_controller->resetCursor(); // reset the cursor to the center of the window; prevents the first image bounce

	while (!glfwWindowShouldClose(this->m_window)) {
		// process the input
		this->m_controller->processInput();

		// --- scene rendering
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render the models
		for (auto* model : this->m_scene.getModels()) {
			model->draw();
		}

		// on-loop processing
		//this->onLoopProcessing();

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(this->m_window);
	}

	// post-loop processing
	//this->postLoopProcessing();
}

// --- private -----------------------------------------------------------------
void Renderer::preLoopProcessing() {
	// full path to the executable file
	char charBuffer[MAX_PATH];
	GetModuleFileNameA(nullptr, charBuffer, MAX_PATH); // ANSI character set should suffice; there is no reason to deal with Unicode

	/*
	// get the current working directory; find the last backslash and remove the file name
	std::string fullPath(charBuffer);
	std::string dirPath;
	size_t lastSlashIndex = fullPath.find_last_of("\\/");
	if (lastSlashIndex != std::string::npos) {
		dirPath = fullPath.substr(0, lastSlashIndex);
	}
	*/
	// get the current working directory
	if (_getcwd(charBuffer, MAX_PATH) != nullptr) { }; // prevents warning C6031: return value ignored: '_getcwd'

	// ffmpeg as an external process
	this->m_ffmpeg = _popen(std::string(std::string(charBuffer) + "/../../3rd/bin/ffmpeg/bin/ffmpeg -y -f rawvideo -pixel_format rgb24 -video_size 800x600 -framerate 30 -i - -vf vflip -c:v libx264 -preset fast -crf 23 output.mp4").c_str(), "wb"); // constant rate factor: '-crf 23' vs bitrate: '-b:v 1M'
	if (!this->m_ffmpeg)
		std::cerr << "error: failed to open ffmpeg" << std::endl;

	glfwGetWindowSize(this->m_window, &this->m_sizeX, &this->m_sizeY);

	this->m_pixels.resize(this->m_sizeX * this->m_sizeY * 3); // buffer for saving images
}

void Renderer::onLoopProcessing() {
	// ffmpeg save
	glReadPixels(0, 0, this->m_sizeX, this->m_sizeY, GL_RGB, GL_UNSIGNED_BYTE, this->m_pixels.data()); // read the screen into the pixel buffer
	fwrite(this->m_pixels.data(), sizeof(uint8_t), this->m_pixels.size(), this->m_ffmpeg); // write data to ffmpeg
}

void Renderer::postLoopProcessing() {
	// ffmpeg free resources
	_pclose(this->m_ffmpeg);
}
