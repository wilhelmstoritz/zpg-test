#include "Config.h"

// math
const size_t Config::MATH_NUM_BEZIER_SAMPLES = 100;

// system
const std::string Config::SYSTEM_RESOURCES_PATH = "../resources/";
const std::string Config::SYSTEM_RESOURCES_RELPATH_SHADERS  = "shaders.glsl/";
const std::string Config::SYSTEM_RESOURCES_RELPATH_MODELS   = "models.obj/";
const std::string Config::SYSTEM_RESOURCES_RELPATH_TEXTURES = "textures/";
const std::string Config::SYSTEM_RESOURCES_RELPATH_FONTS    = "fonts/";

const std::string Config::SYSTEM_SPLASH_IMAGE = "splash/splash1.png";
const bool        Config::SYSTEM_SPLASH_RANDOM       = true; // if false, the splash image is shown; if true, a random splash image is shown (must differ by number)
const size_t      Config::SYSTEM_SPLASH_RANDOM_COUNT = 4;
const bool        Config::SYSTEM_SPLASH_SHOW         = true;

const std::string Config::SYSTEM_BITMAP_FONT      = "bm437-IBM_EGA-9x14.bin";
const glm::uvec2  Config::SYSTEM_BITMAP_FONT_SIZE = glm::uvec2(16, 14); // (x, y) pixels; x has to be a (corresponding) multiple of 8; y stays the same

const std::string Config::SYSTEM_MENU = "menu";

const bool Config::SYSTEM_XTRA_RENDER_PROCESSING = false;

// window
const glm::uvec2 Config::WINDOW_SIZE = glm::uvec2(800, 600); // (width, height) pixels
const bool       Config::WINDOW_FULLSCREEN = false;

const std::string Config::WINDOW_TITLE = "ZPG project";
const std::string Config::WINDOW_TITLE_HELP            = " | ESC exit : X fullscreen";
const std::string Config::WINDOW_TITLE_HELP_MOVE       = " : SHIFT+CURSOR run/walk";
const std::string Config::WINDOW_TITLE_HELP_FLASHLIGHT = " : F flashlight";
const std::string Config::WINDOW_TITLE_HELP_FIREBALL   = " : 1-4 fireball 0 off";
const std::string Config::WINDOW_TITLE_HELP_MENU       = " : 1-9 scene";
const float Config::WINDOW_TITLE_UPDATE_INTERVAL = 1.f; // seconds

// skybox
const float Config::SKYBOX_XMIN = -100.f;
const float Config::SKYBOX_XMAX =  100.f;
const float Config::SKYBOX_YMIN_REALWORLDSCENE    =    0.f;
const float Config::SKYBOX_YMIN_VIRTUALWORLDSCENE = -100.f;
const float Config::SKYBOX_YMAX =  100.f;
const float Config::SKYBOX_ZMIN = -100.f;
const float Config::SKYBOX_ZMAX =  100.f;
const glm::vec3 Config::SKYBOX_MIN_REALWORLD    = glm::vec3(-100.f,    0.f, -100.f); // upper half of the cube; xz plane (x, 0, z)
const glm::vec3 Config::SKYBOX_MIN_VIRTUALWORLD = glm::vec3(-100.f, -100.f, -100.f); // cube; symmetric to the (0, 0, 0)
const glm::vec3 Config::SKYBOX_MAX              = glm::vec3( 100.f,  100.f,  100.f);

// movement
const float Config::MOVEMENT_SPEED_WALK =  3.f; // units per second
const float Config::MOVEMENT_SPEED_RUN  = 30.f;

const float Config::MOUSE_SENSITIVITY = .1f;

const bool  Config::STAY_INSIDE_SKYBOX = true;
const float Config::STAY_INSIDE_SKYBOX_BORDER  = 1.f;
const float Config::STAY_INSIDE_SKYBOX_EPSILON =  .1f;

// player
const float Config::CAMERA_FOV = 60.f; // degrees
const float Config::CAMERA_NEAR =   0.1f;
const float Config::CAMERA_FAR  = 300.f;
const float Config::CAMERA_HEIGHT = 1.8f;

const float     Config::FLASHLIGHT_CUTOFF = 15.f; // degrees
const glm::vec3 Config::FLASHLIGHT_ATTENUATION = glm::vec3(1.f, .09f, .032f); // constant, linear, quadratic
const float     Config::FLASHLIGHT_OFFSET = -1.f;

// environment
const size_t Config::ENVIRONMENT_TREES     = 333;
const size_t Config::ENVIRONMENT_BUSHES    = 666;
const size_t Config::ENVIRONMENT_FIREFLIES = 111;
//const size_t Config::ENVIRONMENT_TREES     = 1;
//const size_t Config::ENVIRONMENT_BUSHES    = 1;
//const size_t Config::ENVIRONMENT_FIREFLIES = 1;

const size_t    Config::ENVIRONMENT_WALLS_PER_SIDE = 42; // the answer to the ultimate question of life, the universe, and everything
const glm::vec2 Config::ENVIRONMENT_WALLS_RANGE = glm::vec2(.63f, .68f); // (min/100%, max/100%) of (half) the size of the skybox

const float Config::ENVIRONMENT_FIREBALL_OFFSET    = 2.f;
const float Config::ENVIRONMENT_FIREBALL_MAX_POWER = 1.f;
