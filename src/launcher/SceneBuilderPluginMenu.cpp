#include "SceneBuilderPluginMenu.h"
//#include "AppUtils.h"
#include "Config.h"
#include "Light.h"
#include "LightFlashlight.h"
//#include "ModelFirefly.h"
//#include "TransformationAnimationRandomMove.h"
#include "TransformationAnimationRotate.h"

#include "ModelLibrary.h"
#include "ModelLetters.h"

// --- protected ---------------------------------------------------------------
void SceneBuilderPluginMenu::preProcess() {
    // scene size
    this->m_scene->setSize(
        glm::vec3(Config::SKYBOX_XMIN, Config::SKYBOX_YMIN_VIRTUALWORLDSCENE, Config::SKYBOX_ZMIN),
        glm::vec3(Config::SKYBOX_XMAX, Config::SKYBOX_YMAX, Config::SKYBOX_ZMAX));

    this->setEnvironment();
}

void SceneBuilderPluginMenu::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createShaderProgram("menu::shader:texture", (this->m_shaderResourcesPath + "05/texture.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/texture.frag.glsl").c_str());

    this->m_shaderWarehouse->createShaderProgram("menu::shader:phong",         (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/phong.frag.glsl"        ).c_str());
    this->m_shaderWarehouse->createShaderProgram("menu::shader:phong_texture", (this->m_shaderResourcesPath + "05/normals-texture.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/phong-texture.frag.glsl").c_str());
    this->m_shaderWarehouse->createShaderProgram("menu::shader:single_color",  (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/single-color.frag.glsl" ).c_str());
}

void SceneBuilderPluginMenu::createLights() {
    Light* light;

    // moonlight
    glm::vec3 moonlight = glm::vec3(.827f, .871f, 1.f); // pale moonlight
    moonlight *= 0.001f; // dimmed moonlight

    light = this->m_lightWarehouse->createLight("menu::moonlight", Light::LightTypeE::DIRECTIONAL, glm::vec3(0.f, 90.f, 0.f));
    light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    //light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(moonlight);
    light->setSpecularColor(moonlight);

    light = this->m_lightWarehouse->createLight("menu::center_light", Light::LightTypeE::POINT, glm::vec3(0.f, 0.f, 0.f));
    //light->setDirection(glm::vec3(0.f, -1.f, -1.f));
    //light->setSpotCutoffDegrees(30.f);
    //light->setDiffuseColor(moonlight);
    light->setDiffuseColor(glm::vec3(1.f, 1.f, 1.f));
    light->setSpecularColor(moonlight);
    light->setAttenuation(glm::vec3(1.f, .01f, 0.f));

    light = this->m_lightWarehouse->createLight("menu::menu_light", Light::LightTypeE::SPOT, glm::vec3(0.f, 90.f, 90.f));
    light->setDirection(glm::vec3(0.f, -1.f, -1.f));
    light->setSpotCutoffDegrees(30.f);
    //light->setDiffuseColor(moonlight);
    light->setDiffuseColor(glm::vec3(0.f, .3f, 0.f));
    light->setSpecularColor(moonlight);
    light->setAttenuation(glm::vec3(.1f, .01f, .001f));
}

void SceneBuilderPluginMenu::createModels() {
    Model* model;
    std::vector<GLsizei> numVerticesList;

    // skybox
    this->m_modelWarehouse->createModel(
        "menu::skybox",
        //"menu::shader:lambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        "menu::shader:phong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        glm::vec3(this->m_size.x, this->m_size.y, this->m_size.z),
        glm::vec3(0.f),
        glm::vec3(this->m_min.x, this->m_min.y, this->m_min.z));

    // menu
	ModelLetters* modelLetters = ModelLetters::getInstance();
    this->m_modelWarehouse->createVertexResources("res:letter_xxx0", modelLetters->getLetter('Q'), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_xxx1", modelLetters->getLetter('W'), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_xxx2", modelLetters->getLetter('X'), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    float size = 1.f;
    float offsetX = 0.f;
    float offsetY = 0.f;
    this->m_modelWarehouse->createModel("menu::letter_xxx0", "menu::shader:phong", "res:letter_xxx0", 0, modelLetters->getLetterSize('Q'), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX),                                     size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("menu::letter_xxx1", "menu::shader:phong", "res:letter_xxx1", 0, modelLetters->getLetterSize('W'), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + modelLetters->getFontSize().x),     size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("menu::letter_xxx2", "menu::shader:phong", "res:letter_xxx2", 0, modelLetters->getLetterSize('X'), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + modelLetters->getFontSize().x * 2), size * offsetY, 0.f));

    // login
    numVerticesList = this->m_modelWarehouse->createVertexResources("res:login", (this->m_modelResourcesPath + "login.my.obj").c_str());

    model = this->m_modelWarehouse->createModel(
        "menu::login",
        "menu::shader:phong_texture", "res:login0", 0, numVerticesList[0],
        glm::vec3(10.f), glm::vec3(0.f), glm::vec3(this->m_center.x, 50.f, this->m_center.z));
    model->setTextureID(4); // texture unit 4; wooden fence

    model->getTransformation()->updateRotateStep(
        //std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.01f, .05f, 0.01f))); // all axis rotation
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, .05f, 0.f))); // y axis rotation
}

void SceneBuilderPluginMenu::loadTextures() {
    //this->m_textureWarehouse->loadTexture("tex:grass", (this->m_textureResourcesPath + "grass.png").c_str(), GL_TEXTURE0);
    //this->m_textureWarehouse->loadTexture("tex:wood", (this->m_textureResourcesPath + "test.png").c_str(), GL_TEXTURE1);
    //this->m_textureWarehouse->loadTexture("tex:house", (this->m_textureResourcesPath + "house.png").c_str(), GL_TEXTURE2);
    //this->m_textureWarehouse->loadTexture("tex:zombie", (this->m_textureResourcesPath + "zombie.png").c_str(), GL_TEXTURE3);
    this->m_textureWarehouse->loadTexture("tex:wooden_fence", (this->m_textureResourcesPath + "wooden_fence.png").c_str(), GL_TEXTURE4);
}

void SceneBuilderPluginMenu::postProcess() {
    // camera position & flashlight
    this->m_scene->getCamera()->setPosition(
        glm::vec3(this->m_center.x, this->m_center.y, this->m_max.z - 1.f),
        glm::vec3(0.f, 0.f, -1.f));

    this->m_lightWarehouse->createFlashlight("menu::flashlight", this->m_scene->getCamera());
}

void SceneBuilderPluginMenu::addContextToScene() {
    // add lights to the scene
    this->m_scene->addLight("moonlight",    this->m_lightWarehouse->getLight("menu::moonlight"));
	this->m_scene->addLight("center_light", this->m_lightWarehouse->getLight("menu::center_light"));
	this->m_scene->addLight("menu_light",   this->m_lightWarehouse->getLight("menu::menu_light"));

    this->m_scene->addLight("flashlight",   this->m_lightWarehouse->getLight("menu::flashlight"));

    // add models to the scene
    this->m_scene->addModel("skybox", this->m_modelWarehouse->getModel("menu::skybox"));

	this->m_scene->addModel("letter_xxx0", this->m_modelWarehouse->getModel("menu::letter_xxx0"));
	this->m_scene->addModel("letter_xxx1", this->m_modelWarehouse->getModel("menu::letter_xxx1"));
	this->m_scene->addModel("letter_xxx2", this->m_modelWarehouse->getModel("menu::letter_xxx2"));

    this->m_scene->addModel("login", this->m_modelWarehouse->getModel("menu::login"));
}
