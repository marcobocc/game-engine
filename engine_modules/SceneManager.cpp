#include "SceneManager.h"
#include "../EngineCore.h"
#include "../Object.h"

SceneManager::SceneManager(EngineCore* core) :
	Core(core),
	MainCameraObject(nullptr) {
}

Object* SceneManager::CreateObject(std::string object_name) {
	auto [object_iter, is_new_object] = Objects.try_alloc<Object>(object_name);
	Object* object = object_iter->second.get();
	if (is_new_object) {
		Transform* default_transform = CreateComponent<Transform>(object_name + "_transform");
		object->AttachComponent<Transform>(default_transform);
	}
	return object;
}