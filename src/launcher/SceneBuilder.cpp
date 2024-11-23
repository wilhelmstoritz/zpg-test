#include "SceneBuilder.h"
#include "AppUtils.h"
#include "basicShaderResources.h"
#include "basicModelResources.h"
#include "ModelLibrary.h"
#include "tmpResources.h"

#include "bushes.h"
#include "gift.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

#include "modelLetters.h"

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

Scene* SceneBuilder::createScene(GLFWwindow* t_window) {
	std::lock_guard<std::mutex> lock(_mtx);

    // new empty scene
    int width, height;
    glfwGetWindowSize(t_window, &width, &height);

    this->m_scene = new Scene(new Camera(
        glm::vec3(0.f, 1.f, 10.f), // eye
        glm::vec3(0.f, 0.f, -1.f), // direction
        static_cast<float>(width) / static_cast<float>(height))); // aspect ratio

    this->m_shaderFactory = this->m_scene->getShaderFactory(); // for simplified data creation
    this->m_modelFactory = this->m_scene->getModelFactory();

    this->m_dimensions = glm::vec3(200.f, 100.f, 200.f); // default dimensions; x: 200 (-100..100); y: 100 (-0.1..100); z: 200 (-100..100)

    // fill the scene and bring it to life
    this->createContext();
    this->addContextToScene();

    this->m_scene->setAllCameras();

    return this->m_scene;
}

// --- private -----------------------------------------------------------------
SceneBuilder::SceneBuilder() {
	this->m_resourcesPath = AppUtils::getInstance()->getAppPath() + "/../resources/";
}

void SceneBuilder::createContext() {
    // create shaders and shader programs
    this->createBasicShaders();
    this->createShaders();

    this->createTemporaryShaders();

    // create models
    //this->createModels_01();
    //this->createModels_01();
    /*this->createScene_02_woods( // wooded area 100x100; 300 trees and 600 bushes
        glm::vec2(this->m_dimensions.x / 2.f, this->m_dimensions.z / 2.f),
        300);*/
    //this->createScene_03_illuminatedSpheres();

    this->createTemporaryScene();
}

void SceneBuilder::addContextToScene() {
	// add all (existing) models to the scene
    for (const auto& pair : *this->m_modelFactory->getModels()) {
        this->m_scene->addModel(pair.first, pair.second.get());
    }
}

// === shader factory ==========================================================
void SceneBuilder::createBasicShaders() {
    /* 1st task shaders */
    // vertex & fragment shaders
    this->m_shaderFactory->createVertexShader("basic_vshader", BASIC_VSHADER);
    this->m_shaderFactory->createFragmentShader("basic_fshader", BASIC_FSHADER);

    this->m_shaderFactory->createVertexShader("basic_vshaderColorFromPosition", BASIC_VSHADER_COLORFROMPOSITION);
    this->m_shaderFactory->createFragmentShader("basic_fshaderColorFromPosition", BASIC_FSHADER_COLORFROMPOSITION);

    this->m_shaderFactory->createVertexShader("basic_vshaderColorData", BASIC_VSHADER_COLORDATA);
    this->m_shaderFactory->createFragmentShader("basic_fshaderColorData", BASIC_FSHADER_COLORDATA);

    this->m_shaderFactory->createFragmentShader("basic_fshaderYellow", BASIC_FSHADER_YELLOW);

    // shader programs
    this->m_shaderFactory->createShaderProgram("basic_shader",
        *this->m_shaderFactory->getShader("basic_vshader"),
        *this->m_shaderFactory->getShader("basic_fshader"));

    this->m_shaderFactory->createShaderProgram("basic_shaderColorFromPosition",
        *this->m_shaderFactory->getShader("basic_vshaderColorFromPosition"),
        *this->m_shaderFactory->getShader("basic_fshaderColorFromPosition"));

    this->m_shaderFactory->createShaderProgram("basic_shaderColorData",
        *this->m_shaderFactory->getShader("basic_vshaderColorData"),
        *this->m_shaderFactory->getShader("basic_fshaderColorData"));

    this->m_shaderFactory->createShaderProgram("basic_shaderYellow",
        *this->m_shaderFactory->getShader("basic_vshader"),
        *this->m_shaderFactory->getShader("basic_fshaderYellow"));
}

