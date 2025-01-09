#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin06 : public SceneBuilderPlugin {
protected:
	virtual void createShaders() override;
	virtual void createLights() override;
	virtual void createModels() override;
	virtual void loadTextures() override;

	virtual void postProcess() override;
	virtual void addContextToScene() override;

private:
	std::vector<std::pair<glm::vec3, glm::vec3>> m_wallPositions;

	//void generateWallPositions();

	float randomFloat(float minVal, float maxVal);
	void generateWallsAlongAxis(std::vector<std::pair<glm::vec3, glm::vec3>>& walls, char axis, float fixedCoord, int count, bool rotate90 = false);
	std::vector<std::pair<glm::vec3, glm::vec3>> generateWallPositions();
};
