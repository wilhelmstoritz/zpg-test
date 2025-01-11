#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin01 : public SceneBuilderPlugin {
public:
	virtual void setSceneProperties(Scene* t_scene) override;

protected:
	virtual void createShaders() override;
	virtual void createModels() override;

	virtual void addContextToScene() override;
};