void SceneBuilder::createShaders() {
    /* 2nd task shaders */
    // vertex & fragment shaders; shader program
    this->m_shaderFactory->createVertexShader("vshaderViewProjection", VSHADER_VIEW_PROJECTION);
    this->m_shaderFactory->createFragmentShader("fshaderViewProjection", FSHADER_VIEW_PROJECTION);

    this->m_shaderFactory->createShaderProgram("shaderViewProjection",
        *this->m_shaderFactory->getShader("vshaderViewProjection"),
        *this->m_shaderFactory->getShader("fshaderViewProjection"));

    /* 3rd task shaders */
    // vertex & fragment shaders; shader program
    /*
    this->m_shaderFactory->createVertexShader("vshaderNormal", VSHADER_NORMAL);
    this->m_shaderFactory->createFragmentShader("fshaderLambertian", FSHADER_LAMBERTIAN);
    this->m_shaderFactory->createFragmentShader("fshaderPhong", FSHADER_PHONG);

    this->m_shaderFactory->createShaderProgram("shaderLambertian",
        *this->m_shaderFactory->getShader("vshaderNormal"),
        *this->m_shaderFactory->getShader("fshaderLambertian"));

    this->m_shaderFactory->createShaderProgram("shaderPhong",
        *this->m_shaderFactory->getShader("vshaderNormal"),
        *this->m_shaderFactory->getShader("fshaderPhong"));
    */
    this->m_shaderFactory->createShaderProgram("shaderLambertian", (this->m_resourcesPath + "03_vertexNormal.shader").c_str(), (this->m_resourcesPath + "03_fragmentLambertian.shader").c_str());
    this->m_shaderFactory->createShaderProgram("shaderPhong", (this->m_resourcesPath + "03_vertexNormal.shader").c_str(), (this->m_resourcesPath + "03_fragmentPhong.shader").c_str());
}

void SceneBuilder::createTemporaryShaders() {
    // vertex & fragment shaders; shader program
    /*
    this->m_shaderFactory->createVertexShader("vshaderTMP", VSHADER_TMP);
    this->m_shaderFactory->createFragmentShader("fshaderTMP", FSHADER_TMP);

    this->m_shaderFactory->createShaderProgram("shaderTMP",
        *this->m_shaderFactory->getShader("vshaderTMP"),
        *this->m_shaderFactory->getShader("fshaderTMP"));
    */
    this->m_shaderFactory->createShaderProgram("shaderTMP", (this->m_resourcesPath + "vertexTMP.shader").c_str(), (this->m_resourcesPath + "fragmentTMP.shader").c_str());
}

// === model factory ===========================================================
void SceneBuilder::createModels_01() {
    /* 1st task models */
    this->m_modelFactory->createVertexResources("1stTriangle", MODEL_TRIANGLE, ModelFactory::s_defaultBufferList);
    this->m_modelFactory->createVertexResources("1stTriangleColorData", MODEL_TRIANGLE_COLORDATA, ModelFactory::s_defaultPositionColorBufferList);
    this->m_modelFactory->createVertexResources("1stSquare", MODEL_SQUARE, ModelFactory::s_defaultBufferList);
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

    //this->m_modelFactory->createModel("1stTriangle", "basic_shader", "1stTriangle", 0, 3);
    //this->m_modelFactory->createModel("1stTriangleColorFromPosition", "basic_shaderColorFromPosition", "1stTriangle", 0, 3);
    this->m_modelFactory->createModel("1stTriangleColorData", "basic_shaderColorData", "1stTriangleColorData", 0, 3);
    this->m_modelFactory->createModel("1stSquare", "basic_shaderYellow", "1stSquare", 0, 6);
    this->m_modelFactory->createModel("1stPentagon", "basic_shader", "1stPentagon", 0, 15);

    // all at once; some vertex resources are created twice this way
    //this->m_modelFactory->createModel("1stTriangle", "basic_shader", MODEL_TRIANGLE, ModelFactory::s_defaultBufferList, 0, 3);
    //this->m_modelFactory->createModel("1stTriangleColorFromPosition", "basic_shaderColorFromPosition", MODEL_TRIANGLE, ModelFactory::s_defaultBufferList, 0, 3);
    //this->m_modelFactory->createModel("1stTriangleColorData", "basic_shaderColorData", MODEL_TRIANGLE_COLORDATA, ModelFactory::s_defaultPositionColorBufferList, 0, 3);
    //this->m_modelFactory->createModel("1stSquare", "basic_shaderYellow", MODEL_SQUARE, ModelFactory::s_defaultBufferList, 0, 6);
    //this->m_modelFactory->createModel("1stPentagon", "basic_shader", sizeof(PENTAGON_POINTS), PENTAGON_POINTS, ModelFactory::s_defaultBufferList, 0, 15);
}

