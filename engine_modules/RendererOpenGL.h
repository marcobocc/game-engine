#ifndef H_RENDERER
#define H_RENDERER

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>
#include "../GameObject.h"

class RendererOpenGL {
public:
	RendererOpenGL() :
		m_lastRendered(nullptr),
		m_mvTransform_location(0),
		m_projTransform_location(0) {
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	~RendererOpenGL() {
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ebo);
	}

	void setClearColor(float r, float g, float b, float a) const {
		glClearColor(r, g, b, a);
	}

	void clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void render(GameObject* object, GameObject* camera) {
		bool new_shader = true;
		bool new_mesh = true;
		if (m_lastRendered) {
			if (object->GetComponent<Material>()->GetShader() == m_lastRendered->GetComponent<Material>()->GetShader()) {
				new_shader = false;
			}
			if (object->GetComponent<Mesh>() == m_lastRendered->GetComponent<Mesh>()) {
				new_mesh = false;
			}
		}
		glm::mat4 mvTransform = camera->GetComponent<Transform>()->to_matrix() * object->GetComponent<Transform>()->to_matrix();
		if (new_shader) {
			GLuint shader_program = object->GetComponent<Material>()->GetShader()->get_program();
			glUseProgram(shader_program);
			m_mvTransform_location = glGetUniformLocation(shader_program, "mvTransform");
			m_projTransform_location = glGetUniformLocation(shader_program, "projTransform");
			glm::mat4 projTransform = camera->GetComponent<Camera>()->get_proj_transform();
			glUniformMatrix4fv(m_projTransform_location, 1, GL_FALSE, glm::value_ptr(projTransform));
		}
		glUniformMatrix4fv(m_mvTransform_location, 1, GL_FALSE, glm::value_ptr(mvTransform));
		if (new_mesh) {
			glBindVertexArray(m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * object->GetComponent<Mesh>()->m_vertices.size(), object->GetComponent<Mesh>()->m_vertices.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(int) * object->GetComponent<Mesh>()->m_indices.size(), object->GetComponent<Mesh>()->m_indices.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}
		glDrawElements(GL_TRIANGLES, (GLsizei)(3 * object->GetComponent<Mesh>()->m_indices.size()), GL_UNSIGNED_INT, 0);
		m_lastRendered = object;
	}

private:
	GameObject* m_lastRendered;
	GLint m_mvTransform_location;
	GLint m_projTransform_location;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
};

#endif