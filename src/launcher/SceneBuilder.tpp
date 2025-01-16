#include "SceneBuilder.h"

// === template implementation =================================================
// --- public ------------------------------------------------------------------
template <typename T>
T* SceneBuilder::createScene(const std::string& t_name, SceneBuilderPlugin* t_sceneBuilderPlugin) {
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene"); // check if T is derived from Scene; if not, the compilation will fail

	// new empty scene
	T* scene = new T(t_name, new Camera("camera:default",
		glm::vec3(0.f, 0.f,  1.f),   // eye
		glm::vec3(0.f, 0.f, -1.f))); // direction

	// fill the scene and bring it to life
	t_sceneBuilderPlugin->setSceneProperties(scene);
	t_sceneBuilderPlugin->createContext(scene);
	scene->setAllCameras();
	scene->setAllLights();

	// cleanup
	delete t_sceneBuilderPlugin;

	return scene;
}
