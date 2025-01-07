#pragma once

#include "Scene.h"
#include "ModelFireball.h"

class SceneFireball : public Scene {
public:
	SceneFireball(const std::string& t_name, Camera* t_camera);
	SceneFireball(Camera* t_camera);

	virtual void callbackKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) override;

private:
	void chargeFireball(ModelFireball::fireballT t_type);
	void throwFireball();
};
