#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin05b : public SceneBuilderPlugin {
protected:
	virtual void createShaders() override;
	virtual void createLights() override;
	virtual void createModels() override;
	virtual void loadTextures() override;

	virtual void postProcess() override;
};
