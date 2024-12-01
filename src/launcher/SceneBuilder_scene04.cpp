#include "SceneBuilder.h"
#include "AppUtils.h"
#include "Config.h"
#include "LightFlashlight.h"
#include "TransformationAnimationRotate.h"
#include "TransformationAnimationRandomMove.h"

#include "ModelLibrary.h"
#include "Model.h"
#include "ModelFirefly.h"

#include "bushes.h"
#include "gift.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

// include the standard C++ headers
//#include <memory>

void SceneBuilder::createScene_04_magicWoods() {
    // skybox
    this->m_modelFactory->createModel(
        "skybox",
        //"shaderViewProjection", ModelLibrary::MODEL_SKYBOX_RNDCOLORS, ModelFactory::s_defaultPositionColorBufferList, 0, 36,
        //"shaderLambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::s_defaultPositionNormalBufferList, 0, 36,
        "shaderPhong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::s_defaultPositionNormalBufferList, 0, 36,
        glm::vec3(Config::SKYBOX_XSIZE, Config::SKYBOX_YSIZE, Config::SKYBOX_ZSIZE),
        glm::vec3(0.f),
        glm::vec3(Config::SKYBOX_XMIN, Config::SKYBOX_YMIN, Config::SKYBOX_ZMIN));

    // trees
    this->m_modelFactory->createVertexResources("tree", sizeof(tree), tree, ModelFactory::s_defaultPositionNormalBufferList);

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

        Model* model = this->m_modelFactory->createModel(
            "tree" + std::to_string(i),
            "shaderPhong", "tree", 0, 92814,
            scale, rotation, position);
    }

    // bushes
    this->m_modelFactory->createVertexResources("bushes", sizeof(bushes), bushes, ModelFactory::s_defaultPositionNormalBufferList);

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

        Model* model = this->m_modelFactory->createModel(
            "bushes" + std::to_string(i),
            "shaderPhong", "bushes", 0, 8730,
            scale, rotation, position);
    }

    // fireflies
    this->m_modelFactory->createVertexResources("sphere", sizeof(sphere), sphere, ModelFactory::s_defaultPositionNormalBufferList);

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

        auto shaderProgram = this->m_shaderFactory->getShaderProgram("shaderSingleColor");
        auto vao = this->m_modelFactory->getVAO("sphere");

        auto modelFf = std::make_unique<ModelFirefly>(shaderProgram, vao, 0, 2880);
        modelFf->getTransformation()->setTranslation(position);
        modelFf->getTransformation()->setRotationEulerAngles(glm::vec3(0.f));
        modelFf->getTransformation()->setScale(scale);
        this->m_modelFactory->addModel("firefly" + std::to_string(i), std::move(modelFf));

        ModelFirefly* model = static_cast<ModelFirefly*>(this->m_modelFactory->getModel("firefly" + std::to_string(i)));

        /*Model* model = this->m_modelFactory->createModel(
            "firefly" + std::to_string(i),
            "shaderSingleColor", "sphere", 0, 2880,
            scale, glm::vec3(0.f), position);*/

        model->getTransformation()->updateTranslateStep(std::make_shared<TransformationAnimationRandomMove>(position));

        // --- firefly light source
        Light* light = new Light("firefly" + std::to_string(i), Light::LightTypeE::POINT, glm::vec3(0.f)); // no need to set position; it will follow the model
        light->setSpecularColor(glm::vec3(.6f, .6f, .6f));
        light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));
        this->m_scene->addLight(light);

        model->addObserver(light); // light source now follows the model
    }

    // suzi
    this->m_modelFactory->createModel(
        "suziFlat",
        "shaderPhong", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER - 3.f, 1.5f, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 3.f));

    this->m_modelFactory->createModel(
        "suziSmooth",
        "shaderPhong", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER + 3.f, 1.5f, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 3.f));

    this->m_modelFactory->getModel("suziFlat")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, .05f, 0.f))); // 20 seconds for a full rotation
    this->m_modelFactory->getModel("suziSmooth")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, -.03f, 0.f))); // 30 seconds for a full rotation

    // torches
    // --- torch01
    Model* model = this->m_modelFactory->createModel(
        "torch01",
        "shaderSingleColor", sizeof(sphere), sphere, ModelFactory::s_defaultPositionNormalBufferList, 0, 2880,
        glm::vec3(.5f, 1.5f, .5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER - 6.f, 1.5f, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 3.f));
    model->setDiffuseColor(glm::vec3(.6f));

    Light* light = new Light("torch01", Light::LightTypeE::POINT, glm::vec3(0.f)); // no need to set position; it will follow the model
    light->setSpecularColor(glm::vec3(.6f, .6f, .6f));
    light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));
    this->m_scene->addLight(light);

    model->addObserver(light); // light source now follows the model

    // --- torch02
    model = this->m_modelFactory->createModel(
        "torch02",
        "shaderSingleColor", sizeof(sphere), sphere, ModelFactory::s_defaultPositionNormalBufferList, 0, 2880,
        glm::vec3(.5f, 1.5f, .5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER + 6.f, 1.5f, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 3.f));
    model->setDiffuseColor(glm::vec3(.6f));

    light = new Light("torch02", Light::LightTypeE::POINT, glm::vec3(0.f)); // no need to set position; it will follow the model
    light->setSpecularColor(glm::vec3(.6f, .6f, .6f));
    light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));
    this->m_scene->addLight(light);

    model->addObserver(light); // light source now follows the model

    // gift
    this->m_modelFactory->createModel(
        "gift",
        "shaderPhong", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList, 0, 66624,
        glm::vec3(11.f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XMIN + 30.f, 4.f, Config::SKYBOX_ZMIN + 30.f));

    this->m_modelFactory->getModel("gift")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(.05f, .1f, .15f))); // all axis rotation

    // light source
    light = new Light("light01default", Light::LightTypeE::DIRECTIONAL, glm::vec3(0.f, 90.f, 0.f)); // moonlight
    light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    //light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(glm::vec3(0.f, .01f, 0.f));
    light->setSpecularColor(glm::vec3(0.f, .3f, 0.f));
    //this->m_scene->addLight(light);

    light = new Light("light02", Light::LightTypeE::SPOT, glm::vec3(0.f, 90.f, 90.f));
    light->setDirection(glm::vec3(0.f, -1.f, -1.f));
    light->setSpotCutoffDegrees(30.f);
    light->setDiffuseColor(glm::vec3(0.f, .1f, 0.f));
    light->setSpecularColor(glm::vec3(0.f, .1f, 0.f));
    //this->m_scene->addLight(light);

    light = new Light("light03", Light::LightTypeE::SPOT, glm::vec3(-50.f, 10.f, -50.f)); // gift spotlight
    light->setDirection(glm::vec3(-2.f, -1.f, -2.f));
    light->setSpotCutoffDegrees(30.f);
    light->setDiffuseColor(glm::vec3(1.f, 0.5f, 1.f));
    light->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
    light->setAttenuation(glm::vec3(1.f, .01f, .001f));
    this->m_scene->addLight(light);

    // camera position & flashlight
    this->m_scene->getCamera()->setPosition(
        glm::vec3(Config::SKYBOX_XCENTER, Config::CAMERA_HEIGHT, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 11.f),
        glm::vec3(0.f, 0.f, -1.f));

	LightFlashlight* flashlight = new LightFlashlight("flashlight", this->m_scene->getCamera());
	this->m_scene->addLight(flashlight);
}
