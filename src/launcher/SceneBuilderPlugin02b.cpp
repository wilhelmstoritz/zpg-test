#include "SceneBuilderPlugin02b.h"
#include "AppUtils.h"
#include "Config.h"

#include "ModelLibrary.h"
#include "tree.h"
#include "bushes.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "gift.h"

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin02b::createShaders() {
}

void SceneBuilderPlugin02b::createLights() {
    // light source
    Light* light = new Light("light01default", Light::LightTypeE::POINT, glm::vec3(0.f, 90.f, 0.f));

	this->m_scene->addLight(light);
}

void SceneBuilderPlugin02b::createModels() {
    // skybox
    this->m_modelWarehouse->createModel(
        "skybox",
        "shaderViewProjection", ModelLibrary::MODEL_SKYBOX_RNDCOLORS, ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 36,
        //"shaderLambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        glm::vec3(Config::SKYBOX_XSIZE, Config::SKYBOX_YSIZE, Config::SKYBOX_ZSIZE),
        glm::vec3(0.f),
        glm::vec3(Config::SKYBOX_XMIN, Config::SKYBOX_YMIN, Config::SKYBOX_ZMIN));

    // trees
    this->m_modelWarehouse->createVertexResources("tree", sizeof(tree), tree, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    for (uint32_t i = 0; i < Config::ENVIRONMENT_TREES; ++i) {
        // random scale; between 0.5 and 1.5
        float rnd = AppUtils::getInstance()->randomNumber(.5f, 1.5f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = AppUtils::getInstance()->randomNumber(0.f, 360.f);
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        float x = AppUtils::getInstance()->randomNumber(Config::SKYBOX_XMIN, Config::SKYBOX_XMAX);
        float z = AppUtils::getInstance()->randomNumber(Config::SKYBOX_ZMIN, Config::SKYBOX_ZMAX);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        Model* model = this->m_modelWarehouse->createModel(
            "tree" + std::to_string(i),
            "shaderViewProjection", "tree", 0, 92814,
            //"shaderLambertian", "tree", 0, 92814,
            scale, rotation, position);
    }

    // bushes
    this->m_modelWarehouse->createVertexResources("bushes", sizeof(bushes), bushes, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    for (uint32_t i = 0; i < Config::ENVIRONMENT_BUSHES; ++i) {
        // random scale; between 0.5 and 1.5
        float rnd = AppUtils::getInstance()->randomNumber(.5f, 1.5f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = AppUtils::getInstance()->randomNumber(0.f, 360.f);
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        float x = AppUtils::getInstance()->randomNumber(Config::SKYBOX_XMIN, Config::SKYBOX_XMAX);
        float z = AppUtils::getInstance()->randomNumber(Config::SKYBOX_ZMIN, Config::SKYBOX_ZMAX);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        Model* model = this->m_modelWarehouse->createModel(
            "bushes" + std::to_string(i),
            "shaderViewProjection", "bushes", 0, 8730,
            //"shaderLambertian", "bushes", 0, 8730,
            scale, rotation, position);
    }

    // suzi
    this->m_modelWarehouse->createModel(
        "suziFlat",
        "shaderViewProjection", sizeof(suziFlat), suziFlat, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        //"shaderLambertian", sizeof(suziFlat), suziFlat, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER - 3.f, 1.5f, Config::SKYBOX_ZMAX - 20.f));

    this->m_modelWarehouse->createModel(
        "suziSmooth",
        "shaderViewProjection", sizeof(suziSmooth), suziSmooth, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        //"shaderLambertian", sizeof(suziSmooth), suziSmooth, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER + 3.f, 1.5f, Config::SKYBOX_ZMAX - 20.f));

    // gift
    this->m_modelWarehouse->createModel(
        "gift",
        "shaderViewProjection", sizeof(gift), gift, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 66624,
        //"shaderLambertian", sizeof(gift), gift, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 66624,
        glm::vec3(11.f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER, 4.f, Config::SKYBOX_ZCENTER));
}

void SceneBuilderPlugin02b::postProcess() {
    // camera position
    this->m_scene->getCamera()->setPosition(
        glm::vec3(Config::SKYBOX_XCENTER, Config::CAMERA_HEIGHT, Config::SKYBOX_ZMAX - 10.f),
        glm::vec3(0.f, 0.f, -1.f));
}
