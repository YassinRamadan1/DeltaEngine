#pragma once

#include <GL/glew.h>

namespace delta
{
	namespace graphics
	{
		class IndexBuffer
		{
			GLuint buffer_id_;
			GLuint count_;
		public:

			IndexBuffer(GLuint* data, GLsizei count);
			~IndexBuffer();
			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return count_; }
		};
	}
}