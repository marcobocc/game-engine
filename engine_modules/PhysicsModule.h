#ifndef H_PHYSICSMODULE
#define H_PHYSICSMODULE

class EngineCore;

class PhysicsModule {
public:
	EngineCore* const Core;

	PhysicsModule(EngineCore* core);

	void simulate();
};

#endif