#include "SceneBuilder.h"
#include "data.h"

#include "bushes.h"
#include "gift.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

// initialization of static class members
//SceneBuilder* SceneBuilder::_instance = nullptr;
std::unique_ptr<SceneBuilder> SceneBuilder::_instance = nullptr;
std::mutex SceneBuilder::_mtx;

// --- public ------------------------------------------------------------------
SceneBuilder* SceneBuilder::getInstance() {
    std::lock_guard<std::mutex> lock(_mtx);
    if (_instance == nullptr) {
        //_instance = new SceneBuilder();
        _instance.reset(new SceneBuilder());
    }

    //return _instance;
    return _instance.get();
}

Scene* SceneBuilder::createScene() {
	std::lock_guard<std::mutex> lock(_mtx);

    // new empty scene
    this->m_scene = new Scene(new Camera(glm::vec3(0.f, 1.f, 40.f), glm::vec3(0.f, 0.f, -1.f)));
    this->m_shaderFactory = this->m_scene->getShaderFactory(); // for simplified data creation
    this->m_modelFactory = this->m_scene->getModelFactory();

    // fill the scene and bring it to life
    this->createContext();
    this->addContextToScene();

    this->m_scene->setCamera();

	return this->m_scene;
}

// --- private -----------------------------------------------------------------
void SceneBuilder::createContext() {
    // create shaders and shader programs
    this->createDefaultShaders();
    this->createTransformingShaders();

    // create models
    //this->createDefaultModels();
    this->createSceneForest(100.f, 300); // wooded area 100x100; 300 trees and 600 bushes
}

void SceneBuilder::addContextToScene() {
	// add all (existing) models to the scene
    for (const auto& pair : *this->m_modelFactory->getModels()) {
        this->m_scene->addModel(pair.second.get());
    }
}

// === shader factory ==========================================================
void SceneBuilder::createDefaultShaders() {
    // vertex & fragment shaders
    this->m_shaderFactory->createVertexShader("v_default", DEFAULT_VERTEX_SHADER);
    this->m_shaderFactory->createFragmentShader("f_default", DEFAULT_FRAGMENT_SHADER);

    this->m_shaderFactory->createVertexShader("v_defaultColorFromPosition", DEFAULT_VERTEX_SHADER_COLORFROMPOSITION);
    this->m_shaderFactory->createFragmentShader("f_defaultColorFromPosition", DEFAULT_FRAGMENT_SHADER_COLORFROMPOSITION);

    this->m_shaderFactory->createVertexShader("v_defaultColorData", DEFAULT_VERTEX_SHADER_COLORDATA);
    this->m_shaderFactory->createFragmentShader("f_defaultColorData", DEFAULT_FRAGMENT_SHADER_COLORDATA);

    this->m_shaderFactory->createFragmentShader("f_yellow", YELLOW_FRAGMENT_SHADER);

    // shader programs
    this->m_shaderFactory->createShaderProgram("default",
        *this->m_shaderFactory->getShader("v_default"),
        *this->m_shaderFactory->getShader("f_default"));

    this->m_shaderFactory->createShaderProgram("defaultColorFromPosition",
        *this->m_shaderFactory->getShader("v_defaultColorFromPosition"),
        *this->m_shaderFactory->getShader("f_defaultColorFromPosition"));

    this->m_shaderFactory->createShaderProgram("defaultColorData",
        *this->m_shaderFactory->getShader("v_defaultColorData"),
        *this->m_shaderFactory->getShader("f_defaultColorData"));

    this->m_shaderFactory->createShaderProgram("yellow",
        *this->m_shaderFactory->getShader("v_default"),
        *this->m_shaderFactory->getShader("f_yellow"));
}

void SceneBuilder::createTransformingShaders() {
    // vertex & fragment shaders
    this->m_shaderFactory->createVertexShader("v_transformingNormalData", TRANSFORMING_VERTEX_SHADER_NORMALDATA);
    this->m_shaderFactory->createFragmentShader("f_transformingNormalData", TRANSFORMING_FRAGMENT_SHADER_NORMALDATA);

    // shader programs
    this->m_shaderFactory->createShaderProgram("transformingNormalData",
        *this->m_shaderFactory->getShader("v_transformingNormalData"),
        *this->m_shaderFactory->getShader("f_transformingNormalData"));
}

