#pragma once
#include <GL/glew.h>
#include "../utils/file_utils.h"
#include "../math/math.h"

namespace sparky
{
	namespace graphics
	{
		class Shader {

		private:

			GLuint shader_program_id_ = 0;
			
			GLint getUniformLocation(const GLchar* uniform_name) const;
		public:

			Shader(const char* vertex_shader_path, const char* fragment_shader_path, const char* geometry_shader_path = nullptr);
			~Shader();
			void enable() const;
			void disable() const;


			void set1i(const GLchar* uniform_name, GLint v) const;
			void set1f(const GLchar* uniform_name, GLfloat v) const;
			
			void set2f(const GLchar* uniform_name, const math::vec2& v) const;
			void set3f(const GLchar* uniform_name, const math::vec3& v) const;
			void set4f(const GLchar* uniform_name, const math::vec4& v) const;

			void setMat4f(const GLchar* uniform_name, bool Transpose, const math::mat4& v) const;
		};
	}
}