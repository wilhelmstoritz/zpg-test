#include "Config.h"

// --- public ------------------------------------------------------------------
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

// player
const float Config::PLAYER_HEIGHT = 2.f;
const float Config::PLAYER_FLASHLIGHT_HEIGHT = 1.f;

// environment
const unsigned int Config::ENVIRONMENT_TREES = 300;
const unsigned int Config::ENVIRONMENT_BUSHES = 300;
//const unsigned int Config::ENVIRONMENT_FIREFLIES = 200;
const unsigned int Config::ENVIRONMENT_FIREFLIES = 100;

// movement speed (in units per second)
const float Config::MOVEMENT_SPEED_WALK = 3.f;
const float Config::MOVEMENT_SPEED_RUN = 30.f;

const float Config::MOUSE_SENSITIVITY = .1f;
