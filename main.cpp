#include "application/GLFWContext.h"
#include "EngineCore.h"

GLFWContext context;
EngineCore* GLFWContext::Core;

int main() {
	EngineCore Engine;
	GLFWContext::Core = &Engine;
	Engine.Time.set_gettime_callback(context.time_callback);

	float aspect_ratio = (float)(context.window_width / context.window_height);;
	Object* main_camera = Engine.Scene.CreateObject("main_camera");
	main_camera->AttachComponent(Engine.Scene.CreateComponent<Camera>("my_camera", aspect_ratio));
	Engine.Scene.MainCameraObject = main_camera;

	Object* my_cube = Engine.Scene.CreateObject("my_cube");
	my_cube->AttachComponent(Engine.Scene.CreateComponent<RigidBody>("my_cube_rigidbody"));
	my_cube->AttachComponent(Engine.Scene.CreateComponent<Mesh>("my_cube_mesh", "mesh/cube"));
	my_cube->AttachComponent(Engine.Scene.CreateComponent<Material>("my_cube_material"));
	my_cube->GetComponent<Material>()->SetShader(Engine.Scene.LoadResource<Shader>("shader/test", "shader/test"));

	Object* my_pyramid = Engine.Scene.CreateObject("my_pyramid");
	my_pyramid->AttachComponent(Engine.Scene.CreateComponent<RigidBody>("my_pyramid_rigidbody"));
	my_pyramid->AttachComponent(Engine.Scene.CreateComponent<Mesh>("my_pyramid_mesh", "mesh/pyramid"));
	my_pyramid->AttachComponent(Engine.Scene.CreateComponent<Material>("my_pyramid_material"));
	my_pyramid->GetComponent<Material>()->SetShader(Engine.Scene.LoadResource<Shader>("shader/test", "shader/test"));

	my_cube->GetComponent<Transform>()->translate(glm::fvec3(0.0f, -1.0f, -3.0f));
	my_pyramid->GetComponent<Transform>()->translate(glm::fvec3(0.0f, 0.0f, -3.0f));
	my_pyramid->GetComponent<Transform>()->rotate(glm::radians(180.0f), glm::fvec3(1.0f, 0.0f, 0.0f));

	my_cube->GetComponent<RigidBody>()->angular_acceleration = 45.0f;
	my_cube->GetComponent<RigidBody>()->rotation_axis = glm::fvec3(0.0f, 1.0f, 0.0);

	my_pyramid->GetComponent<RigidBody>()->angular_acceleration = 90.0f;
	my_pyramid->GetComponent<RigidBody>()->rotation_axis = glm::fvec3(0.0f, 1.0f, 0.0);

	bool toggle = true;
	while (!context.should_close()) {
		Engine.run_once();

		if (toggle && my_cube->GetComponent<RigidBody>()->angular_speed >= 180.0) {
			my_cube->GetComponent<RigidBody>()->angular_acceleration *= -1.0f;
			my_pyramid->GetComponent<RigidBody>()->angular_acceleration *= -1.0f;
			toggle = false;
		}
		else if (!toggle && my_cube->GetComponent<RigidBody>()->angular_speed <= -180.0) {
			my_cube->GetComponent<RigidBody>()->angular_acceleration *= -1.0f;
			my_pyramid->GetComponent<RigidBody>()->angular_acceleration *= -1.0f;
			toggle = true;
		}

		context.swap_buffers();
		context.poll_events();
	}
}