void SceneBuilder::createModels_02() {
    /* 2nd task models */
    // first/also try with the 'defaultColorData' shader program
    this->m_modelFactory->createModel("2ndBushes", "shaderViewProjection", sizeof(bushes), bushes, ModelFactory::s_defaultPositionNormalBufferList, 0, 8730);
    this->m_modelFactory->createModel("2ndGift", "shaderViewProjection", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList, 0, 66624);
    this->m_modelFactory->createModel("2ndPlain", "shaderViewProjection", sizeof(plain), plain, ModelFactory::s_defaultPositionNormalBufferList, 0, 36);
    this->m_modelFactory->createModel("2ndSphere", "shaderViewProjection", sizeof(sphere), sphere, ModelFactory::s_defaultPositionNormalBufferList, 0, 17280);
    this->m_modelFactory->createModel("2ndSuziFlat", "shaderViewProjection", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424);
    this->m_modelFactory->createModel("2ndSuziSmooth", "shaderViewProjection", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424);
    this->m_modelFactory->createModel("2ndTree", "shaderViewProjection", sizeof(tree), tree, ModelFactory::s_defaultPositionNormalBufferList, 0, 92814);

    this->m_modelFactory->getModel("2ndBushes")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-9.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndGift")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-6.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndPlain")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-3.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndSphere")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(0.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndSuziFlat")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(3.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndSuziSmooth")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(6.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndTree")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(9.f, 0.f, 0.f)));

    // camera position; corresponding to the scene
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 1.f, 18.f),
        glm::vec3(0.f, 0.f, -1.f));
}

void SceneBuilder::createScene_02_woods(const glm::vec2 t_areaSize, const int t_numberOfTrees) {
    srand(static_cast<unsigned int>(time(0))); // seed random number generator

    /*// skybox
    this->m_modelFactory->createModel(
        "skybox",
        //"shaderViewProjection", MODEL_SKYBOX, ModelFactory::s_defaultPositionColorBufferList, 0, 216,
        "shaderLambertian", MODEL_SKYBOX, ModelFactory::s_defaultPositionColorBufferList, 0, 216,
        this->m_dimensions / glm::vec3(2.f, 1.f, 2.f), glm::vec3(0.f), glm::vec3(0.f));*/

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
            "shaderLambertian", "tree", 0, 92814,
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
            "shaderLambertian", "bushes", 0, 8730,
            scale, rotation, position);
    }

    // suzi
    this->m_modelFactory->createModel(
        "suziFlat",
        "shaderLambertian", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(-3.f, 1.5f, t_areaSize.y / 2.f + 3.f)); // -3 to the left, 3 ahead before the first tree

    this->m_modelFactory->createModel(
        "suziSmooth",
        "shaderLambertian", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(3.f, 1.5f, t_areaSize.y / 2.f + 3.f)); // 3 to the right, 3 ahead before the first tree

    // gift
    this->m_modelFactory->createModel(
		"gift",
		"shaderLambertian", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList, 0, 66624,
        glm::vec3(11.f), glm::vec3(0.f), glm::vec3( // to the center of the upper left corner; in the middle of the skybox and wooded area
            -t_areaSize.x / 2.f - (m_dimensions.x - t_areaSize.x) / 4.f,
            3.f,
            -t_areaSize.y / 2.f - (m_dimensions.z - t_areaSize.y) / 4.f));

    // light source
    this->m_scene->addLight("light01default", new Light(1, glm::vec3(0.f, 90.f, 190.f)));

    // camera position; corresponding to the scene
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 1.f, t_areaSize.y / 2.f + 10.f), // in the middle; 10 ahead before the first tree
        glm::vec3(0.f, 0.f, -1.f));
}

