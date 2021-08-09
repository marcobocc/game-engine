#ifndef H_RENDERINGMODULE
#define H_RENDERINGMODULE

#include "../EngineCore.h"
#include "../Object.h"

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
		Object* camera = Core->Scene.MainCameraObject;
		for (auto it = Core->Scene.Objects.cbegin<Object>(); it != Core->Scene.Objects.cend<Object>(); ++it) {
			if (it->second.get()->HasComponent<Mesh>() && it->second.get()->HasComponent<Material>()) {
				Renderer.render(it->second.get(), camera);
			}
		}
	}

private:
	RendererType Renderer;
};

#endif