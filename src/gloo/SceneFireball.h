#pragma once

#include "Scene.h"
#include "ModelFireball.h"

class SceneFireball : public Scene {
public:
	SceneFireball(const std::string& t_name, Camera* t_camera);
	SceneFireball(Camera* t_camera);

	virtual void callbackKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) override;

private:
	void chargeFireball(ModelFireball::fireballTypeE t_type);
	void throwFireball();

	/**/
	std::vector<std::vector<glm::vec3>> generateSpiralBezierCurves(
		const std::vector<glm::vec3>& bezierCurve, float radius, int numTurns, int numSegments);
	std::vector<std::vector<glm::vec3>> zigZagCurve(const std::vector<glm::vec3>& t_bezierCurve, float t_power);
};
