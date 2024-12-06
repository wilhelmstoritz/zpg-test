#include "SceneBuilder.h"
#include "AppUtils.h"

#include "SceneBuilderPlugin_emptyScene.h"

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//SceneBuilder* SceneBuilder::_instance = nullptr;
std::unique_ptr<SceneBuilder> SceneBuilder::_instance = nullptr;
std::mutex SceneBuilder::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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

SceneBuilder::~SceneBuilder() {
    delete this->m_sceneBuilderPlugin;
}

void SceneBuilder::setPlugin(SceneBuilderPlugin* t_sceneBuilderPlugin) {
	delete this->m_sceneBuilderPlugin;

    this->m_sceneBuilderPlugin = t_sceneBuilderPlugin;
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

    // fill the scene and bring it to life
	this->m_sceneBuilderPlugin->createContext(this->m_scene);
    this->m_scene->setAllCameras();

    return this->m_scene;
}

// --- private -----------------------------------------------------------------
SceneBuilder::SceneBuilder() {
	this->m_sceneBuilderPlugin = new SceneBuilderPlugin_emptyScene();

    // to prevent visual studio warnings; value(s) will be set later
    this->m_scene = nullptr;
}
