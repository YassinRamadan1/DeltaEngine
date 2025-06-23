#pragma once

#include <GL/glew.h>

namespace delta
{
	namespace graphics
	{
		class VertexBuffer
		{
			GLuint buffer_id_;
			GLuint component_count_;
		public:

			VertexBuffer(GLfloat* data, GLsizei count, GLuint component_count);
			~VertexBuffer();

			void bind() const;
			void unbind() const;

			inline GLuint getComponentCount() const { return component_count_; }
		};
	}
}