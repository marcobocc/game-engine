#include "SceneManager.h"
#include "../EngineCore.h"
#include "../GameObject.h"

SceneManager::SceneManager(EngineCore* core) :
	Core(core),
	MainCameraObject(nullptr) {
}

GameObject* SceneManager::CreateObject(std::string object_name) {
	auto [object_iter, is_new_object] = Objects.try_alloc<GameObject>(object_name);
	GameObject* object = object_iter->second.get();
	if (is_new_object) {
		Transform* default_transform = CreateComponent<Transform>(object_name + "_transform");
		object->AttachComponent<Transform>(default_transform);
	}
	return object;
}