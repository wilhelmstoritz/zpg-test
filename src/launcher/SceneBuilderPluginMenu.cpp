#include "SceneBuilderPluginMenu.h"
#include "Config.h"
#include "Light.h"
#include "LightFlashlight.h"
#include "Model.h"
#include "ModelFireballBouncing.h"
#include "TransformationAnimationRotate.h"

#include "ModelLibrary.h"
#include "ModelLetters.h"
#include "sphere.h"

// --- public ------------------------------------------------------------------
void SceneBuilderPluginMenu::setSceneProperties(Scene* t_scene) {
    t_scene->setTitle("menu | " + t_scene->getTitle()
        + Config::WINDOW_TITLE_HELP_MENU);
}

// --- protected ---------------------------------------------------------------
void SceneBuilderPluginMenu::preProcess() {
    // scene size
    this->m_scene->setSize(
        Config::SKYBOX_MIN_VIRTUALWORLD,
        Config::SKYBOX_MAX);

    this->setEnvironment();
}

void SceneBuilderPluginMenu::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createShaderProgram("menu::shader:phong",        (this->m_shaderResourcesPath + "05/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/phong.frag.glsl"       ).c_str());
    this->m_shaderWarehouse->createShaderProgram("menu::shader:single_color", (this->m_shaderResourcesPath + "05/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/single-color.frag.glsl").c_str());
}

void SceneBuilderPluginMenu::createLights() {
    Light* light;

    // moonlight
    glm::vec3 moonlight = glm::vec3(.827f, .871f, 1.f); // pale moonlight
    moonlight *= 0.1f; // dimmed moonlight

    light = this->m_lightWarehouse->createLight("menu::center_light", Light::lightTypeE::POINT_LIGHT, glm::vec3(0.f, 0.f, 10.f));
    //light->setDirection(glm::vec3(0.f, -1.f, -1.f));
    //light->setSpotCutoffDegrees(30.f);
    //light->setDiffuseColor(moonlight);
	light->setDiffuseColor(glm::vec3(1.f, 1.f, 1.f)); // white
    light->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
    light->setAttenuation(glm::vec3(1.f, .01f, 0.001f));

    light = this->m_lightWarehouse->createLight("menu::menu_light1", Light::lightTypeE::SPOT_LIGHT, glm::vec3(-35.f, 20.f, 20.f));
    light->setDirection(glm::vec3(0.f, 0.f, -1.f));
    light->setSpotCutoffDegrees(160.f);
    //light->setDiffuseColor(moonlight);
	light->setDiffuseColor(glm::vec3(1.f, 0.f, 0.f)); // red
	//light->setDiffuseColor(glm::vec3(.9f, .9f, .9f)); // light gray
    light->setSpecularColor(glm::vec3(1.f, 0.f, 0.f));
    light->setAttenuation(glm::vec3(.8f, 0.f, 0.001f));

    light = this->m_lightWarehouse->createLight("menu::menu_light2", Light::lightTypeE::SPOT_LIGHT, glm::vec3(35.f, 20.f, 20.f));
    light->setDirection(glm::vec3(0.f, 0.f, -1.f));
    light->setSpotCutoffDegrees(160.f);
    //light->setDiffuseColor(moonlight);
	light->setDiffuseColor(glm::vec3(0.f, 1.f, 0.f)); // green
    //light->setDiffuseColor(glm::vec3(.9f, .9f, .9f)); // light gray
    light->setSpecularColor(glm::vec3(0.f, 1.f, 0.f));
    light->setAttenuation(glm::vec3(.8f, 0.f, 0.001f));

    light = this->m_lightWarehouse->createLight("menu::menu_light3", Light::lightTypeE::SPOT_LIGHT, glm::vec3(-35.f, -20.f, 20.f));
    light->setDirection(glm::vec3(0.f, 0.f, -1.f));
    light->setSpotCutoffDegrees(160.f);
    //light->setDiffuseColor(moonlight);
    light->setDiffuseColor(glm::vec3(0.f, 0.f, 1.f)); // blue
    //light->setDiffuseColor(glm::vec3(.9f, .9f, .9f)); // light gray
    light->setSpecularColor(glm::vec3(0.f, 0.f, 1.f));
    light->setAttenuation(glm::vec3(.8f, 0.f, 0.001f));

    light = this->m_lightWarehouse->createLight("menu::menu_light4", Light::lightTypeE::SPOT_LIGHT, glm::vec3(35.f, -20.f, 20.f));
    light->setDirection(glm::vec3(0.f, 0.f, -1.f));
    light->setSpotCutoffDegrees(160.f);
    //light->setDiffuseColor(moonlight);
	light->setDiffuseColor(glm::vec3(1.f, 1.f, 0.f)); // yellow
    //light->setDiffuseColor(glm::vec3(.9f, .9f, .9f)); // light gray
    light->setSpecularColor(glm::vec3(1.f, 1.f, 0.f));
    light->setAttenuation(glm::vec3(.8f, 0.f, 0.001f));
}

