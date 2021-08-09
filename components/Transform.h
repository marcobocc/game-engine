#ifndef H_TRANSFORM
#define H_TRANSFORM

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform
{
public:
	Transform() :
		m_transform_matrix(1.0f),
		m_translation(0.0f),
		m_rotation(1.0f, 0.0f, 0.0f, 0.0f),
		m_scale(1.0f) {
	}

	void scale(glm::fvec3 scale) {
		m_scale = m_scale * scale;
		m_transform_matrix = glm::scale(m_transform_matrix, m_scale);
	}

	void set_scale(glm::fvec3 scale) {
		m_scale = scale;
		m_transform_matrix = glm::scale(m_transform_matrix, m_scale);
	}

	void rotate(float angle, glm::fvec3 axis) {
		rotate(glm::angleAxis(angle, axis));
	}

	void rotate(glm::fquat rotation) {
		m_rotation = m_rotation * rotation;
		m_rotation = glm::normalize(m_rotation);
		m_transform_matrix = glm::translate(glm::fmat4(1.0f), m_translation);
		m_transform_matrix = glm::rotate(m_transform_matrix, glm::angle(m_rotation), glm::axis(m_rotation));
		m_transform_matrix = glm::scale(m_transform_matrix, m_scale);
	}

	void set_rotation(float angle, glm::fvec3 axis) {
		set_rotation(glm::angleAxis(angle, axis));
	}

	void set_rotation(glm::fquat rotation) {
		m_rotation = rotation;
		m_rotation = glm::normalize(m_rotation);
		m_transform_matrix = glm::translate(glm::fmat4(1.0f), m_translation);
		m_transform_matrix = glm::rotate(m_transform_matrix, glm::angle(m_rotation), glm::axis(m_rotation));
		m_transform_matrix = glm::scale(m_transform_matrix, m_scale);
	}

	void translate(glm::fvec3 offset) {
		m_transform_matrix = glm::translate(glm::fmat4(1.0f), offset) * m_transform_matrix;
		m_translation = m_translation + offset;
	}

	void set_translation(glm::fvec3 position) {
		glm::fvec3 offset = position - m_translation;
		m_transform_matrix = glm::translate(glm::fmat4(1.0f), offset) * m_transform_matrix;
		m_translation = position;
	}

	void reset() {
		m_transform_matrix = glm::fmat4(1.0f);
		m_translation = glm::fvec3(0.0f);
		m_rotation = glm::fquat(1.0f, 0.0f, 0.0f, 0.0f);
		m_scale = glm::fvec3(1.0f);
	}

	glm::fmat4 to_matrix() const {
		return m_transform_matrix;
	}

	glm::fvec3 right() const {
		return glm::normalize(m_rotation * glm::fvec3(1.0f, 0.0f, 0.0f));
	}

	glm::fvec3 up() const {
		return glm::normalize(m_rotation * glm::fvec3(0.0f, 1.0f, 0.0f));
	}

	glm::fvec3 forward() const {
		return glm::normalize(m_rotation * glm::fvec3(0.0f, 0.0f, 1.0f));
	}

	glm::fvec3 position() const {
		return m_translation;
	}

	glm::fvec3 scale() const {
		return m_scale;
	}

	glm::fquat rotation() const {
		return m_rotation;
	}

private:
	glm::fmat4 m_transform_matrix;
	glm::fvec3 m_translation;
	glm::fquat m_rotation;
	glm::fvec3 m_scale;
};

#endif