#include "SceneBuilder.h"
#include "Config.h"

#include "ModelLibrary.h"

#include "bushes.h"
#include "gift.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

// include the standard C++ headers
#include <cstdlib> // rand, srand
#include <ctime>   // seeding random numbers

void SceneBuilder::createScene_02_woods() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // seed random number generator

    // skybox
    this->m_modelFactory->createModel(
        "skybox",
        "shaderViewProjection", ModelLibrary::MODEL_SKYBOX_RNDCOLORS, ModelFactory::s_defaultPositionColorBufferList, 0, 36,
        //"shaderLambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::s_defaultPositionNormalBufferList, 0, 36,
        glm::vec3(Config::SKYBOX_XSIZE, Config::SKYBOX_YSIZE, Config::SKYBOX_ZSIZE),
        glm::vec3(0.f),
        glm::vec3(Config::SKYBOX_XMIN, Config::SKYBOX_YMIN, Config::SKYBOX_ZMIN));

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
        float x = static_cast<float>(rand()) / RAND_MAX * Config::SKYBOX_XSIZE + Config::SKYBOX_XMIN;
        float z = static_cast<float>(rand()) / RAND_MAX * Config::SKYBOX_ZSIZE + Config::SKYBOX_ZMIN;
        glm::vec3 position = glm::vec3(x, 0.f, z);

        Model* model = this->m_modelFactory->createModel(
            "tree" + std::to_string(i),
            "shaderViewProjection", "tree", 0, 92814,
            //"shaderLambertian", "tree", 0, 92814,
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
        float x = static_cast<float>(rand()) / RAND_MAX * Config::SKYBOX_XSIZE + Config::SKYBOX_XMIN;
        float z = static_cast<float>(rand()) / RAND_MAX * Config::SKYBOX_ZSIZE + Config::SKYBOX_ZMIN;
        glm::vec3 position = glm::vec3(x, 0.f, z);

        Model* model = this->m_modelFactory->createModel(
            "bushes" + std::to_string(i),
            "shaderViewProjection", "bushes", 0, 8730,
            //"shaderLambertian", "bushes", 0, 8730,
            scale, rotation, position);
    }

    // suzi
    this->m_modelFactory->createModel(
        "suziFlat",
        "shaderViewProjection", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList, 0, 2904,
        //"shaderLambertian", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER - 3.f, 1.5f, Config::SKYBOX_ZMAX - 20.f));

    this->m_modelFactory->createModel(
        "suziSmooth",
        "shaderViewProjection", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList, 0, 2904,
        //"shaderLambertian", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER + 3.f, 1.5f, Config::SKYBOX_ZMAX - 20.f));

    // gift
    this->m_modelFactory->createModel(
        "gift",
        "shaderViewProjection", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList, 0, 66624,
        //"shaderLambertian", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList, 0, 66624,
        glm::vec3(11.f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER, 4.f, Config::SKYBOX_ZCENTER));

    // light source
    this->m_scene->addLight(new Light("light01default", Light::LightTypeE::POINT, glm::vec3(0.f, 90.f, 0.f)));

    // camera position
    this->m_scene->getCamera()->setPosition(
        glm::vec3(Config::SKYBOX_XCENTER, Config::CAMERA_HEIGHT, Config::SKYBOX_ZMAX - 10.f),
        glm::vec3(0.f, 0.f, -1.f));
}
