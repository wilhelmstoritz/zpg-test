#include "SceneBuilder.h"
#include "AppUtils.h"

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

    this->m_scene = new Scene(new Camera("default",
        glm::vec3(0.f, 1.f, 10.f), // eye
        glm::vec3(0.f, 0.f, -1.f), // direction
        static_cast<float>(width) / static_cast<float>(height))); // aspect ratio

    this->m_shaderFactory = this->m_scene->getShaderFactory(); // for simplified data creation
    this->m_modelFactory = this->m_scene->getModelFactory();

    // fill the scene and bring it to life
    this->createContext();
    this->addContextToScene();

    this->m_scene->setAllCameras();

    return this->m_scene;
}

// --- private -----------------------------------------------------------------
SceneBuilder::SceneBuilder() {
    this->m_resourcesPath = AppUtils::getInstance()->getResourcesPath() + "shaders.glsl/";

    // to prevent visual studio warnings; value(s) will be set later
    this->m_scene = nullptr;
    this->m_shaderFactory = nullptr;
    this->m_modelFactory = nullptr;
}

void SceneBuilder::createContext() {
    // create shaders and shader programs
    this->createBasicShaders();
    this->createShaders();

    this->createTemporaryShaders();

    // create models
    //this->createModels_01();
    //this->createModels_02();
    //this->createScene_02_woods();
    //this->createScene_03_illuminatedSpheres();
    this->createScene_04_magicWoods();

    //this->createTemporaryScene(); //!
}

void SceneBuilder::addContextToScene() {
	// add all (existing) models to the scene
    for (const auto& pair : *this->m_modelFactory->getModels()) {
        this->m_scene->addModel(pair.first, pair.second.get());
    }
}
