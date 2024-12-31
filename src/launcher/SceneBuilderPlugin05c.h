#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin05c : public SceneBuilderPlugin {
protected:
	virtual void createShaders() override;
	virtual void createLights() override;
	virtual void createModels() override;
	virtual void loadTextures() override;

	virtual void postProcess() override;
	virtual void addContextToScene() override;
};
