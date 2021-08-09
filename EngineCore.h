#ifndef H_ENGINECORE
#define H_ENGINECORE

#include "engine_modules/InputModule.h"
#include "engine_modules/TimeModule.h"
#include "engine_modules/PhysicsModule.h"
#include "engine_modules/RenderingModule.h"
#include "engine_modules/RendererOpenGL.h"
#include "engine_modules/SceneManager.h"

#include "components/Transform.h"
#include "components/RigidBody.h"
#include "components/Camera.h"
#include "components/Material.h"
#include "components/Mesh.h"

#include "Object.h"
#include "Shader.h"

class EngineCore {
public:
	InputModule Input;
	TimeModule Time;
	RenderingModule<RendererOpenGL> Renderer;
	PhysicsModule Physics;
	SceneManager Scene;

	EngineCore() :
		Input(this),
		Time(this),
		Renderer(this),
		Physics(this),
		Scene(this) {
	}

	void run_once() {
		Time.update();
		Physics.simulate();
		Renderer.render();
	}
};

#endif