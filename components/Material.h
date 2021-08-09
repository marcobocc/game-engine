#ifndef H_MATERIAL
#define H_MATERIAL

#include <string>
#include "../Shader.h"

class Material {
public:
	Material() : m_shader(nullptr) {
	}

	void SetShader(Shader* shader) {
		m_shader = shader;
	}

	Shader* GetShader() const {
		return m_shader;
	}

private:
	Shader* m_shader;
};

#endif