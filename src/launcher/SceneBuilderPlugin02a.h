#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin02a : public SceneBuilderPlugin {
protected:
	virtual void createShaders() override;
	virtual void createModels() override;
};
