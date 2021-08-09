#ifndef H_CAMERA
#define H_CAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	Camera(float aspect_ratio) :
		m_aspect_ratio(aspect_ratio) {
	}

	glm::fmat4 get_proj_transform() const {
		return glm::perspective(glm::radians(60.0f), m_aspect_ratio, 0.1f, 100.0f);
	}

private:
	float m_aspect_ratio;
};

#endif