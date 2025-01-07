#pragma once

#include "Scene.h"

class SceneFlashlight : public Scene {
public:
	SceneFlashlight(const std::string& t_name, Camera* t_camera);
	SceneFlashlight(Camera* t_camera);

	virtual void callbackKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) override;
};