void SceneBuilder::createScene_03_illuminatedSpheres() {
    /*
    // skybox
    this->m_modelFactory->createModel(
        "skybox",
        "shaderViewProjection", MODEL_SKYBOX, ModelFactory::s_defaultPositionColorBufferList, 0, 216,
        this->m_dimensions / glm::vec3(2.f, 1.f, 2.f), glm::vec3(0.f), glm::vec3(0.f));
    */

    // spheres
    this->m_modelFactory->createVertexResources("sphere", sizeof(sphere), sphere, ModelFactory::s_defaultPositionNormalBufferList);

    this->m_modelFactory->createModel("sphere01", "shaderLambertian", "sphere", 0, 17280, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(2.f, 0.f, 0.f));
    this->m_modelFactory->createModel("sphere02", "shaderLambertian", "sphere", 0, 17280, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(0.f, 2.f, 0.f));
    this->m_modelFactory->createModel("sphere03", "shaderPhong", "sphere", 0, 17280, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-2.f, 0.f, 0.f));
    this->m_modelFactory->createModel("sphere04", "shaderPhong", "sphere", 0, 17280, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(0.f, -2.f, 0.f));

    // letters
    this->m_modelFactory->createVertexResources("letter_L", ModelLetters::getLetter(ModelLetters::LETTER_L), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_P", ModelLetters::getLetter(ModelLetters::LETTER_P), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_a", ModelLetters::getLetter(ModelLetters::LETTER_a), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_b", ModelLetters::getLetter(ModelLetters::LETTER_b), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_e", ModelLetters::getLetter(ModelLetters::LETTER_e), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_h", ModelLetters::getLetter(ModelLetters::LETTER_h), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_i", ModelLetters::getLetter(ModelLetters::LETTER_i), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_o", ModelLetters::getLetter(ModelLetters::LETTER_o), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_m", ModelLetters::getLetter(ModelLetters::LETTER_m), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_n", ModelLetters::getLetter(ModelLetters::LETTER_n), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_g", ModelLetters::getLetter(ModelLetters::LETTER_g), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_r", ModelLetters::getLetter(ModelLetters::LETTER_r), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_t", ModelLetters::getLetter(ModelLetters::LETTER_t), ModelFactory::s_defaultPositionNormalBufferList);

    float size = 0.1f;
    float offsetX = 13.f;
    float offsetY = 13.f;
    this->m_modelFactory->createModel("letter_L01", "shaderLambertian", "letter_L", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_L), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX),                                        size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_a01", "shaderLambertian", "letter_a", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_a), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1)),     size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_m01", "shaderLambertian", "letter_m", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_m), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 2), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_b01", "shaderLambertian", "letter_b", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_b), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 3), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_e01", "shaderLambertian", "letter_e", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_e), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 4), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_r01", "shaderLambertian", "letter_r", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_r), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 5), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_t01", "shaderLambertian", "letter_t", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_t), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 6), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_i01", "shaderLambertian", "letter_i", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_i), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 7), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_a02", "shaderLambertian", "letter_a", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_a), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 8), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_n01", "shaderLambertian", "letter_n", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_n), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 9), size * offsetY, 0.f));

    offsetX = -43.f;
    offsetY = -19.f;
    this->m_modelFactory->createModel("letter_P11", "shaderPhong", "letter_P", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX),                                        size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_h11", "shaderPhong", "letter_h", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1)),     size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_o11", "shaderPhong", "letter_o", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 2), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_n11", "shaderPhong", "letter_n", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 3), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_g11", "shaderPhong", "letter_g", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 4), size * offsetY, 0.f));

    // light sources
    this->m_scene->addLight("light01default", new Light(1, glm::vec3(0.f, 0.f, 0.f)));
    this->m_scene->addLight("light02", new Light(1, glm::vec3(-10.f, 0.f, 1.f)));
    //this->m_scene->addLight("light03", new Light(1, glm::vec3(3.f, 3.f, 3.f)));

    // camera position; corresponding to the scene
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 1.f, 11.f),
        glm::vec3(0.f, 0.f, -1.f));
}

