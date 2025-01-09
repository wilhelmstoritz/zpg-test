#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPluginEmptyScene : public SceneBuilderPlugin {
protected:
	virtual void createShaders() override;
	virtual void createModels() override;
};
