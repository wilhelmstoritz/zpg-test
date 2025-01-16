#pragma once

#include "Scene.h"
#include "ModelFireball.h"

class SceneFireball : public Scene {
public:
	SceneFireball(const std::string& t_name, Camera* t_camera);
	SceneFireball(Camera* t_camera);

	virtual void callbackKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) override;

private:
	enum class curveTypeE {
		CURVE_SPIRAL = 0,
		CURVE_ZIGZAG = 1
	};

	void chargeFireball(ModelFireball::fireballTypeE t_type);
	void throwFireball();

	std::vector<std::vector<glm::vec3>> specialCurve(const std::vector<glm::vec3>& t_bezierCurve, float t_power, curveTypeE t_type);
	glm::vec3 zigzagPoint(const glm::vec3& t_point, float t_diffRange);
	glm::vec3 spiralPoint(const glm::vec3& t_point, const glm::vec3& t_tangent, float t_radius, float t_angle);
};
