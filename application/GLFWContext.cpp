#include "GLFWContext.h"
#include "../EngineCore.h"

GLFWContext::GLFWContext(EngineCore* core, unsigned int window_width, unsigned int window_height) :
	m_window(nullptr),
	m_window_width(window_width),
	m_window_height(window_height) {
	Core = core;
	init();
}

GLFWContext::~GLFWContext() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool GLFWContext::init() {
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		return false;
	}
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	m_window = glfwCreateWindow(m_window_width, m_window_height, "Graphics Application", nullptr, nullptr);
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

bool GLFWContext::should_close() const {
	return glfwWindowShouldClose(m_window);
}

void GLFWContext::swap_buffers() const {
	glfwSwapBuffers(m_window);
}

void GLFWContext::poll_events() const {
	glfwPollEvents();
}

double GLFWContext::time_callback() {
	return glfwGetTime();
}

void GLFWContext::error_callback(int error, const char* description) {
}

void GLFWContext::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Core->Input.handle_input(key, scancode, action, mods);
}

void GLFWContext::cursor_callback(GLFWwindow* window, double xpos, double ypos) {
}