// === model factory ===========================================================
void SceneBuilder::createDefaultModels() {
    // 1st task models
    //this->m_modelFactory->createVertexResources("triangle", TRIANGLE_POINTS, ModelFactory::s_defaultBufferList);
    //this->m_modelFactory->createVertexResources("triangleColorData", TRIANGLE_POINTS_COLORDATA, ModelFactory::s_defaultPositionColorBufferList);
    //this->m_modelFactory->createVertexResources("square", SQUARE_POINTS, ModelFactory::s_defaultBufferList);
    float PENTAGON_POINTS[] = {
        // 1st triangle
         0.0f,     0.0f,    0.0f, // centre
         1.0f,     0.0f,    0.0f, // apex #1
         0.3090f,  0.9511f, 0.0f, // apex #2
        // 2nd triangle
         0.0f,     0.0f,    0.0f, // centre
         0.3090f,  0.9511f, 0.0f, // apex #2
        -0.8090f,  0.5878f, 0.0f, // apex #3
        // 3rd triangle
         0.0f,     0.0f,    0.0f, // centre
        -0.8090f,  0.5878f, 0.0f, // apex #3
        -0.8090f, -0.5878f, 0.0f, // apex #4
        // 4th triangle
         0.0f,     0.0f,    0.0f, // centre
        -0.8090f, -0.5878f, 0.0f, // apex #4
         0.3090f, -0.9511f, 0.0f, // apex #5
        // 5th triangle
         0.0f,     0.0f,    0.0f, // centre
         0.3090f, -0.9511f, 0.0f, // apex #5
         1.0f,     0.0f,    0.0f  // apex #1
    };
    //this->m_modelFactory->createVertexResources("pentagon", sizeof(PENTAGON_POINTS), PENTAGON_POINTS, ModelFactory::s_defaultBufferList);

    //this->m_modelFactory->createModel("triangle", "default", "triangle", 0, 3);
    //this->m_modelFactory->createModel("triangleColorFromPosition", "defaultColorFromPosition", "triangle", 0, 3);
    //this->m_modelFactory->createModel("triangleColorData", "defaultColorData", "triangleColorData", 0, 3);
    //this->m_modelFactory->createModel("square", "yellow", "square", 0, 6);
    //this->m_modelFactory->createModel("pentagon", "default", "pentagon", 0, 15);
    // all at once
    //this->m_modelFactory->createModel("triangle", "default", TRIANGLE_POINTS, ModelFactory::s_defaultBufferList, 0, 3);
    //this->m_modelFactory->createModel("triangleColorFromPosition", "defaultColorFromPosition", TRIANGLE_POINTS, ModelFactory::s_defaultBufferList, 0, 3);
    //this->m_modelFactory->createModel("triangleColorData", "defaultColorData", TRIANGLE_POINTS_COLORDATA, ModelFactory::s_defaultPositionColorBufferList, 0, 3);
    //this->m_modelFactory->createModel("square", "yellow", SQUARE_POINTS, ModelFactory::s_defaultBufferList, 0, 6);
    //this->m_modelFactory->createModel("pentagon", "default", sizeof(PENTAGON_POINTS), PENTAGON_POINTS, ModelFactory::s_defaultBufferList, 0, 15);

    // 2nd task models
    //this->m_modelFactory->createModel("zpgBushes", "transformingNormalData", sizeof(bushes), bushes, ModelFactory::s_defaultPositionNormalBufferList, 0, 8730);
    //this->m_modelFactory->createModel("zpgGift", "transformingNormalData", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList, 0, 66624);
    //this->m_modelFactory->createModel("zpgPlain", "transformingNormalData", sizeof(plain), plain, ModelFactory::s_defaultPositionNormalBufferList, 0, 36);
    //this->m_modelFactory->createModel("zpgSphere", "transformingNormalData", sizeof(sphere), sphere, ModelFactory::s_defaultPositionNormalBufferList, 0, 17280);
    //this->m_modelFactory->createModel("zpgSuziFlat", "transformingNormalData", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424);
    //this->m_modelFactory->createModel("zpgSuziSmooth", "transformingNormalData", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424);
    //this->m_modelFactory->createModel("zpgTree", "transformingNormalData", sizeof(tree), tree, ModelFactory::s_defaultPositionNormalBufferList, 0, 92814);
}

void SceneBuilder::createSceneForest(const float t_areaSize, const int t_numberOfTrees) {
    srand(static_cast<unsigned int>(time(0))); // seed random number generator

    // skybox
    this->m_modelFactory->createModel("skybox", "transformingNormalData", SKYBOX, ModelFactory::s_defaultPositionColorBufferList, 0, 216);

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
        float x = static_cast<float>(rand()) / RAND_MAX * t_areaSize - (t_areaSize / 2);
        float z = static_cast<float>(rand()) / RAND_MAX * t_areaSize - (t_areaSize / 2);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        Model* model = this->m_modelFactory->createModel(
            "tree" + std::to_string(i),
            "transformingNormalData", "tree", 0, 92814,
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
        float x = static_cast<float>(rand()) / RAND_MAX * t_areaSize - (t_areaSize / 2);
        float z = static_cast<float>(rand()) / RAND_MAX * t_areaSize - (t_areaSize / 2);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        Model* model = this->m_modelFactory->createModel(
            "bushes" + std::to_string(i),
            "transformingNormalData", "bushes", 0, 8730,
            scale, rotation, position);
    }

    // suzi
    this->m_modelFactory->createModel(
        "suziFlat",
        "transformingNormalData", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(-3.f, 1.5f, 52.f));

    this->m_modelFactory->createModel(
        "suziSmooth",
        "transformingNormalData", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(3.f, 1.5f, 52.f));
}
