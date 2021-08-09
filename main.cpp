#include "EngineCore.h"

int main() {
	/* Engine start up */
	unsigned int window_width = 800;
	unsigned int window_height = 600;
	float aspect_ratio = (float)window_width / (float)window_height;
	EngineCore Engine(window_width, window_height);

	/* Setting up the scene */
	GameObject* main_camera = Engine.Scene.CreateObject("main_camera");
	main_camera->AttachComponent(Engine.Scene.CreateComponent<Camera>("main_camera_component", aspect_ratio));
	Engine.Scene.MainCameraObject = main_camera;

	GameObject* my_cube = Engine.Scene.CreateObject("my_cube");
	my_cube->AttachComponent(Engine.Scene.CreateComponent<RigidBody>("my_cube_rigidbody"));
	my_cube->AttachComponent(Engine.Scene.CreateComponent<Mesh>("my_cube_mesh", "mesh/cube"));
	my_cube->AttachComponent(Engine.Scene.CreateComponent<Material>("my_cube_material"));
	my_cube->GetComponent<Material>()->SetShader(Engine.Scene.LoadResource<Shader>("shader/test", "shader/test"));
	my_cube->GetComponent<Transform>()->translate(glm::fvec3(0.0f, -1.0f, -5.0f));
	my_cube->GetComponent<RigidBody>()->angular_acceleration = 45.0f;
	my_cube->GetComponent<RigidBody>()->rotation_axis = glm::fvec3(0.0f, 1.0f, 0.0);

	GameObject* my_pyramid = Engine.Scene.CreateObject("my_pyramid");
	my_pyramid->AttachComponent(Engine.Scene.CreateComponent<RigidBody>("my_pyramid_rigidbody"));
	my_pyramid->AttachComponent(Engine.Scene.CreateComponent<Mesh>("my_pyramid_mesh", "mesh/pyramid"));
	my_pyramid->AttachComponent(Engine.Scene.CreateComponent<Material>("my_pyramid_material"));
	my_pyramid->GetComponent<Material>()->SetShader(Engine.Scene.LoadResource<Shader>("shader/test", "shader/test"));
	my_pyramid->GetComponent<Transform>()->translate(glm::fvec3(0.0f, 0.0f, -5.0f));
	my_pyramid->GetComponent<RigidBody>()->angular_acceleration = 90.0f;
	my_pyramid->GetComponent<RigidBody>()->rotation_axis = glm::fvec3(0.0f, 1.0f, 0.0);

	/* Simulating some dynamic behaviour of the scene */
	bool toggle = true;
	while (!Engine.App.should_close()) {
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
		Engine.App.swap_buffers();
		Engine.App.poll_events();
	}
}