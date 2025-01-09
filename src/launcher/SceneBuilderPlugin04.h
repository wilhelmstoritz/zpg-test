#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin04 : public SceneBuilderPlugin {
public:
	virtual void setSceneProperties(Scene* t_scene) override;

protected:
	virtual void createShaders() override;
	virtual void createLights() override;
	virtual void createModels() override;

	virtual void postProcess() override;
	virtual void addContextToScene() override;
};
