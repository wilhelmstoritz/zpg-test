#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPluginMenu : public SceneBuilderPlugin {
public:
	virtual void setSceneProperties(Scene* t_scene) override;

protected:
	virtual void preProcess() override;

	virtual void createShaders() override;
	virtual void createLights() override;
	virtual void createModels() override;

	virtual void postProcess() override;
	virtual void addContextToScene() override;
};
