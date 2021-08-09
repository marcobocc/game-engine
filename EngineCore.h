#ifndef H_ENGINECORE
#define H_ENGINECORE

#include "application/GLFWContext.h"
#include "engine_modules/InputModule.h"
#include "engine_modules/TimeModule.h"
#include "engine_modules/PhysicsModule.h"
#include "engine_modules/RenderingModule.h"
#include "engine_modules/RendererOpenGL.h"
#include "engine_modules/SceneManager.h"

#include "GameObject.h"
#include "Shader.h"

class EngineCore {
public:
	GLFWContext App;
	InputModule Input;
	TimeModule Time;
	RenderingModule<RendererOpenGL> Renderer;
	PhysicsModule Physics;
	SceneManager Scene;

	EngineCore(unsigned int window_width, unsigned int window_height) :
		App(this, window_width, window_height),
		Input(this),
		Time(this),
		Renderer(this),
		Physics(this),
		Scene(this) {
		Time.set_gettime_callback(App.time_callback);
	}

	void run_once() {
		Time.update();
		Physics.simulate();
		Renderer.render();
	}
};

#endif