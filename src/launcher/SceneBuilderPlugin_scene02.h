#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin_scene02 : public SceneBuilderPlugin {
protected:
	virtual void createShaders() override;
	virtual void createModels() override;
};
