#include "vertex_array.h"

namespace sparky
{
	namespace graphics
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &buffer_id_);
			glBindVertexArray(buffer_id_);
		}

		VertexArray::~VertexArray()
		{
			for (int i = 0; i < buffers_.size(); i++)
			{
				delete buffers_[i];
			}
			glDeleteVertexArrays(1, &buffer_id_);
		}

		void VertexArray::bind() const
		{
			glBindVertexArray(buffer_id_);
		}
		void VertexArray::unbind() const
		{
			glBindVertexArray(0);
		}

		void VertexArray::addBuffer(VertexBuffer* buffer, GLuint index)
		{
			buffers_.push_back(buffer);
			bind();
			buffer->bind();
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, sizeof(GLfloat) * buffer->getComponentCount(), (void*)(0));
			buffer->unbind();
			unbind();
		}
	}
}