void SceneBuilderPluginMenu::createModels() {
    Light* light;
    Model* model;
    std::vector<GLsizei> numVerticesList;

    // skybox
    this->m_modelWarehouse->createModel(
        "menu::skybox",
        "menu::shader:phong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        glm::vec3(this->m_size.x, this->m_size.y, this->m_size.z),
        glm::vec3(0.f),
        glm::vec3(this->m_min.x, this->m_min.y, this->m_min.z));

    // menu choices
    ModelLetters* modelLetters = ModelLetters::getInstance();

    float size = .4f;
    float offsetX = -150.f;
    float offsetY =    0.f;
    glm::ivec2 letterOffset = { modelLetters->getFontSize().x - 7, 0 }; // getFontSize().x - 7 = real width of the letter
    
	this->m_modelWarehouse->createVertexResources("res:choice1",     modelLetters->getText("  1  basic geometries",             letterOffset), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL); int chsize1 = modelLetters->getLastTextSize();
    this->m_modelWarehouse->createVertexResources("res:choice2",     modelLetters->getText("  2  ZPG models:normals as colors", letterOffset), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL); int chsize2 = modelLetters->getLastTextSize();
    this->m_modelWarehouse->createVertexResources("res:choice3",     modelLetters->getText("  3  woods:normals as colors",      letterOffset), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL); int chsize3 = modelLetters->getLastTextSize();
    this->m_modelWarehouse->createVertexResources("res:choice4",     modelLetters->getText("  4  illuminated spheres",          letterOffset), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL); int chsize4 = modelLetters->getLastTextSize();
    this->m_modelWarehouse->createVertexResources("res:choice5",     modelLetters->getText("  5  magic woods",                  letterOffset), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL); int chsize5 = modelLetters->getLastTextSize();
    this->m_modelWarehouse->createVertexResources("res:choice6",     modelLetters->getText("  6  skycube & skydome",            letterOffset), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL); int chsize6 = modelLetters->getLastTextSize();
    this->m_modelWarehouse->createVertexResources("res:choice7",     modelLetters->getText("  7  magic woods:textures",         letterOffset), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL); int chsize7 = modelLetters->getLastTextSize();
    this->m_modelWarehouse->createVertexResources("res:choice8",     modelLetters->getText("  8  magic woods:obj models",       letterOffset), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL); int chsize8 = modelLetters->getLastTextSize();
    this->m_modelWarehouse->createVertexResources("res:choice9",     modelLetters->getText("  9  dark magic woods:fireballs",   letterOffset), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL); int chsize9 = modelLetters->getLastTextSize();
    this->m_modelWarehouse->createVertexResources("res:choice_exit", modelLetters->getText("ESC  exit",                         letterOffset), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL); int chsize_exit = modelLetters->getLastTextSize();

    this->m_modelWarehouse->createModel("menu::choice1",     "menu::shader:phong", "res:choice1",     0, chsize1,     glm::vec3(size, size, size * 3), glm::vec3(0.f), glm::vec3(size * offsetX, size * (offsetY + modelLetters->getFontSize().y * 4), 0.f));
	this->m_modelWarehouse->createModel("menu::choice2",     "menu::shader:phong", "res:choice2",     0, chsize2,     glm::vec3(size, size, size * 3), glm::vec3(0.f), glm::vec3(size * offsetX, size * (offsetY + modelLetters->getFontSize().y * 3), 0.f));
    this->m_modelWarehouse->createModel("menu::choice3",     "menu::shader:phong", "res:choice3",     0, chsize3,     glm::vec3(size, size, size * 3), glm::vec3(0.f), glm::vec3(size * offsetX, size * (offsetY + modelLetters->getFontSize().y * 2), 0.f));
    this->m_modelWarehouse->createModel("menu::choice4",     "menu::shader:phong", "res:choice4",     0, chsize4,     glm::vec3(size, size, size * 3), glm::vec3(0.f), glm::vec3(size * offsetX, size * (offsetY + modelLetters->getFontSize().y),     0.f));
    this->m_modelWarehouse->createModel("menu::choice5",     "menu::shader:phong", "res:choice5",     0, chsize5,     glm::vec3(size, size, size * 3), glm::vec3(0.f), glm::vec3(size * offsetX, size * (offsetY),                                     0.f));
    this->m_modelWarehouse->createModel("menu::choice6",     "menu::shader:phong", "res:choice6",     0, chsize6,     glm::vec3(size, size, size * 3), glm::vec3(0.f), glm::vec3(size * offsetX, size * (offsetY - modelLetters->getFontSize().y),     0.f));
    this->m_modelWarehouse->createModel("menu::choice7",     "menu::shader:phong", "res:choice7",     0, chsize7,     glm::vec3(size, size, size * 3), glm::vec3(0.f), glm::vec3(size * offsetX, size * (offsetY - modelLetters->getFontSize().y * 2), 0.f));
    this->m_modelWarehouse->createModel("menu::choice8",     "menu::shader:phong", "res:choice8",     0, chsize8,     glm::vec3(size, size, size * 3), glm::vec3(0.f), glm::vec3(size * offsetX, size * (offsetY - modelLetters->getFontSize().y * 3), 0.f));
    this->m_modelWarehouse->createModel("menu::choice9",     "menu::shader:phong", "res:choice9",     0, chsize9,     glm::vec3(size, size, size * 3), glm::vec3(0.f), glm::vec3(size * offsetX, size * (offsetY - modelLetters->getFontSize().y * 4), 0.f));
    this->m_modelWarehouse->createModel("menu::choice_exit", "menu::shader:phong", "res:choice_exit", 0, chsize_exit, glm::vec3(size, size, size * 3), glm::vec3(0.f), glm::vec3(size * offsetX, size * (offsetY - modelLetters->getFontSize().y * 5), 0.f));

    // menu label
	//numVerticesList = this->m_modelWarehouse->createBufferResources("res:menu_label", (this->m_modelResourcesPath + "my/menu-label.obj"         ).c_str()); // normal text
	numVerticesList = this->m_modelWarehouse->createBufferResources("res:menu_label", (this->m_modelResourcesPath + "my/menu-label-inflated.obj").c_str()); // inflated text

    model = this->m_modelWarehouse->createModel(
        "menu::label",
        "menu::shader:phong", "res:menu_label0", 0, numVerticesList[0],
        glm::vec3(22.f), glm::vec3(0.f), glm::vec3(this->m_center.x, 33.f, this->m_center.z));
    model->getTransformation()->updateRotateStep(
        //std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.01f, .05f, 0.01f))); // all axis rotation
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, .05f, 0.f))); // y axis rotation

    // fireballs
    this->m_modelWarehouse->createVertexResources("res:sphere", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    for (size_t i = 0; i < Config::ENVIRONMENT_MENU_FIREBALLS; ++i) {
        // --- fireball model
        auto modelFB = this->m_modelWarehouse->createModel<ModelFireballBouncing>(
            "menu::fireball" + std::to_string(i),
            "menu::shader:single_color", "res:sphere", 0, 2880,
            glm::vec3(Config::ENVIRONMENT_FIREBALL_MAX_POWER * 3.f)); // 3 times bigger; power = size; the default diameter of the sphere is 2 units
		modelFB->setState(ModelFireball::fireballStateE::STATE_THROWN_CONTINUOUS, static_cast<ModelFireball::fireballTypeE>(i % 4));

        // --- fireball light source
        light = this->m_lightWarehouse->createLight(
            "menu::fireball_light" + std::to_string(i),
            Light::lightTypeE::POINT_LIGHT); // no need to set position; it will follow the model
        //light->setDiffuseColor(glm::vec3(0.f));  // no light emission; will be set when the fireball is thrown
        //light->setSpecularColor(glm::vec3(0.f)); // no light emission; will be set when the fireball is thrown
        //light->setAttenuation(glm::vec3(1.f, 0.f, 0.f)); // no attenuation

        modelFB->addObserver(light); // light source now follows the model
    }
}

