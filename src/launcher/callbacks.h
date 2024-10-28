#pragma once

// include GLFW
#include <GLFW/glfw3.h>

void callbackError(int t_error, const char* t_description);
void callbackKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods);
void callbackWindowFocus(GLFWwindow* t_window, int t_focused);
void callbackWindowIconify(GLFWwindow* t_window, int t_iconified);
void callbackWindowSize(GLFWwindow* t_window, int t_width, int t_height);
void callbackCursor(GLFWwindow* t_window, double t_x, double t_y);
void callbackButton(GLFWwindow* t_window, int t_button, int t_action, int t_mode);
