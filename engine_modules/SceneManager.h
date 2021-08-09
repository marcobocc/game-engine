#ifndef H_SCENEMANAGER
#define H_SCENEMANAGER

#include "../BaseManager.h"
#include <string>

class EngineCore;
class GameObject;
class Transform;
class RigidBody;
class Camera;
class Material;
class Mesh;
class Shader;

class SceneManager {
public:
	EngineCore* const Core;
	BaseManager<std::string, GameObject> Objects;
	BaseManager<std::string, Transform, RigidBody, Camera, Material, Mesh> Components;
	BaseManager<std::string, Shader> Resources;
	GameObject* MainCameraObject;

	SceneManager(EngineCore* core);

	GameObject* CreateObject(std::string object_name);

	template<typename ComponentType, typename... Args>
	ComponentType* CreateComponent(std::string component_name, Args&&... args) {
		auto [component_iter, is_new_component] = Components.try_alloc<ComponentType>(component_name, std::forward<Args>(args)...);
		return component_iter->second.get();
	}

	template<typename ResourceType, typename... Args>
	ResourceType* LoadResource(std::string resource_name, Args&&... args) {
		auto [resource_iter, is_new_component] = Resources.try_alloc<ResourceType>(resource_name, std::forward<Args>(args)...);
		return resource_iter->second.get();
	}
};

#endif