void SceneBuilderPluginMenu::postProcess() {
    // camera position & flashlight
    this->m_scene->getCamera()->setPosition(
        glm::vec3(this->m_center.x, this->m_center.y, this->m_max.z - 1.f),
        glm::vec3(0.f, 0.f, -1.f));

    Light* light = this->m_lightWarehouse->createFlashlight("menu::flashlight", this->m_scene->getCamera());
	light->setAttenuation(glm::vec3(1.f, 0.f, 0.f)); // no attenuation
}

void SceneBuilderPluginMenu::addContextToScene() {
    // add lights to the scene
	//this->m_scene->addLight("center_light", this->m_lightWarehouse->getLight("menu::center_light"));
	//this->m_scene->addLight("menu_light1",  this->m_lightWarehouse->getLight("menu::menu_light1"));
	//this->m_scene->addLight("menu_light2",  this->m_lightWarehouse->getLight("menu::menu_light2"));
	//this->m_scene->addLight("menu_light3",  this->m_lightWarehouse->getLight("menu::menu_light3"));
	//this->m_scene->addLight("menu_light4",  this->m_lightWarehouse->getLight("menu::menu_light4"));

    this->m_scene->addLight("flashlight",   this->m_lightWarehouse->getLight("menu::flashlight"));

    // add models to the scene
    //this->m_scene->addModel("skybox",      this->m_modelWarehouse->getModel("menu::skybox"));

	this->m_scene->addModel("choice1",     this->m_modelWarehouse->getModel("menu::choice1"));
	this->m_scene->addModel("choice2",     this->m_modelWarehouse->getModel("menu::choice2"));
	this->m_scene->addModel("choice3",     this->m_modelWarehouse->getModel("menu::choice3"));
    this->m_scene->addModel("choice4",     this->m_modelWarehouse->getModel("menu::choice4"));
    this->m_scene->addModel("choice5",     this->m_modelWarehouse->getModel("menu::choice5"));
    this->m_scene->addModel("choice6",     this->m_modelWarehouse->getModel("menu::choice6"));
    this->m_scene->addModel("choice7",     this->m_modelWarehouse->getModel("menu::choice7"));
    this->m_scene->addModel("choice8",     this->m_modelWarehouse->getModel("menu::choice8"));
    this->m_scene->addModel("choice9",     this->m_modelWarehouse->getModel("menu::choice9"));
    this->m_scene->addModel("choice_exit", this->m_modelWarehouse->getModel("menu::choice_exit"));

    this->m_scene->addModel("menu_label",  this->m_modelWarehouse->getModel("menu::label"));

    for (size_t i = 0; i < Config::ENVIRONMENT_MENU_FIREBALLS; ++i) {
        this->m_scene->addModel("fireball"       + std::to_string(i), this->m_modelWarehouse->getModel("menu::fireball"       + std::to_string(i)));
        this->m_scene->addLight("fireball_light" + std::to_string(i), this->m_lightWarehouse->getLight("menu::fireball_light" + std::to_string(i)));
    }
}
