#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin_emptyScene : public SceneBuilderPlugin {
protected:
	virtual void createShaders() override;
	virtual void createModels() override;
	virtual void addContextToScene() override;
};
