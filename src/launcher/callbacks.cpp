#include "callbacks.h"

// include the standard C++ headers
#include <stdio.h>

// --- callbacks ---------------------------------------------------------------
void callbackError(int t_error, const char* t_description) { fputs(t_description, stderr); }

void callbackKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) {
	if (t_key == GLFW_KEY_ESCAPE && t_action == GLFW_PRESS)
		glfwSetWindowShouldClose(t_window, GL_TRUE);

	printf("callback:key [key: %d, scancode: %d, action: %d, mods: %d]\n", t_key, t_scancode, t_action, t_mods);
}

void callbackWindowFocus(GLFWwindow* t_window, int t_focused) { printf("callback:window_focus\n"); }

void callbackWindowIconify(GLFWwindow* t_window, int t_iconified) { printf("callback:window_iconify\n"); }

void callbackWindowSize(GLFWwindow* t_window, int t_width, int t_height) {
	glViewport(0, 0, t_width, t_height);

	printf("callback:window_size %d, %d\n", t_width, t_height);
}

void callbackCursor(GLFWwindow* t_window, double t_x, double t_y) { printf("callback:cursor\n"); }

void callbackButton(GLFWwindow* t_window, int t_button, int t_action, int t_mode) {
	if (t_action == GLFW_PRESS) printf("callback:button [%d,%d,%d]\n", t_button, t_action, t_mode);
}
