#ifndef H_GLFWCONTEXT
#define H_GLFWCONTEXT

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class EngineCore;

class GLFWContext {
public:
	inline static EngineCore* Core;

	GLFWContext(EngineCore* core, unsigned int window_width, unsigned int window_height);

	~GLFWContext();

	bool init();

	bool should_close() const;

	void swap_buffers() const;

	void poll_events() const;

	static double time_callback();

	static void error_callback(int error, const char* description);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void cursor_callback(GLFWwindow* window, double xpos, double ypos);

private:
	GLFWwindow* m_window;
	unsigned int m_window_width;
	unsigned int m_window_height;
};

#endif