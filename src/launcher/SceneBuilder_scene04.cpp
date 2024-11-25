#include "SceneBuilder.h"
#include "Config.h"
#include "LightFlashlight.h"
#include "TransformationAnimationRotate.h"

#include "ModelLibrary.h"

#include "bushes.h"
#include "gift.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

void SceneBuilder::createScene_04_magicWoods() {
    srand(static_cast<unsigned int>(time(0))); // seed random number generator

    // skybox
    this->m_modelFactory->createModel(
        "skybox",
        //"shaderViewProjection", ModelLibrary::MODEL_SKYBOX_RNDCOLORS, ModelFactory::s_defaultPositionColorBufferList, 0, 36,
        //"shaderLambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::s_defaultPositionNormalBufferList, 0, 36,
        "shaderPhong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::s_defaultPositionNormalBufferList, 0, 36,
        glm::vec3(Config::SKYBOX_XSIZE, Config::SKYBOX_YSIZE, Config::SKYBOX_ZSIZE),
        glm::vec3(0.f),
        glm::vec3(Config::SKYBOX_XMIN, 0.f, Config::SKYBOX_ZMIN));

    // trees
    this->m_modelFactory->createVertexResources("tree", sizeof(tree), tree, ModelFactory::s_defaultPositionNormalBufferList);

    for (uint32_t i = 0; i < Config::ENVIRONMENT_TREES; ++i) {
        // random scale; between 0.5 and 1.5
        float rnd = .5f + (static_cast<float>(rand()) / RAND_MAX) * (1.5f - .5f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = static_cast<float>(rand()) / RAND_MAX * 360.f;
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        float x = static_cast<float>(rand()) / RAND_MAX * Config::SKYBOX_XSIZE / 2.f + Config::SKYBOX_XMIN + Config::SKYBOX_XSIZE / 4.f;
        float z = static_cast<float>(rand()) / RAND_MAX * Config::SKYBOX_ZSIZE / 2.f + Config::SKYBOX_ZMIN + Config::SKYBOX_ZSIZE / 4.f;
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
        float rnd = .5f + (static_cast<float>(rand()) / RAND_MAX) * (1.5f - .5f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = static_cast<float>(rand()) / RAND_MAX * 360.f;
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        //float x = static_cast<float>(rand()) / RAND_MAX * Config::SKYBOX_XSIZE + Config::SKYBOX_XMIN;
        //float z = static_cast<float>(rand()) / RAND_MAX * Config::SKYBOX_ZSIZE + Config::SKYBOX_ZMIN;
        float x = static_cast<float>(rand()) / RAND_MAX * Config::SKYBOX_XSIZE / 2.f + Config::SKYBOX_XMIN + Config::SKYBOX_XSIZE / 4.f;
        float z = static_cast<float>(rand()) / RAND_MAX * Config::SKYBOX_ZSIZE / 2.f + Config::SKYBOX_ZMIN + Config::SKYBOX_ZSIZE / 4.f;
        glm::vec3 position = glm::vec3(x, 0.f, z);

        Model* model = this->m_modelFactory->createModel(
            "bushes" + std::to_string(i),
            "shaderPhong", "bushes", 0, 8730,
            scale, rotation, position);
    }

    // fireflies

    // suzi
    this->m_modelFactory->createModel(
        "suziFlat",
        "shaderPhong", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER - 3.f, 1.5f, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 3.f));

    this->m_modelFactory->createModel(
        "suziSmooth",
        "shaderPhong", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER + 3.f, 1.5f, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 3.f));

    this->m_modelFactory->getModel("suziFlat")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, .05f, 0.f))); // 20 seconds for a full rotation
    this->m_modelFactory->getModel("suziSmooth")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, -.03f, 0.f))); // 30 seconds for a full rotation

    // gift
    this->m_modelFactory->createModel(
        "gift",
        "shaderPhong", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList, 0, 66624,
        glm::vec3(11.f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XMIN + 30.f, 4.f, Config::SKYBOX_ZMIN + 30.f));

    this->m_modelFactory->getModel("gift")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(.05f, .1f, .15f))); // all axis rotation

    // light source
    Light* light = new Light("light01default", 0, glm::vec3(0.f, 90.f, 0.f)); // moonlight
    light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    //light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(glm::vec3(0.f, .01f, 0.f));
    light->setSpecularColor(glm::vec3(0.f, .3f, 0.f));
    this->m_scene->addLight(light);

    light = new Light("light02", 2, glm::vec3(0.f, 90.f, 90.f));
    light->setDirection(glm::vec3(0.f, -1.f, -1.f));
    light->setSpotCutoffDegrees(30.f);
    light->setDiffuseColor(glm::vec3(0.f, .1f, 0.f));
    light->setSpecularColor(glm::vec3(0.f, .1f, 0.f));
    //this->m_scene->addLight(light);

    light = new Light("light03", 2, glm::vec3(-50.f, 10.f, -50.f)); // gift spotlight
    light->setDirection(glm::vec3(-2.f, -1.f, -2.f));
    light->setSpotCutoffDegrees(30.f);
    light->setDiffuseColor(glm::vec3(1.f, 0.5f, 1.f));
    light->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
    light->setAttenuation(1.f, .01f, .001f);
    this->m_scene->addLight(light);

    LightFlashlight* flashlight = new LightFlashlight("flashlight", 2, glm::vec3(Config::SKYBOX_XCENTER, Config::PLAYER_FLASHLIGHT_HEIGHT, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 11.f)); // flashlight
    flashlight->setDirection(glm::vec3(0.f, 0.f, -1.f));
    flashlight->setSpotCutoffDegrees(15.f);
    flashlight->setDiffuseColor(glm::vec3(1.f, 1.f, 0.f)); // yellow
    flashlight->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
    flashlight->setAttenuation(1.f, .09f, .032f);
    this->m_scene->addLight(flashlight);

    // camera position; corresponding to the scene
    this->m_scene->getCamera()->addObserver(flashlight); // flashlight follows the camera now
    this->m_scene->getCamera()->setPosition(
        glm::vec3(Config::SKYBOX_XCENTER, Config::PLAYER_HEIGHT, Config::SKYBOX_ZCENTER + Config::SKYBOX_ZSIZE / 4.f + 11.f),
        glm::vec3(0.f, 0.f, -1.f));
}
