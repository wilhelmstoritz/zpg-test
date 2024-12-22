#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin03 : public SceneBuilderPlugin {
protected:
	virtual void preProcess() override;

	virtual void createShaders() override;
	virtual void createLights() override;
	virtual void createModels() override;

	virtual void postProcess() override;
	virtual void addContextToScene() override;
};
