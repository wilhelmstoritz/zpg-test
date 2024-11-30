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

	// movement; speed (in units per second)
	static const float MOVEMENT_SPEED_WALK;
	static const float MOVEMENT_SPEED_RUN;

	static const float MOUSE_SENSITIVITY;

	static const bool STAY_INSIDE_SKYBOX;
	static const float STAY_INSIDE_SKYBOX_BORDER;
	static const float STAY_INSIDE_SKYBOX_EPSILON; // the range for calculating movement along the wall; minimum distance to the skybox limits
};
