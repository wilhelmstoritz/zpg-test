#pragma once

class Config {
public:
	// skybox
	static const float SKYBOX_XMIN;
	static const float SKYBOX_XMAX;
	static const float SKYBOX_YMIN;
	static const float SKYBOX_YMAX;
	static const float SKYBOX_ZMIN;
	static const float SKYBOX_ZMAX;

	static const float SKYBOX_XSIZE;
	static const float SKYBOX_YSIZE;
	static const float SKYBOX_ZSIZE;

	static const float SKYBOX_XCENTER;
	static const float SKYBOX_YCENTER;
	static const float SKYBOX_ZCENTER;

	// player
	static const float PLAYER_HEIGHT;

	static const float FLASHLIGHT_HEIGHT;
	static const float FLASHLIGHT_CUTOFF;
	static const float FLASHLIGHT_ATTENUATION_CONSTANT;
	static const float FLASHLIGHT_ATTENUATION_LINEAR;
	static const float FLASHLIGHT_ATTENUATION_QUADRATIC;

	// environment
	static const unsigned int ENVIRONMENT_TREES;
	static const unsigned int ENVIRONMENT_BUSHES;
	static const unsigned int ENVIRONMENT_FIREFLIES;

	// movement; speed (in units per second)
	static const bool STAY_INSIDE_SKYBOX;

	static const float MOVEMENT_SPEED_WALK;
	static const float MOVEMENT_SPEED_RUN;

	static const float MOUSE_SENSITIVITY;
};
