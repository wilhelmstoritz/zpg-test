#include "Config.h"

// window
const unsigned int Config::WINDOW_WIDTH = 800;
const unsigned int Config::WINDOW_HEIGHT = 600;
const bool Config::WINDOW_FULLSCREEN = false;

const std::string Config::WINDOW_TITLE = "ZPG projekt";
const float Config::WINDOW_TITLE_UPDATE_INTERVAL = .5f; // seconds

// skybox
const float Config::SKYBOX_XMIN = -100.f;
const float Config::SKYBOX_XMAX = 100.f;
const float Config::SKYBOX_YMIN = 0.f;
const float Config::SKYBOX_YMAX = 100.f;
const float Config::SKYBOX_ZMIN = -100.f;
const float Config::SKYBOX_ZMAX = 100.f;

const float Config::SKYBOX_XSIZE = Config::SKYBOX_XMAX - Config::SKYBOX_XMIN;
const float Config::SKYBOX_YSIZE = Config::SKYBOX_YMAX - Config::SKYBOX_YMIN;
const float Config::SKYBOX_ZSIZE = Config::SKYBOX_ZMAX - Config::SKYBOX_ZMIN;

const float Config::SKYBOX_XCENTER = (Config::SKYBOX_XMIN + Config::SKYBOX_XMAX) / 2.f;
const float Config::SKYBOX_YCENTER = (Config::SKYBOX_YMIN + Config::SKYBOX_YMAX) / 2.f;
const float Config::SKYBOX_ZCENTER = (Config::SKYBOX_ZMIN + Config::SKYBOX_ZMAX) / 2.f;

// movement; speed (in units per second)
const float Config::MOVEMENT_SPEED_WALK = 3.f;
const float Config::MOVEMENT_SPEED_RUN = 30.f;

const float Config::MOUSE_SENSITIVITY = .1f;

const bool Config::STAY_INSIDE_SKYBOX = true;
const float Config::STAY_INSIDE_SKYBOX_BORDER = 1.f;
const float Config::STAY_INSIDE_SKYBOX_EPSILON = .1f;

// player
const float Config::CAMERA_FOV = 60.f; // degrees
const float Config::CAMERA_NEAR = 0.1f;
const float Config::CAMERA_FAR = 300.f;
const float Config::CAMERA_HEIGHT = 1.8f;

const float Config::FLASHLIGHT_CUTOFF = 15.f; // degrees
const float Config::FLASHLIGHT_ATTENUATION_CONSTANT = 1.f;
const float Config::FLASHLIGHT_ATTENUATION_LINEAR = .09f;
const float Config::FLASHLIGHT_ATTENUATION_QUADRATIC = .032f;
const float Config::FLASHLIGHT_HEIGHT = 1.f;

// environment
const unsigned int Config::ENVIRONMENT_TREES = 333;
const unsigned int Config::ENVIRONMENT_BUSHES = 666;
const unsigned int Config::ENVIRONMENT_FIREFLIES = 111;
//const unsigned int Config::ENVIRONMENT_TREES = 1;
//const unsigned int Config::ENVIRONMENT_BUSHES = 1;
//const unsigned int Config::ENVIRONMENT_FIREFLIES = 1;
