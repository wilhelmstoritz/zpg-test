#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin02b : public SceneBuilderPlugin {
public:
	virtual void setSceneProperties(Scene* t_scene) override;

protected:
	virtual void createShaders() override;
	virtual void createModels() override;

	virtual void postProcess() override;
	virtual void addContextToScene() override;
};
