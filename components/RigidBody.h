#ifndef H_RIGIDBODY
#define H_RIGIDBODY

#include "Transform.h"
#include <glm/glm.hpp>

class RigidBody {
public:
	float angular_speed;
	float angular_acceleration;
	glm::fvec3 rotation_axis;
	glm::fvec3 linear_velocity;
	glm::fvec3 linear_acceleration;

	RigidBody() :
		angular_speed(0.0f),
		angular_acceleration(0.0f),
		rotation_axis(0.0f),
		linear_velocity(0.0f),
		linear_acceleration(0.0f) {
	}

	void update(Transform* transform, float deltaTime) {
		if (transform) {
			angular_speed += angular_acceleration * deltaTime;
			if (angular_speed != 0.0f && rotation_axis != glm::fvec3(0.0f)) {
				transform->rotate(glm::radians(angular_speed * deltaTime), rotation_axis);
			}
			linear_velocity += linear_acceleration * deltaTime;
			if (linear_velocity != glm::fvec3(0.0f)) {
				transform->translate(linear_velocity * deltaTime);
			}
		}
	}
};

#endif