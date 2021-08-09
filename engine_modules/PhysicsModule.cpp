#include "PhysicsModule.h"
#include "../EngineCore.h"
#include "../GameObject.h"

PhysicsModule::PhysicsModule(EngineCore* core) :
	Core(core) {
}

void PhysicsModule::simulate() {
	double deltaTime = Core->Time.deltaTime();
	for (auto it = Core->Scene.Objects.cbegin<GameObject>(); it != Core->Scene.Objects.cend<GameObject>(); ++it) {
		GameObject* object = it->second.get();
		if (object->HasComponent<RigidBody>()) {
			object->GetComponent<RigidBody>()->update(object->GetComponent<Transform>(), (float)deltaTime);
		}
	}
}