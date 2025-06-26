#include "shader.h"

#ifdef DEBUG
#define Log(x) std::cout << (x)

#else
#define Log(x)

#endif

namespace delta
{
	namespace graphics
	{
		Shader::Shader(const char* vertex_shader_path, const char* fragment_shader_path, const char* geometry_shader_path)
		{
			int success;
			char information_log[1000];

			std::string vertex_shader_string = readFile(vertex_shader_path);
			std::string fragment_shader_string = readFile(fragment_shader_path);

			const char *vertex_shader_code = vertex_shader_string.c_str();
			const char *fragment_shader_code = fragment_shader_string.c_str();;

			unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex_shader_id, 1, &vertex_shader_code, nullptr);
			glCompileShader(vertex_shader_id);

			glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(vertex_shader_id, 1000, NULL, information_log);
				std::cout << "Vertex Shader Compiling Error!\n" << information_log << '\n';
			}

			unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment_shader_id, 1, &fragment_shader_code, NULL);
			glCompileShader(fragment_shader_id);

			glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(fragment_shader_id, 1000, NULL, information_log);
				std::cout << "Fragment Shader Compiling Error!\n" << information_log << '\n';
			}

			shader_program_id_ = glCreateProgram();
			glAttachShader(shader_program_id_, vertex_shader_id);
			glAttachShader(shader_program_id_, fragment_shader_id);

			unsigned int geometry_shader_id;
			if (geometry_shader_path)
			{
				std::string geometry_shader_string = readFile(geometry_shader_path);
				const char* geometry_shader_code = geometry_shader_string.c_str();

				geometry_shader_id = glCreateShader(GL_GEOMETRY_SHADER);
				glShaderSource(geometry_shader_id, 1, &geometry_shader_code, NULL);
				glCompileShader(geometry_shader_id);

				glGetShaderiv(geometry_shader_id, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(geometry_shader_id, 1000, NULL, information_log);
					std::cout << "Geometry Shader Compiling Error!\n" << information_log << '\n';
				}

				glAttachShader(shader_program_id_, geometry_shader_id);
			}

			glLinkProgram(shader_program_id_);

			glGetProgramiv(shader_program_id_, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader_program_id_, 1000, NULL, information_log);
				std::cout << "Shader Program Linking Error!\n" << information_log << '\n';
			}

			glDeleteShader(vertex_shader_id);
			glDeleteShader(fragment_shader_id);
			if (geometry_shader_path)
			{
				glDeleteShader(geometry_shader_id);
			}
		}

		Shader::~Shader()
		{
			glDeleteProgram(shader_program_id_);
		}

		void Shader::enable() const
		{
			glUseProgram(shader_program_id_);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}

		GLint Shader::getUniformLocation(const GLchar* uniform_name) const
		{
			return glGetUniformLocation(shader_program_id_, uniform_name);
		}

		void Shader::set1iv(const GLchar* uniform_name, unsigned int count, int* v) const
		{
			glUniform1iv(getUniformLocation(uniform_name), count, v);
		}

		void Shader::set1i(const GLchar* uniform_name, GLint v) const
		{
			glUniform1i(getUniformLocation(uniform_name), v);
		}

		void Shader::set1f(const GLchar* uniform_name, GLfloat v) const
		{
			glUniform1f(getUniformLocation(uniform_name), v);
		}

		void Shader::set2f(const GLchar* uniform_name, const math::vec2& v) const
		{
			glUniform2fv(getUniformLocation(uniform_name), 1, (GLfloat*)(&v));
		}

		void Shader::set3f(const GLchar* uniform_name, const math::vec3& v) const
		{
			glUniform3fv(getUniformLocation(uniform_name), 1, (GLfloat*)(&v));
		}

		void Shader::set4f(const GLchar* uniform_name, const math::vec4& v) const
		{
			glUniform4fv(getUniformLocation(uniform_name), 1, (GLfloat*)(&v));
		}

		void Shader::setMat4f(const GLchar* uniform_name, bool Transpose, const math::mat4& v) const
		{
			glUniformMatrix4fv(getUniformLocation(uniform_name), 1, Transpose, (GLfloat*)(&v));
		}

	}
}