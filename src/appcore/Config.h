#pragma once

// glm
#include <glm/vec2.hpp> // glm::vec2
#include <glm/vec3.hpp> // glm::vec3

// standard c++ libraries
#include <cstddef>
#include <string>

class Config {
public:
	// math
	static const size_t MATH_NUM_BEZIER_SAMPLES; // number of samples for the length estimation of the bezier curve

	// system
	static const std::string SYSTEM_RESOURCES_PATH;
	static const std::string SYSTEM_RESOURCES_RELPATH_SHADERS;
	static const std::string SYSTEM_RESOURCES_RELPATH_MODELS;
	static const std::string SYSTEM_RESOURCES_RELPATH_TEXTURES;
	static const std::string SYSTEM_RESOURCES_RELPATH_FONTS;

	static const std::string SYSTEM_SPLASH_IMAGE;
	static const bool        SYSTEM_SPLASH_RANDOM;       // random splash image
	static const size_t      SYSTEM_SPLASH_RANDOM_COUNT; // number of random splash images
	static const bool        SYSTEM_SPLASH_SHOW;

	static const std::string SYSTEM_BITMAP_FONT;
	static const glm::u8vec2 SYSTEM_BITMAP_FONT_SIZE;

	static const std::string SYSTEM_MENU; // the name of the menu scene

	static const bool SYSTEM_XTRA_RENDER_PROCESSING; // additional render processing; e.g. grabbing the output of the framebuffer and saving it to a video file

	// window
	static const glm::uvec2 WINDOW_SIZE;
	static const bool       WINDOW_FULLSCREEN;

	static const std::string WINDOW_TITLE;
	static const std::string WINDOW_TITLE_HELP;
	static const std::string WINDOW_TITLE_HELP_MOVE;
	static const std::string WINDOW_TITLE_HELP_FLASHLIGHT;
	static const std::string WINDOW_TITLE_HELP_FIREBALL;
	static const std::string WINDOW_TITLE_HELP_MENU;
	static const float WINDOW_TITLE_UPDATE_INTERVAL;

	// skybox
	static const glm::vec3 SKYBOX_MIN_REALWORLD;
	static const glm::vec3 SKYBOX_MIN_VIRTUALWORLD;
	static const glm::vec3 SKYBOX_MAX;

	// movement
	static const float MOVEMENT_SPEED_WALK;
	static const float MOVEMENT_SPEED_RUN;

	static const float MOUSE_SENSITIVITY;

	static const bool  STAY_INSIDE_SKYBOX;
	static const float STAY_INSIDE_SKYBOX_BORDER;
	static const float STAY_INSIDE_SKYBOX_EPSILON; // the range for calculating movement along the wall; minimum distance to the skybox limits

	// player
	static const float CAMERA_FOV;
	static const float CAMERA_NEAR;
	static const float CAMERA_FAR;
	static const float CAMERA_HEIGHT;

	static const float     FLASHLIGHT_CUTOFF;
	static const glm::vec3 FLASHLIGHT_ATTENUATION;
	static const float     FLASHLIGHT_OFFSET; // height of the flashlight; relative to the camera position

	// environment
	static const size_t ENVIRONMENT_MENU_FIREBALLS;

	static const size_t ENVIRONMENT_TREES;
	static const size_t ENVIRONMENT_BUSHES;
	static const size_t ENVIRONMENT_FIREFLIES;

	static const size_t    ENVIRONMENT_WALLS_PER_SIDE; // max number of walls per side; total number of walls = 4 * cca(ENVIRONMENT_WALLS_PER_SIDE)
	static const glm::vec2 ENVIRONMENT_WALLS_RANGE;    // walls range; relative to the skybox limits

	static const float  ENVIRONMENT_FIREBALL_OFFSET;          // position of the fireball; relative to the camera position
	static const float  ENVIRONMENT_FIREBALL_MAX_POWER;       // max power of the fireball; affects the size, brightness, as well as the duration and length of the fireball throw
	static const size_t ENVIRONMENT_FIREBALL_PATH_COMPLEXITY; // complexity of the fireball path; affects the number of segments of the throw curve
};
