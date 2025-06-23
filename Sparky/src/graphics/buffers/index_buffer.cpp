#include "index_buffer.h"

namespace delta
{
	namespace graphics
	{
		IndexBuffer::IndexBuffer(GLuint* data, GLsizei count) : count_(count)
		{
			glGenBuffers(1, &buffer_id_);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * count_, data, GL_STATIC_DRAW);
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &buffer_id_);
		}

		void IndexBuffer::bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_);
		}

		void IndexBuffer::unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}