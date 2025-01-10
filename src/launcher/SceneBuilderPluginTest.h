#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPluginTest : public SceneBuilderPlugin {
public:
	virtual void setSceneProperties(Scene* t_scene) override;

protected:
	virtual void createShaders() override;
	virtual void createLights() override;
	virtual void createModels() override;

	virtual void postProcess() override;
};
