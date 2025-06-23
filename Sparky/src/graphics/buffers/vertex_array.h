#pragma once
#include <iostream>
#include <vector>
#include "vertex_buffer.h"

namespace delta
{
	namespace graphics
	{
		class VertexArray
		{
			GLuint buffer_id_;
			std::vector<VertexBuffer*> buffers_;
		public:
			VertexArray();
			~VertexArray();

			void bind() const;
			void unbind() const;

			void addBuffer(VertexBuffer* buffer, GLuint index);
		};
	}
}