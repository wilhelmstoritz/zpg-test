#include "Renderer.h"

// include the standard C++ headers
#include <iostream>

// --- public ------------------------------------------------------------------
Renderer::Renderer(GLFWwindow* t_window, Controller* t_controller, const Scene& t_scene)
	: m_window(t_window), m_controller(t_controller), m_scene(t_scene) { }

void Renderer::renderLoop() {
	// pre-loop processing
	//this->preLoopProcessing();

	// rendering loop
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
	// ffmpeg as an external process
	//this->m_ffmpeg = _popen("../../3rd/bin/ffmpeg/bin/ffmpeg -y -f rawvideo -pixel_format rgb24 -video_size 800x600 -framerate 30 -i - -vf vflip -c:v libx264 -preset fast -crf 23 -b:v 1M output.mp4", "wb");
	this->m_ffmpeg = _popen("../../3rd/bin/ffmpeg/bin/ffmpeg -y -f rawvideo -pixel_format rgb24 -video_size 800x600 -framerate 30 -i - -vf vflip -c:v libx264 -preset fast -crf 23 output.mp4", "wb");
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
