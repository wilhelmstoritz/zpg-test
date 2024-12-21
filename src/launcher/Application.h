#pragma once

// include GLEW
#include <GL/glew.h>
// include GLFW
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <mutex>
#include <unordered_map>

#include "Scene.h"
#include "SceneBuilder.h"
#include "ObserverSubject.h"
#include "Controller.h"
#include "Renderer.h"

class Application {
public:
	static Application* getInstance();
	~Application();

	void addScene(const std::string& t_name, Scene* t_scene);

	Scene* getScene(const std::string& t_name) const;

	void setScene(Scene* t_scene);
	void setScene(const std::string& t_name);

	void run();

	void callbackDispatcherFramebufferSize(GLFWwindow* t_window, int t_width, int t_height);
	void callbackDispatcherKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods);

private:
	// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - -
	// private constructor to avoid creating multiple instances
	Application();

	// disable copy constructor and assignment operator
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	// a singleton instance pointer
	//static Application* _instance;
	static std::unique_ptr<Application> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	GLFWwindow* m_window;

	std::unordered_map<std::string, Scene*> m_scenes;
	Scene* m_scene; // current scene
	Controller* m_controller;
	Renderer* m_renderer;

	int m_windowXpos, m_windowYpos;

	void initWindow();
	void versionInfo();
};
