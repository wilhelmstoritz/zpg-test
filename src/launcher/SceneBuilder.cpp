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
    this->m_scene = new Scene(new Camera(glm::vec3(0.f, 1.f, 60.f), glm::vec3(0.f, 0.f, -1.f)));
    this->m_shaderFactory = this->m_scene->getShaderFactory(); // for simplified data creation
    this->m_modelFactory = this->m_scene->getModelFactory();

    this->m_dimensions = glm::vec3(200.f, 100.f, 200.f); // default dimensions; x: 200 (-100..100); y: 100 (-0.1..100); z: 200 (-100..100)

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
    //this->createDefaultModels_01();
    //this->createDefaultModels_02();
    this->createSceneForest( // wooded area 100x100; 300 trees and 600 bushes
        glm::vec2(this->m_dimensions.x / 2.f, this->m_dimensions.y / 2.f),
        300);
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
void SceneBuilder::createDefaultModels_01() {
    // 1st task models
    this->m_modelFactory->createVertexResources("1stTriangle", TRIANGLE_POINTS, ModelFactory::s_defaultBufferList);
    this->m_modelFactory->createVertexResources("1stTriangleColorData", TRIANGLE_POINTS_COLORDATA, ModelFactory::s_defaultPositionColorBufferList);
    this->m_modelFactory->createVertexResources("1stSquare", SQUARE_POINTS, ModelFactory::s_defaultBufferList);
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
    this->m_modelFactory->createVertexResources("1stPentagon", sizeof(PENTAGON_POINTS), PENTAGON_POINTS, ModelFactory::s_defaultBufferList);

    //this->m_modelFactory->createModel("1stTriangle", "default", "1stTriangle", 0, 3);
    //this->m_modelFactory->createModel("1stTriangleColorFromPosition", "defaultColorFromPosition", "1stTriangle", 0, 3);
    this->m_modelFactory->createModel("1stTriangleColorData", "defaultColorData", "1stTriangleColorData", 0, 3);
    this->m_modelFactory->createModel("1stSquare", "yellow", "1stSquare", 0, 6);
    this->m_modelFactory->createModel("1stPentagon", "default", "1stPentagon", 0, 15);

    // all at once; some vertex resources are created twice this way
    //this->m_modelFactory->createModel("1stTriangle", "default", TRIANGLE_POINTS, ModelFactory::s_defaultBufferList, 0, 3);
    //this->m_modelFactory->createModel("1stTriangleColorFromPosition", "defaultColorFromPosition", TRIANGLE_POINTS, ModelFactory::s_defaultBufferList, 0, 3);
    //this->m_modelFactory->createModel("1stTriangleColorData", "defaultColorData", TRIANGLE_POINTS_COLORDATA, ModelFactory::s_defaultPositionColorBufferList, 0, 3);
    //this->m_modelFactory->createModel("1stSquare", "yellow", SQUARE_POINTS, ModelFactory::s_defaultBufferList, 0, 6);
    //this->m_modelFactory->createModel("1stPentagon", "default", sizeof(PENTAGON_POINTS), PENTAGON_POINTS, ModelFactory::s_defaultBufferList, 0, 15);
}

void SceneBuilder::createDefaultModels_02() {
    // 2nd task models; first/also try with the 'defaultColorData' shader program
    this->m_modelFactory->createModel("2ndBushes", "transformingNormalData", sizeof(bushes), bushes, ModelFactory::s_defaultPositionNormalBufferList, 0, 8730);
    this->m_modelFactory->createModel("2ndGift", "transformingNormalData", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList, 0, 66624);
    this->m_modelFactory->createModel("2ndPlain", "transformingNormalData", sizeof(plain), plain, ModelFactory::s_defaultPositionNormalBufferList, 0, 36);
    this->m_modelFactory->createModel("2ndSphere", "transformingNormalData", sizeof(sphere), sphere, ModelFactory::s_defaultPositionNormalBufferList, 0, 17280);
    this->m_modelFactory->createModel("2ndSuziFlat", "transformingNormalData", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424);
    this->m_modelFactory->createModel("2ndSuziSmooth", "transformingNormalData", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424);
    this->m_modelFactory->createModel("2ndTree", "transformingNormalData", sizeof(tree), tree, ModelFactory::s_defaultPositionNormalBufferList, 0, 92814);

    this->m_modelFactory->getModel("2ndBushes")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-9.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndGift")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-6.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndPlain")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-3.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndSphere")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(0.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndSuziFlat")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(3.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndSuziSmooth")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(6.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndTree")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(9.f, 0.f, 0.f)));
}

void SceneBuilder::createSceneForest(const glm::vec2 t_areaSize, const int t_numberOfTrees) {
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
        float x = static_cast<float>(rand()) / RAND_MAX * t_areaSize.x - (t_areaSize.x / 2);
        float z = static_cast<float>(rand()) / RAND_MAX * t_areaSize.y - (t_areaSize.y / 2);
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
        float x = static_cast<float>(rand()) / RAND_MAX * t_areaSize.x - (t_areaSize.x / 2);
        float z = static_cast<float>(rand()) / RAND_MAX * t_areaSize.y - (t_areaSize.y / 2);
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

    // gift
    this->m_modelFactory->createModel(
		"gift",
		"transformingNormalData", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList, 0, 66624,
		glm::vec3(11.f), glm::vec3(0.f), glm::vec3(-75.f, 3.f, -75.f));
}
