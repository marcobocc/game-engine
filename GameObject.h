#ifndef H_GAMEOBJECT
#define H_GAMEOBJECT

#include <tuple>
#include "components/Transform.h"
#include "components/RigidBody.h"
#include "components/Camera.h"
#include "components/Material.h"
#include "components/Mesh.h"

class GameObject {
public:
	template<typename ComponentType>
	void AttachComponent(ComponentType* component) {
		std::get<ComponentType*>(Components) = component;
	}

	template<typename ComponentType>
	void RemoveComponent() {
		std::get<ComponentType*>(Components) = nullptr;
	}

	template<typename ComponentType>
	ComponentType* GetComponent() {
		return std::get<ComponentType*>(Components);
	}

	template<typename ComponentType>
	bool HasComponent() {
		return (std::get<ComponentType*>(Components) != nullptr);
	}

private:
	std::tuple<Transform*, RigidBody*, Camera*, Material*, Mesh*> Components;
};

#endif