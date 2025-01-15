#pragma once

#include "Scene.h"
#include "ModelFireball.h"

class SceneFireball : public Scene {
public:
	SceneFireball(const std::string& t_name, Camera* t_camera);
	SceneFireball(Camera* t_camera);

	virtual void callbackKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) override;

private:
	enum curveTypeE {
		CURVE_SPIRAL = 0,
		CURVE_ZIGZAG = 1
	};

	void chargeFireball(ModelFireball::fireballTypeE t_type);
	void throwFireball();

	std::vector<std::vector<glm::vec3>> spiralCurve(const std::vector<glm::vec3>& t_bezierCurve, float t_power);
	std::vector<std::vector<glm::vec3>> specialCurve(const std::vector<glm::vec3>& t_bezierCurve, float t_power, curveTypeE t_type);

	glm::vec3 zigzagPoint(const glm::vec3& t_point, float t_diff);

	/**/
	std::vector<std::vector<glm::vec3>> generateSpiralBezierCurves(
		const std::vector<glm::vec3>& bezierCurve, float radius, int numTurns, int numSegments);
};
