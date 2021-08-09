#ifndef H_MESH
#define H_MESH

#include <glm/glm.hpp>
#include <vector>
#include <string>

class Mesh {
public:
	Mesh(std::string mesh_name) {
		STUB_load_mesh(mesh_name);
	}

	std::vector<glm::fvec3> m_vertices;
	std::vector<glm::ivec3> m_indices;

private:

	void STUB_load_mesh(std::string mesh_name) {
		std::pair<std::vector<glm::fvec3>, std::vector<glm::ivec3>> mesh_data;
		if (mesh_name == "mesh/pyramid") {
			mesh_data = STUB_pyramid();
		}
		else if (mesh_name == "mesh/cube") {
			mesh_data = STUB_cube();
		}
		else {
			mesh_data = STUB_empty();
		}
		m_vertices = mesh_data.first;
		m_indices = mesh_data.second;
	}

	std::pair<std::vector<glm::fvec3>, std::vector<glm::ivec3>> STUB_pyramid() {
		std::vector<glm::fvec3> vertices = {
			glm::fvec3(0.0f,  +0.5f, 0.0f),
			glm::fvec3(0.5f, -0.5f, -0.5f),
			glm::fvec3(-0.5f, -0.5f, -0.5f),
			glm::fvec3(-0.5f, -0.5f, 0.5f),
			glm::fvec3(0.5f, -0.5f, 0.5f)
		};
		std::vector<glm::ivec3> indices = {
			glm::ivec3(0, 1, 2),
			glm::ivec3(0, 4, 1),
			glm::ivec3(0, 3, 4),
			glm::ivec3(0, 2, 3),
			glm::ivec3(3, 2, 1),
			glm::ivec3(3, 1, 4)
		};
		return std::pair<std::vector<glm::fvec3>, std::vector<glm::ivec3>>(vertices, indices);
	}

	std::pair<std::vector<glm::fvec3>, std::vector<glm::ivec3>> STUB_cube() {
		std::vector<glm::fvec3> vertices = {
			glm::fvec3(-0.5f, -0.5f, 0.5f),
			glm::fvec3(0.5f, -0.5f, 0.5f),
			glm::fvec3(0.5f, 0.5f, 0.5f),
			glm::fvec3(-0.5f, 0.5f, 0.5f),
			glm::fvec3(-0.5f, -0.5f, -0.5f),
			glm::fvec3(0.5f, -0.5f, -0.5f),
			glm::fvec3(0.5f, 0.5f, -0.5f),
			glm::fvec3(-0.5f, 0.5f, -0.5f)
		};
		std::vector<glm::ivec3> indices = {
			glm::ivec3(3, 2, 6),
			glm::ivec3(6, 7, 3),
			glm::ivec3(0, 1, 2),
			glm::ivec3(2, 3, 0),
			glm::ivec3(1, 5, 6),
			glm::ivec3(6, 2, 1),
			glm::ivec3(7, 6, 5),
			glm::ivec3(5, 4, 7),
			glm::ivec3(4, 0, 3),
			glm::ivec3(3, 7, 4),
			glm::ivec3(4, 5, 1),
			glm::ivec3(1, 0, 4)
		};
		return std::pair<std::vector<glm::fvec3>, std::vector<glm::ivec3>>(vertices, indices);
	}

	std::pair<std::vector<glm::fvec3>, std::vector<glm::ivec3>> STUB_empty() {
		std::vector<glm::fvec3> vertices;
		std::vector<glm::ivec3> indices;
		return std::pair<std::vector<glm::fvec3>, std::vector<glm::ivec3>>(vertices, indices);
	}
};

#endif