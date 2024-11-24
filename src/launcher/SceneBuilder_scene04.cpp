#include "SceneBuilder.h"

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
        "shaderViewProjection", ModelLibrary::MODEL_SKYBOX, ModelFactory::s_defaultPositionColorBufferList, 0, 216,
        //"shaderLambertian", ModelLibrary::MODEL_SKYBOX, ModelFactory::s_defaultPositionColorBufferList, 0, 216,
        this->m_dimensions / glm::vec3(2.f, 1.f, 2.f), glm::vec3(0.f), glm::vec3(0.f));

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

    // gift
    this->m_modelFactory->createModel(
        "gift",
        "shaderPhong", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList, 0, 66624,
        glm::vec3(11.f), glm::vec3(0.f), glm::vec3( // to the center of the upper left corner; in the middle of the skybox and wooded area
            -t_areaSize.x / 2.f - (m_dimensions.x - t_areaSize.x) / 4.f,
            3.f,
            -t_areaSize.y / 2.f - (m_dimensions.z - t_areaSize.y) / 4.f));

    // light source
    Light* light = new Light(0, glm::vec3(0.f, 190.f, 0.f));
    light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    light->setSpotCutoff(0.9f);
    light->setDiffuseColor(glm::vec3(0.f, 1.f, 0.f));
    light->setSpecularColor(glm::vec3(0.f, 1.f, 0.0f));
    this->m_scene->addLight("light01default", light);

    light = new Light(2, glm::vec3(0.f, 90.f, 190.f));
    light->setDirection(glm::vec3(0.f, -90.f, -190.f));
    light->setSpotCutoff(0.98f);
    light->setDiffuseColor(glm::vec3(1.f, 1.f, 0.f)); // yellow
    light->setSpecularColor(glm::vec3(1.f, 1.f, 1.0f)); // white
    this->m_scene->addLight("light02", light);

    // camera position; corresponding to the scene
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 1.f, t_areaSize.y / 2.f + 10.f), // in the middle; 10 ahead before the first tree
        glm::vec3(0.f, 0.f, -1.f));
}
