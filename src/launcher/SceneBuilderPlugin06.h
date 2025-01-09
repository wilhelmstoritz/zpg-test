#pragma once

#include "SceneBuilderPlugin.h"

class SceneBuilderPlugin06 : public SceneBuilderPlugin {
public:
	virtual void setSceneProperties(Scene* t_scene) override;

protected:
	virtual void createShaders() override;
	virtual void createLights() override;
	virtual void createModels() override;
	virtual void loadTextures() override;

	virtual void postProcess() override;
	virtual void addContextToScene() override;

private:
	std::vector<std::pair<glm::vec3, glm::vec3>> m_wallPositions;

	std::vector<std::pair<glm::vec3, glm::vec3>> generateWallPositions();
	void generateWallsAlongAxis(std::vector<std::pair<glm::vec3, glm::vec3>>& t_walls,
		char t_axis, float t_fixedCoord, size_t t_count, bool t_rotate90 = false);

	glm::vec3 minRange(); // min wall size range
	glm::vec3 maxRange(); // max wall size range
};
