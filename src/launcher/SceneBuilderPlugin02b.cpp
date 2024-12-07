#include "SceneBuilderPlugin02b.h"
#include "AppUtils.h"
#include "Config.h"

#include "resShaders.h"

#include "ModelLibrary.h"
#include "tree.h"
#include "bushes.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "gift.h"

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin02b::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createVertexShader("vert:view_projection_matrix", VSHADER_VIEW_PROJECTION_MATRIX);
    this->m_shaderWarehouse->createFragmentShader("frag:view_projection_matrix", FSHADER_VIEW_PROJECTION_MATRIX);

    this->m_shaderWarehouse->createShaderProgram("shader:view_projection_matrix",
        *this->m_shaderWarehouse->getShader("vert:view_projection_matrix"),
        *this->m_shaderWarehouse->getShader("frag:view_projection_matrix"));
}

void SceneBuilderPlugin02b::createModels() {
    // skybox
    this->m_modelWarehouse->createModel(
        "02::skybox",
        "shader:view_projection_matrix", ModelLibrary::MODEL_SKYBOX_RNDCOLORS, ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 36,
        glm::vec3(Config::SKYBOX_XSIZE, Config::SKYBOX_YSIZE, Config::SKYBOX_ZSIZE),
        glm::vec3(0.f),
        glm::vec3(Config::SKYBOX_XMIN, Config::SKYBOX_YMIN, Config::SKYBOX_ZMIN));

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
        float x = AppUtils::getInstance()->randomNumber(Config::SKYBOX_XMIN, Config::SKYBOX_XMAX);
        float z = AppUtils::getInstance()->randomNumber(Config::SKYBOX_ZMIN, Config::SKYBOX_ZMAX);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        Model* model = this->m_modelWarehouse->createModel(
            "02::tree:" + std::to_string(i),
            "shader:view_projection_matrix", "res:tree", 0, 92814,
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
        float x = AppUtils::getInstance()->randomNumber(Config::SKYBOX_XMIN, Config::SKYBOX_XMAX);
        float z = AppUtils::getInstance()->randomNumber(Config::SKYBOX_ZMIN, Config::SKYBOX_ZMAX);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        Model* model = this->m_modelWarehouse->createModel(
            "02::bushes:" + std::to_string(i),
            "shader:view_projection_matrix", "res:bushes", 0, 8730,
            scale, rotation, position);
    }

    // suzi
    this->m_modelWarehouse->createModel(
        "02::suziFlat",
        "shader:view_projection_matrix", sizeof(suziFlat), suziFlat, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER - 3.f, 1.5f, Config::SKYBOX_ZMAX - 20.f));

    this->m_modelWarehouse->createModel(
        "02::suziSmooth",
        "shader:view_projection_matrix", sizeof(suziSmooth), suziSmooth, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER + 3.f, 1.5f, Config::SKYBOX_ZMAX - 20.f));

    // gift
    this->m_modelWarehouse->createModel(
        "02::gift",
        "shader:view_projection_matrix", sizeof(gift), gift, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 66624,
        glm::vec3(11.f), glm::vec3(0.f), glm::vec3(Config::SKYBOX_XCENTER, 4.f, Config::SKYBOX_ZCENTER));
}

void SceneBuilderPlugin02b::postProcess() {
    // camera position
    this->m_scene->getCamera()->setPosition(
        glm::vec3(Config::SKYBOX_XCENTER, Config::CAMERA_HEIGHT, Config::SKYBOX_ZMAX - 10.f),
        glm::vec3(0.f, 0.f, -1.f));
}
