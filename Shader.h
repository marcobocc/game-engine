#ifndef H_SHADER
#define H_SHADER

#include <string>
#include <fstream>
#define GLEW_STATIC
#include <GL/glew.h>

class Shader {
public:
	Shader(std::string shader_name) : 
		m_program(0) {
		if (STUB_load_shader(shader_name)) {
		}
	}

	~Shader() {
		glDeleteProgram(m_program);
	}

	GLuint get_program() const {
		return m_program;
	}

private:
	GLuint m_program;

	bool STUB_load_shader(std::string shader_name) {
		if (shader_name == "shader/test") {
			return make_program_from_files("src/resources/shaders/vertex.txt", "src/resources/shaders/fragment.txt");
		}
		return false;
	}

	bool make_program_from_files(const char* vertex, const char* fragment) {
		m_program = glCreateProgram();
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		if (!make_shader_from_file(vertex, vertexShader)) {
			return false;
		}
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		if (!make_shader_from_file(fragment, fragmentShader)) {
			glDeleteShader(vertexShader);
			return false;
		}
		GLint linkStatusCode;
		glAttachShader(m_program, vertexShader);
		glAttachShader(m_program, fragmentShader);
		glLinkProgram(m_program);
		glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatusCode);
		if (!linkStatusCode) {
			GLint infoLogSize;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogSize);
			char* infoLog = new char[infoLogSize];
			glGetProgramInfoLog(m_program, infoLogSize, NULL, infoLog);
			//std::cout << infoLog << std::endl;
			delete[] infoLog;
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return false;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return true;
	}

	bool make_shader_from_file(const char* path, GLuint shader) {
		std::ifstream file(path, std::ios::ate | std::ios::binary);
		if (!file.is_open()) {
			return false;
		}
		std::size_t charCount = (std::size_t)(file.tellg());
		char* shaderSource = new char[charCount + 1];
		file.seekg(std::ios::beg);
		file.read(shaderSource, charCount);
		shaderSource[charCount] = '\0';
		file.close();
		GLint compileStatusCode;
		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatusCode);
		if (!compileStatusCode) {
			GLint infoLogSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogSize);
			char* infoLog = new char[infoLogSize];
			glGetShaderInfoLog(shader, infoLogSize, NULL, infoLog);
			//std::cout << infoLog << std::endl;
			delete[] infoLog;
			delete[] shaderSource;
			return false;
		}
		delete[] shaderSource;
		return true;
	}
};

#endif