void SceneBuilder::createTemporaryScene() {
    /*
    // skybox
    this->m_modelFactory->createModel(
        "skybox",
        "shaderViewProjection", MODEL_SKYBOX, ModelFactory::s_defaultPositionColorBufferList, 0, 216,
        this->m_dimensions / glm::vec3(2.f, 1.f, 2.f), glm::vec3(0.f), glm::vec3(0.f));
    */

    // models
    this->m_modelFactory->createVertexResources("tmpBushes", sizeof(bushes), bushes, ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("tmpGift", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("tmpPlain", sizeof(plain), plain, ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("tmpSphere", sizeof(sphere), sphere, ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("tmpSuziFlat", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("tmpSuziSmooth", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("tmpTree", sizeof(tree), tree, ModelFactory::s_defaultPositionNormalBufferList);

    this->m_modelFactory->createVertexResources("tmpWall", ModelLibrary::MODEL_BASIC_WALL, ModelFactory::s_defaultPositionNormalBufferList);

    //this->m_modelFactory->createModel("tmpBushes01", "shaderLambertian", "tmpBushes", 0, 8730,          glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-9.f, 0.f, 0.f));
    //this->m_modelFactory->createModel("tmpGift01", "shaderLambertian", "tmpGift", 0, 66624,             glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-6.f, 0.f, 0.f));
    //this->m_modelFactory->createModel("tmpPlain01", "shaderLambertian", "tmpPlain", 0, 36,              glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-3.f, 0.f, 0.f));
    //this->m_modelFactory->createModel("tmpSphere01", "shaderLambertian", "tmpSphere", 0, 17280,         glm::vec3(1.f), glm::vec3(0.f), glm::vec3(0.f, 0.f, 0.f));
    //this->m_modelFactory->createModel("tmpSuziFlat01", "shaderLambertian", "tmpSuziFlat", 0, 17424,     glm::vec3(1.f), glm::vec3(0.f), glm::vec3(3.f, 0.f, 0.f));
    //this->m_modelFactory->createModel("tmpSuziSmooth01", "shaderLambertian", "tmpSuziSmooth", 0, 17424, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(6.f, 0.f, 0.f));
    //this->m_modelFactory->createModel("tmpTree01", "shaderLambertian", "tmpTree", 0, 92814,             glm::vec3(1.f), glm::vec3(0.f), glm::vec3(9.f, 0.f, 0.f));

    this->m_modelFactory->createModel("tmpWall01", "shaderTMP", "tmpWall", 0, 6, glm::vec3(10.f), glm::vec3(0.f), glm::vec3(0.f));

    //this->m_modelFactory->getModel("tmpBushes01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-9.f, 0.f, 0.f)));
    //this->m_modelFactory->getModel("tmpGift01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-6.f, 0.f, 0.f)));
    //this->m_modelFactory->getModel("tmpPlain01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-3.f, 0.f, 0.f)));
    //this->m_modelFactory->getModel("tmpSphere01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(0.f, 0.f, 0.f)));
    //this->m_modelFactory->getModel("tmpSuziFlat01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(3.f, 0.f, 0.f)));
    //this->m_modelFactory->getModel("tmpSuziSmooth01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(6.f, 0.f, 0.f)));
    //this->m_modelFactory->getModel("tmpTree01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(9.f, 0.f, 0.f)));

    // light source
    Light* light = new Light(1, glm::vec3(8.f, 0.f, 3.f));
    light->setDirection(glm::vec3(-6.f, 0.f, -1.f));
    light->setSpotCutoff(0.9f);
    light->setDiffuseColor(glm::vec3(0.f, 0.f, 1.0f));
    light->setSpecularColor(glm::vec3(1.f, 0.f, 0.0f));
    this->m_scene->addLight("light01default", light);

    // camera position; corresponding to the scene
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 0.f, 20.f),
        glm::vec3(0.f, 0.f, -1.f));
}
