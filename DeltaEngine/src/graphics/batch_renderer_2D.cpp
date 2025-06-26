#include "batch_renderer_2D.h"
#include "renderable_2d.h"

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
			
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (void*)(offsetof(Vertex, Vertex::position_)));
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (void*)(offsetof(Vertex, Vertex::color_)));
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			
			glVertexAttribPointer(SHADER_TEXTURE_COORDINATE_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (void*)(offsetof(Vertex, Vertex::texture_coordinate_)));
			glEnableVertexAttribArray(SHADER_TEXTURE_COORDINATE_INDEX);
			
			glVertexAttribPointer(SHADER_TEXTURE_SLOT_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (void*)(offsetof(Vertex, Vertex::texture_slot_)));
			glEnableVertexAttribArray(SHADER_TEXTURE_SLOT_INDEX);

			for (int i = 0; i < 32; i++)
				texture_slots_[i] = 0;

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
			const std::vector<math::vec2>& uvs = object->getTextureCoordinates();
			const unsigned int& texture_id = object->getTextureID();
			const math::mat4& matrix = transformation_stack_.back();
			unsigned int c = 0, texture_slot = 0;
			
			if (texture_id == 0)
			{
				unsigned char red = color.r * 255.0, green = color.g * 255.0, blue = color.b * 255.0, alpha = color.a * 255.0;
				c = (red | (green << 8) | (blue << 16) | (alpha << 24));
				texture_slot = 0;
			}
			else
			{
				for (int i = 0; i < 32; i++)
				{
					if (texture_slots_[i] == 0 || texture_slots_[i] == texture_id)
					{
						texture_slots_[i] = texture_id;
						texture_slot = i + 1;
						break;
					}
				}
				if (texture_slot == 0)
				{
					end();

					flush();
					//std::cout << "separation needed! : " << texture_id << '\n';
					begin();
					texture_slot = 1;
					texture_slots_[0] = texture_id;
				}
			}

			buffer_->position_ = matrix * position;
			buffer_->color_ = c;
			buffer_->texture_coordinate_ = uvs[0];
			buffer_->texture_slot_ = texture_slot;
			buffer_++;
								
			buffer_->position_ = matrix * math::vec3(position.x + size.x, position.y, position.z);
			buffer_->color_ = c;
			buffer_->texture_coordinate_ = uvs[1];
			buffer_->texture_slot_ = texture_slot;
			buffer_++;
						
			buffer_->position_ = matrix * math::vec3(position.x + size.x, position.y + size.y, position.z);
			buffer_->color_ = c;
			buffer_->texture_coordinate_ = uvs[2];
			buffer_->texture_slot_ = texture_slot;
			buffer_++;
								
			buffer_->position_ = matrix * math::vec3(position.x, position.y + size.y, position.z);
			buffer_->color_ = c;
			buffer_->texture_coordinate_ = uvs[3];
			buffer_->texture_slot_ = texture_slot;
			buffer_++;

			index_count_ += 6;
		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		void BatchRenderer2D::flush()
		{
			for (int i = 0; i < 32; i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, texture_slots_[i]);
			}
			
			glBindVertexArray(vao_);
			glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, nullptr);
			
			index_count_ = 0;
			for (int i = 0; i < 32; i++)
				texture_slots_[i] = 0;
		}

	}
}