#include "Config.h"

// system
const std::string Config::SYSTEM_RESOURCES_PATH = "../resources/";
const std::string Config::SYSTEM_RESOURCES_RELPATH_SHADERS  = "shaders.glsl/";
const std::string Config::SYSTEM_RESOURCES_RELPATH_MODELS   = "models.obj/";
const std::string Config::SYSTEM_RESOURCES_RELPATH_TEXTURES = "textures/";
const std::string Config::SYSTEM_RESOURCES_RELPATH_FONTS    = "fonts/";

const std::string Config::SYSTEM_BITMAP_FONT      = "bm437-IBM_EGA-9x14.bin";
const glm::uvec2  Config::SYSTEM_BITMAP_FONT_SIZE = glm::uvec2(16, 14); // (x, y) pixels; x has to be a (corresponding) multiple of 8; y stays the same

const std::string Config::SYSTEM_MENU = "menu";

bool const Config::SYSTEM_XTRA_RENDER_PROCESSING = false;

// window
const unsigned int Config::WINDOW_WIDTH  = 800;
const unsigned int Config::WINDOW_HEIGHT = 600;
const bool Config::WINDOW_FULLSCREEN = false;

const std::string Config::WINDOW_TITLE = "ZPG project | X fullscreen : F flashlight on/off";
const float Config::WINDOW_TITLE_UPDATE_INTERVAL = .5f; // seconds

// skybox
const float Config::SKYBOX_XMIN = -100.f;
const float Config::SKYBOX_XMAX =  100.f;
const float Config::SKYBOX_YMIN_REALWORLDSCENE    =    0.f;
const float Config::SKYBOX_YMIN_VIRTUALWORLDSCENE = -100.f;
const float Config::SKYBOX_YMAX =  100.f;
const float Config::SKYBOX_ZMIN = -100.f;
const float Config::SKYBOX_ZMAX =  100.f;

// movement; speed (in units per second)
const float Config::MOVEMENT_SPEED_WALK =  3.f;
const float Config::MOVEMENT_SPEED_RUN  = 30.f;

const float Config::MOUSE_SENSITIVITY = .1f;

const bool Config::STAY_INSIDE_SKYBOX = true;
const float Config::STAY_INSIDE_SKYBOX_BORDER  = 1.f;
const float Config::STAY_INSIDE_SKYBOX_EPSILON =  .1f;

// player
const float Config::CAMERA_FOV = 60.f; // degrees
const float Config::CAMERA_NEAR =   0.1f;
const float Config::CAMERA_FAR  = 300.f;
const float Config::CAMERA_HEIGHT = 1.8f;

const float Config::FLASHLIGHT_CUTOFF = 15.f; // degrees
const float Config::FLASHLIGHT_ATTENUATION_CONSTANT  = 1.f;
const float Config::FLASHLIGHT_ATTENUATION_LINEAR    =  .09f;
const float Config::FLASHLIGHT_ATTENUATION_QUADRATIC =  .032f;
const float Config::FLASHLIGHT_HEIGHT = 1.f;

// environment
const unsigned int Config::ENVIRONMENT_TREES     = 333;
const unsigned int Config::ENVIRONMENT_BUSHES    = 666;
const unsigned int Config::ENVIRONMENT_FIREFLIES = 111;
//const unsigned int Config::ENVIRONMENT_TREES     = 1;
//const unsigned int Config::ENVIRONMENT_BUSHES    = 1;
//const unsigned int Config::ENVIRONMENT_FIREFLIES = 1;
