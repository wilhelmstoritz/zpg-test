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
    if (_instance == nullptr)
        //_instance = new SceneBuilder();
        _instance.reset(new SceneBuilder());

    //return _instance;
    return _instance.get();
}

Scene* SceneBuilder::createScene(const std::string& t_name, SceneBuilderPlugin* t_sceneBuilderPlugin) {
	return this->createScene<Scene>(t_name, t_sceneBuilderPlugin);
}
