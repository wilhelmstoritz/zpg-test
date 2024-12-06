#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin_scene01 : public SceneBuilderPlugin {
protected:
	virtual void createShaders() override;
	virtual void createModels() override;
};
