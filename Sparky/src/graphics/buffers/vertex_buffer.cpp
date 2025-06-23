#include "vertex_buffer.h"

namespace delta
{
	namespace graphics
	{

		VertexBuffer::VertexBuffer(GLfloat* data, GLsizei count, GLuint component_count) : component_count_(component_count)
		{
			glGenBuffers(1, &buffer_id_);
			glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * count, data, GL_STATIC_DRAW);
		}

		VertexBuffer::~VertexBuffer()
		{
			glDeleteBuffers(1, &buffer_id_);
		}

		void VertexBuffer::bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
		}

		void VertexBuffer::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}