#include "batch_renderer_2D.h"

namespace delta
{
	namespace graphics
	{
		BatchRenderer2D::BatchRenderer2D()
		{
			glGenVertexArrays(1, &vao_);
			glGenBuffers(1, &vbo_);

			glBindVertexArray(vao_);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_VERTEX_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (void*)(offsetof(Vertex, position_)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (void*)(offsetof(Vertex, color_)));
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			GLuint* indices = new GLuint[RENDERER_INDEX_BUFFER_SIZE];
			for (unsigned int i = 0, accumulation = 0; i < RENDERER_INDEX_BUFFER_SIZE; i += 6, accumulation += 4)
			{
				indices[i] = 0 + accumulation, indices[i + 1] = 1 + accumulation, indices[i + 2] = 2 + accumulation;
				indices[i + 3] = 2 + accumulation, indices[i + 4] = 3 + accumulation, indices[i + 5] = 0 + accumulation;
			}
			ibo_ = new IndexBuffer(indices, RENDERER_INDEX_BUFFER_SIZE);
			delete[] indices;
		}
		
		BatchRenderer2D::~BatchRenderer2D()
		{
			glDeleteVertexArrays(1, &vao_);
			glDeleteBuffers(1, &vbo_);
			delete ibo_;
		}

		void BatchRenderer2D::begin()
		{
			glBindVertexArray(vao_);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_);
			buffer_ = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::submit(Renderable2D* object)
		{
			const math::vec2& size = object->getSize();
			const math::vec3& position = object->getPosition();
			const math::vec4& color = object->getColor();

			buffer_->position_ = position;
			buffer_->color_ = color;
			buffer_++;

			buffer_->position_ = math::vec3(position.x + size.x, position.y, position.z);
			buffer_->color_ = color;
			buffer_++;
		
			buffer_->position_ = math::vec3(position.x + size.x, position.y + size.y, position.z);
			buffer_->color_ = color;
			buffer_++;

			buffer_->position_ = math::vec3(position.x, position.y + size.y, position.z);
			buffer_->color_ = color;
			buffer_++;

			index_count_ += 6;
		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		void BatchRenderer2D::flush()
		{
			glBindVertexArray(vao_);
			glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, nullptr);
			index_count_ = 0;
		}

	}
}