#pragma once

// . . macos platform  . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION // avoids "warning: 'glViewport' is deprecated: first deprecated in macOS 10.14 - OpenGL API deprecated."
#endif
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// glfw
#include <GLFW/glfw3.h>

void callbackError(int t_error, const char* t_description);

void callbackWindowFocus(GLFWwindow* t_window, int t_focused);
void callbackWindowIconify(GLFWwindow* t_window, int t_iconified);
void callbackFramebufferSize(GLFWwindow* t_window, int t_width, int t_height);

void callbackKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods);
void callbackButton(GLFWwindow* t_window, int t_button, int t_action, int t_mode);
void callbackCursor(GLFWwindow* t_window, double t_x, double t_y);
