#ifndef H_RENDERINGMODULE
#define H_RENDERINGMODULE

#include "../EngineCore.h"
#include "../GameObject.h"

template<typename RendererType>
class RenderingModule {
public:
	EngineCore* const Core;

	RenderingModule(EngineCore* core) :
		Core(core) {
		Renderer.setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	}

	void render() {
		Renderer.clear();
		GameObject* camera = Core->Scene.MainCameraObject;
		for (auto it = Core->Scene.Objects.cbegin<GameObject>(); it != Core->Scene.Objects.cend<GameObject>(); ++it) {
			if (it->second.get()->HasComponent<Mesh>() && it->second.get()->HasComponent<Material>()) {
				Renderer.render(it->second.get(), camera);
			}
		}
	}

private:
	RendererType Renderer;
};

#endif