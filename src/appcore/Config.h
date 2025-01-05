#pragma once

// GLM
#include <glm/vec2.hpp> // glm::vec2

// standard C++ libraries
#include <string>

class Config {
public:
	// system
	static const std::string SYSTEM_RESOURCES_PATH;
	static const std::string SYSTEM_RESOURCES_RELPATH_SHADERS;
	static const std::string SYSTEM_RESOURCES_RELPATH_MODELS;
	static const std::string SYSTEM_RESOURCES_RELPATH_TEXTURES;
	static const std::string SYSTEM_RESOURCES_RELPATH_FONTS;

	static const std::string SYSTEM_BITMAP_FONT;
	static const glm::uvec2  SYSTEM_BITMAP_FONT_SIZE;

	static const std::string SYSTEM_MENU; // the name of the menu scene

	bool static const SYSTEM_XTRA_RENDER_PROCESSING; // additional render processing; e.g. grabbing the output of the framebuffer and saving it to a video file

	// window
	static const unsigned int WINDOW_WIDTH;
	static const unsigned int WINDOW_HEIGHT;
	bool static const WINDOW_FULLSCREEN;

	static const std::string WINDOW_TITLE;
	static const float WINDOW_TITLE_UPDATE_INTERVAL;

	// skybox
	static const float SKYBOX_XMIN;
	static const float SKYBOX_XMAX;
	static const float SKYBOX_YMIN_REALWORLDSCENE;
	static const float SKYBOX_YMIN_VIRTUALWORLDSCENE;
	static const float SKYBOX_YMAX;
	static const float SKYBOX_ZMIN;
	static const float SKYBOX_ZMAX;

	// movement; speed (in units per second)
	static const float MOVEMENT_SPEED_WALK;
	static const float MOVEMENT_SPEED_RUN;

	static const float MOUSE_SENSITIVITY;

	static const bool STAY_INSIDE_SKYBOX;
	static const float STAY_INSIDE_SKYBOX_BORDER;
	static const float STAY_INSIDE_SKYBOX_EPSILON; // the range for calculating movement along the wall; minimum distance to the skybox limits

	// player
	static const float CAMERA_FOV;
	static const float CAMERA_NEAR;
	static const float CAMERA_FAR;
	static const float CAMERA_HEIGHT;

	static const float FLASHLIGHT_CUTOFF;
	static const float FLASHLIGHT_ATTENUATION_CONSTANT;
	static const float FLASHLIGHT_ATTENUATION_LINEAR;
	static const float FLASHLIGHT_ATTENUATION_QUADRATIC;
	static const float FLASHLIGHT_HEIGHT;

	// environment
	static const unsigned int ENVIRONMENT_TREES;
	static const unsigned int ENVIRONMENT_BUSHES;
	static const unsigned int ENVIRONMENT_FIREFLIES;
};
