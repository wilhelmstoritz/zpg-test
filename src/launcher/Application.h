#pragma once

// GLEW
#include <GL/glew.h>

// GLFW
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
	void addScene(Scene* t_scene);

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

	enum exitE {
		EXIT_CONTINUE = -1,
		EXIT = 0,

		EXIT_1 = 1, // scene '1' to be loaded
		EXIT_2 = 2,	// ...
		EXIT_3 = 3,
		EXIT_4 = 4,
		EXIT_5 = 5,
		EXIT_6 = 6,
		EXIT_7 = 7,
		EXIT_8 = 8,
		EXIT_9 = 9
	};

	GLFWwindow* m_window;
	int m_windowXpos, m_windowYpos;

	std::unordered_map<std::string, Scene*> m_scenes;
	Scene* m_scene; // current scene
	Controller* m_controller;
	Renderer* m_renderer;

	exitE m_exitCode;

	void initWindow();
	void updateViewport();

	void showVersionInfo();
	void showSplashScreen();
};
