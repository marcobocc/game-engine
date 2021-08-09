#ifndef H_GLFWCONTEXT
#define H_GLFWCONTEXT

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../EngineCore.h"

class GLFWContext {
public:
	static EngineCore* Core;
	static const unsigned int window_width = 800;
	static const unsigned int window_height = 600;

	GLFWContext() {
		init();
	}

	~GLFWContext() {
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	bool init() {
		glfwSetErrorCallback(error_callback);
		if (!glfwInit()) {
			return false;
		}
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		m_window = glfwCreateWindow(window_width, window_height, "Graphics Application", nullptr, nullptr);
		if (glfwGetError(0) != GLFW_NO_ERROR) {
			glfwTerminate();
			return false;
		}
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetCursorPosCallback(m_window, cursor_callback);
		glfwMakeContextCurrent(m_window);
		if (glewInit() != GLEW_OK) {
			glfwTerminate();
			return false;
		}
		return true;
	}

	bool should_close() const {
		return glfwWindowShouldClose(m_window);
	}

	void swap_buffers() const {
		glfwSwapBuffers(m_window);
	}

	void poll_events() const {
		glfwPollEvents();
	}

	static double time_callback() {
		return glfwGetTime();
	}

	static void error_callback(int error, const char* description) {
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Core->Input.handle_input(key, scancode, action, mods);
	}

	static void cursor_callback(GLFWwindow* window, double xpos, double ypos) {
	}

private:
	GLFWwindow* m_window;
};

#endif