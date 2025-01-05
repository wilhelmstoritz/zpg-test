#pragma once

#include "Scene.h"

class SceneFireball : public Scene {
public:
	SceneFireball(const std::string& t_name, Camera* t_camera);
	SceneFireball(Camera* t_camera);

	virtual void callbackKey(int t_key, int t_scancode, int t_action, int t_mods) override;
};
