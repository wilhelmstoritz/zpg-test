#include "SceneFlashlight.h"
#include "LightFlashlight.h"

// glfw
#include <GLFW/glfw3.h>

// --- public ------------------------------------------------------------------
SceneFlashlight::SceneFlashlight(const std::string& t_name, Camera* t_camera)
	: Scene(t_name, t_camera) {
	this->m_title = Config::WINDOW_TITLE
		+ Config::WINDOW_TITLE_HELP
		+ Config::WINDOW_TITLE_HELP_MOVE
		+ Config::WINDOW_TITLE_HELP_FLASHLIGHT;
}

SceneFlashlight::SceneFlashlight(Camera* t_camera)
	: SceneFlashlight("@!#?@!", t_camera) { }

void SceneFlashlight::callbackKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) {
	Scene::callbackKey(t_window, t_key, t_scancode, t_action, t_mods);

	//printf("[scene flashlight] callback key : key %d, scancode %d, action %d, mods %d\n", t_key, t_scancode, t_action, t_mods);

	// 'F' key to toggle flashlight
	if (t_key == GLFW_KEY_F && t_action == GLFW_PRESS) {
		LightFlashlight* flashlight = static_cast<LightFlashlight*>(this->getLight("flashlight"));
		if (flashlight)
			flashlight->toggle();
	}
}
