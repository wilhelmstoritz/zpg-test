#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin01 : public SceneBuilderPlugin {
protected:
	virtual void createShaders() override;
	virtual void createModels() override;

	virtual void addContextToScene() override;
};
