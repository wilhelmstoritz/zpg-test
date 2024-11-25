#include "SceneBuilder.h"
#include "LightFlashlight.h"
#include "TransformationAnimationRotate.h"

#include "ModelLibrary.h"

#include "bushes.h"
#include "gift.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

void SceneBuilder::createScene_04_magicWoods(const glm::vec2 t_areaSize, const int t_numberOfTrees) {
    srand(static_cast<unsigned int>(time(0))); // seed random number generator

    // skybox
    this->m_modelFactory->createModel(
        "skybox",
        //"shaderViewProjection", ModelLibrary::MODEL_SKYBOX_RNDCOLORS, ModelFactory::s_defaultPositionColorBufferList, 0, 36,
        //"shaderLambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::s_defaultPositionNormalBufferList, 0, 36,
        "shaderPhong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::s_defaultPositionNormalBufferList, 0, 36,
        this->m_dimensions, glm::vec3(0.f), glm::vec3(-this->m_dimensions.x / 2.f, 0.f, -this->m_dimensions.z / 2.f));

    // trees
    this->m_modelFactory->createVertexResources("tree", sizeof(tree), tree, ModelFactory::s_defaultPositionNormalBufferList);

    for (int i = 0; i < t_numberOfTrees; ++i) {
        // random scale; between 0.5 and 1.5
        float rnd = .5f + (static_cast<float>(rand()) / RAND_MAX) * (1.5f - .5f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = static_cast<float>(rand()) / RAND_MAX * 360.f;
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        float x = static_cast<float>(rand()) / RAND_MAX * t_areaSize.x - (t_areaSize.x / 2);
        float z = static_cast<float>(rand()) / RAND_MAX * t_areaSize.y - (t_areaSize.y / 2);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        Model* model = this->m_modelFactory->createModel(
            "tree" + std::to_string(i),
            "shaderPhong", "tree", 0, 92814,
            scale, rotation, position);
    }

    // bushes
    this->m_modelFactory->createVertexResources("bushes", sizeof(bushes), bushes, ModelFactory::s_defaultPositionNormalBufferList);

    for (int i = 0; i < (t_numberOfTrees * 2); ++i) {
        // random scale; between 0.5 and 1.5
        float rnd = .5f + (static_cast<float>(rand()) / RAND_MAX) * (1.5f - .5f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = static_cast<float>(rand()) / RAND_MAX * 360.f;
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        float x = static_cast<float>(rand()) / RAND_MAX * t_areaSize.x - (t_areaSize.x / 2);
        float z = static_cast<float>(rand()) / RAND_MAX * t_areaSize.y - (t_areaSize.y / 2);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        Model* model = this->m_modelFactory->createModel(
            "bushes" + std::to_string(i),
            "shaderPhong", "bushes", 0, 8730,
            scale, rotation, position);
    }

    // suzi
    this->m_modelFactory->createModel(
        "suziFlat",
        "shaderPhong", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(-3.f, 1.5f, t_areaSize.y / 2.f + 3.f)); // -3 to the left, 3 ahead before the first tree

    this->m_modelFactory->createModel(
        "suziSmooth",
        "shaderPhong", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(3.f, 1.5f, t_areaSize.y / 2.f + 3.f)); // 3 to the right, 3 ahead before the first tree

    this->m_modelFactory->getModel("suziFlat")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, .05f, 0.f))); // 20 seconds for a full rotation
    this->m_modelFactory->getModel("suziSmooth")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, -.03f, 0.f))); // 30 seconds for a full rotation

    // gift
    this->m_modelFactory->createModel(
        "gift",
        "shaderPhong", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList, 0, 66624,
        glm::vec3(11.f), glm::vec3(0.f), glm::vec3( // to the center of the upper left corner; in the middle of the skybox and wooded area
            -t_areaSize.x / 2.f - (m_dimensions.x - t_areaSize.x) / 4.f,
            4.f,
            -t_areaSize.y / 2.f - (m_dimensions.z - t_areaSize.y) / 4.f));

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

    LightFlashlight* flashlight = new LightFlashlight("flashlight", 2, glm::vec3(0.f, 1.f, t_areaSize.y / 2.f + 10.f)); // flashlight
    flashlight->setDirection(glm::vec3(0.f, 0.f, -1.f));
    flashlight->setSpotCutoffDegrees(15.f);
    flashlight->setDiffuseColor(glm::vec3(1.f, 1.f, 0.f)); // yellow
    flashlight->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
    flashlight->setAttenuation(1.f, .09f, .032f);
    this->m_scene->addLight(flashlight);

    // camera position; corresponding to the scene
    this->m_scene->getCamera()->addObserver(flashlight); // flashlight follows the camera now
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 1.f, t_areaSize.y / 2.f + 10.f), // in the middle; 10 ahead before the first tree
        glm::vec3(0.f, 0.f, -1.f));
}
