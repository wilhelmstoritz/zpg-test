#include "SceneBuilderPlugin05a.h"
#include "AppUtils.h"
#include "Config.h"
#include "Light.h"
#include "LightFlashlight.h"
#include "ModelFirefly.h"
#include "TransformationAnimationRandomMove.h"
#include "TransformationAnimationRotate.h"

#include "ModelLibrary.h"
#include "tree.h"
#include "bushes.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "gift.h"

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin05a::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createShaderProgram("shader:texture", (this->m_shaderResourcesPath + "05/texture.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/texture.frag.glsl").c_str());

    this->m_shaderWarehouse->createShaderProgram("shader:phong",         (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/phong.frag.glsl"        ).c_str());
    this->m_shaderWarehouse->createShaderProgram("shader:phong_texture", (this->m_shaderResourcesPath + "05/normals-texture.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/phong-texture.frag.glsl").c_str());
    this->m_shaderWarehouse->createShaderProgram("shader:single_color",  (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/single-color.frag.glsl" ).c_str());
}

void SceneBuilderPlugin05a::createLights() {
    Light* light;

    // moonlight
    glm::vec3 moonlight = glm::vec3(.827f, .871f, 1.f); // pale moonlight
    moonlight *= 0.01f; // dimmed moonlight

    light = this->m_lightWarehouse->createLight("04::moonlight", Light::LightTypeE::DIRECTIONAL, glm::vec3(0.f, 90.f, 0.f));
    light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    //light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(moonlight);
    light->setSpecularColor(moonlight);

    light = this->m_lightWarehouse->createLight("04::default_light", Light::LightTypeE::SPOT, glm::vec3(0.f, 90.f, 90.f));
    light->setDirection(glm::vec3(0.f, -1.f, -1.f));
    light->setSpotCutoffDegrees(30.f);
    //light->setDiffuseColor(moonlight);
    light->setDiffuseColor(glm::vec3(0.f, .3f, 0.f));
    light->setSpecularColor(moonlight);
    light->setAttenuation(glm::vec3(.1f, .01f, .001f));

    // gift spotlight
    light = this->m_lightWarehouse->createLight("04::light01", Light::LightTypeE::SPOT, glm::vec3(-50.f, 10.f, -50.f));
    light->setDirection(glm::vec3(-2.f, -1.f, -2.f));
    light->setSpotCutoffDegrees(30.f);
    light->setDiffuseColor(glm::vec3(1.f, 0.5f, 1.f));
    light->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
    light->setAttenuation(glm::vec3(1.f, .01f, .001f));
}

void SceneBuilderPlugin05a::createModels() {
	Model* model;

    // skybox
    this->m_modelWarehouse->createModel(
        "04::skybox",
        //"shader:lambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        "shader:phong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        glm::vec3(Config::SKYBOX_XSIZE, Config::SKYBOX_YSIZE, Config::SKYBOX_ZSIZE),
        glm::vec3(0.f),
        glm::vec3(Config::SKYBOX_XMIN, Config::SKYBOX_YMIN, Config::SKYBOX_ZMIN));

    // cubes
	this->m_modelWarehouse->createVertexResources("res:cube", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    
    model = this->m_modelWarehouse->createModel("04::cube01", "shader:texture", "res:cube", 0, 36, glm::vec3(3.f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER - 10.f, Config::SKYBOX_YMIN + 20.f, Config::SKYBOX_ZCENTER));
	model->setTextureID(0); // texture unit 0; grass

    model = this->m_modelWarehouse->createModel("04::cube02", "shader:texture", "res:cube", 0, 36, glm::vec3(3.f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER + 10.f, Config::SKYBOX_YMIN + 20.f, Config::SKYBOX_ZCENTER));
	model->setTextureID(1); // texture unit 1; wood

    // trees
    this->m_modelWarehouse->createVertexResources("res:tree", sizeof(tree), tree, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    for (uint32_t i = 0; i < Config::ENVIRONMENT_TREES; ++i) {
        // random scale; between 0.5 and 1.5
        float rnd = AppUtils::getInstance()->randomNumber(.5f, 1.5f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = AppUtils::getInstance()->randomNumber(0.f, 360.f);
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        float x = AppUtils::getInstance()->randomNumber(Config::SKYBOX_XMIN + Config::SKYBOX_XSIZE / 4.f, Config::SKYBOX_XMAX - Config::SKYBOX_XSIZE / 4.f);
        float z = AppUtils::getInstance()->randomNumber(Config::SKYBOX_ZMIN + Config::SKYBOX_ZSIZE / 4.f, Config::SKYBOX_ZMAX - Config::SKYBOX_ZSIZE / 4.f);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        model = this->m_modelWarehouse->createModel(
            "04::tree" + std::to_string(i),
            "shader:phong", "res:tree", 0, 92814,
            scale, rotation, position);
    }

    // bushes
    this->m_modelWarehouse->createVertexResources("res:bushes", sizeof(bushes), bushes, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    for (uint32_t i = 0; i < Config::ENVIRONMENT_BUSHES; ++i) {
        // random scale; between 0.5 and 1.5
        float rnd = AppUtils::getInstance()->randomNumber(.5f, 1.5f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = AppUtils::getInstance()->randomNumber(0.f, 360.f);
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        //float x = AppUtils::getInstance()->randomNumber(Config::SKYBOX_XMIN, Config::SKYBOX_XMAX);
        //float z = AppUtils::getInstance()->randomNumber(Config::SKYBOX_ZMIN, Config::SKYBOX_ZMAX);
        float x = AppUtils::getInstance()->randomNumber(Config::SKYBOX_XMIN + Config::SKYBOX_XSIZE / 4.f, Config::SKYBOX_XMAX - Config::SKYBOX_XSIZE / 4.f);
        float z = AppUtils::getInstance()->randomNumber(Config::SKYBOX_ZMIN + Config::SKYBOX_ZSIZE / 4.f, Config::SKYBOX_ZMAX - Config::SKYBOX_ZSIZE / 4.f);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        model = this->m_modelWarehouse->createModel(
            "04::bushes" + std::to_string(i),
            "shader:phong", "res:bushes", 0, 8730,
            scale, rotation, position);
    }

    // fireflies
    this->m_modelWarehouse->createVertexResources("res:sphere", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    for (uint32_t i = 0; i < Config::ENVIRONMENT_FIREFLIES; ++i) {
        // --- firefly model
        // random scale; between 0.01 and 0.03
        float rnd = AppUtils::getInstance()->randomNumber(.01f, .03f);
        glm::vec3 scale = glm::vec3(rnd);

        // random position in the area
        float x = AppUtils::getInstance()->randomNumber(Config::SKYBOX_XMIN + Config::SKYBOX_XSIZE / 4.f, Config::SKYBOX_XMAX - Config::SKYBOX_XSIZE / 4.f);
        float y = AppUtils::getInstance()->randomNumber(0.1f, 3.f);
        float z = AppUtils::getInstance()->randomNumber(Config::SKYBOX_ZMIN + Config::SKYBOX_ZSIZE / 4.f, Config::SKYBOX_ZMAX - Config::SKYBOX_ZSIZE / 4.f);
        glm::vec3 position = glm::vec3(x, y, z);
        //position = glm::vec3(Config::SKYBOX_XCENTER, 2.f, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 6.f); // testing purposes

        auto shaderProgram = this->m_shaderWarehouse->getShaderProgram("shader:single_color");
        auto vao = this->m_modelWarehouse->getVAO("res:sphere");

        auto modelFf = std::make_unique<ModelFirefly>(shaderProgram, vao, 0, 2880);
        modelFf->getTransformation()->setTranslation(position);
        modelFf->getTransformation()->setRotationEulerAngles(glm::vec3(0.f));
        modelFf->getTransformation()->setScale(scale);
        this->m_modelWarehouse->addModel("04::firefly" + std::to_string(i), std::move(modelFf));

        //ModelFirefly* model = static_cast<ModelFirefly*>(this->m_modelWarehouse->getModel("04::firefly" + std::to_string(i)));
        model = this->m_modelWarehouse->getModel("04::firefly" + std::to_string(i));

        /*model = this->m_modelWarehouse->createModel(
            "04::firefly" + std::to_string(i),
            "shader:single_color", "res:sphere", 0, 2880,
            scale, glm::vec3(0.f), position);*/

        model->getTransformation()->updateTranslateStep(std::make_shared<TransformationAnimationRandomMove>(position));

        // --- firefly light source
        Light* light = this->m_lightWarehouse->createLight("04::firefly_light" + std::to_string(i), Light::LightTypeE::POINT, glm::vec3(0.f)); // no need to set position; it will follow the model
        light->setSpecularColor(glm::vec3(.6f, .6f, .6f));
        light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));

        model->addObserver(light); // light source now follows the model
    }

    // suzi
    this->m_modelWarehouse->createModel(
        "04::suziFlat",
        "shader:phong", sizeof(suziFlat), suziFlat, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER - 3.f, 1.5f, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 3.f));

    this->m_modelWarehouse->createModel(
        "04::suziSmooth",
        "shader:phong", sizeof(suziSmooth), suziSmooth, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER + 3.f, 1.5f, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 3.f));

    this->m_modelWarehouse->getModel("04::suziFlat")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, .05f, 0.f))); // 20 seconds for a full rotation
    this->m_modelWarehouse->getModel("04::suziSmooth")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, -.03f, 0.f))); // 30 seconds for a full rotation

    // torches
    // --- torch01
    model = this->m_modelWarehouse->createModel(
        "04::torch01",
        "shader:single_color", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2880,
        glm::vec3(.5f, 1.5f, .5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER - 6.f, 1.5f, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 3.f));
    model->setDiffuseColor(glm::vec3(.6f));

    Light* light = this->m_lightWarehouse->createLight("04::torch_light01", Light::LightTypeE::POINT, glm::vec3(0.f)); // no need to set position; it will follow the model
    light->setSpecularColor(glm::vec3(.6f, .6f, .6f));
    light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));

    model->addObserver(light); // light source now follows the model

    // --- torch02
    model = this->m_modelWarehouse->createModel(
        "04::torch02",
        "shader:single_color", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2880,
        glm::vec3(.5f, 1.5f, .5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER + 6.f, 1.5f, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 3.f));
    model->setDiffuseColor(glm::vec3(.6f));

    light = this->m_lightWarehouse->createLight("04::torch_light02", Light::LightTypeE::POINT, glm::vec3(0.f)); // no need to set position; it will follow the model
    light->setSpecularColor(glm::vec3(.6f, .6f, .6f));
    light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));

    model->addObserver(light); // light source now follows the model

    // gift
    this->m_modelWarehouse->createModel(
        "04::gift",
        "shader:phong", sizeof(gift), gift, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 66624,
        glm::vec3(11.f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XMIN + 30.f, 4.f, Config::SKYBOX_ZMIN + 30.f));

    this->m_modelWarehouse->getModel("04::gift")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(.05f, .1f, .15f))); // all axis rotation
}

void SceneBuilderPlugin05a::loadTextures() {
	this->m_textureWarehouse->loadTexture("tex:grass", (this->m_textureResourcesPath + "grass.png").c_str(), GL_TEXTURE0);
	this->m_textureWarehouse->loadTexture("tex:wood",  (this->m_textureResourcesPath + "test.png").c_str(),  GL_TEXTURE1);
}

void SceneBuilderPlugin05a::postProcess() {
    // camera position & flashlight
    this->m_scene->getCamera()->setPosition(
        glm::vec3(Config::SKYBOX_XCENTER, Config::CAMERA_HEIGHT, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 11.f),
        glm::vec3(0.f, 0.f, -1.f));

    this->m_lightWarehouse->createFlashlight("flashlight", this->m_scene->getCamera());
}
