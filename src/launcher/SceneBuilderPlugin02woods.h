#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin02woods : public SceneBuilderPlugin {
protected:
	virtual void createShaders() override;
	virtual void createLights() override;
	virtual void createModels() override;
};
