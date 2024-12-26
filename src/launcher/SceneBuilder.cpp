#include "SceneBuilder.h"
#include "AppUtils.h"

#include "SceneBuilderPluginEmptyScene.h"

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

Scene* SceneBuilder::createScene(const std::string& t_name, SceneBuilderPlugin* t_sceneBuilderPlugin) {
    // new empty scene
    Scene* scene = new Scene(t_name, new Camera("default",
        glm::vec3(0.f, 0.f,  1.f),   // eye
        glm::vec3(0.f, 0.f, -1.f))); // direction

    // fill the scene and bring it to life
	t_sceneBuilderPlugin->createContext(scene);
    scene->setAllCameras();
	scene->setAllLights();

	// cleanup
	delete t_sceneBuilderPlugin;

    return scene;
}
