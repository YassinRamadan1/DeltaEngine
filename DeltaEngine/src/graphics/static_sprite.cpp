#include "static_sprite.h"

namespace delta
{
	namespace graphics
	{
		StaticSprite::StaticSprite(math::vec3 position, math::vec2 size, math::vec4 color, Shader& shader, Texture* texture)
			: Renderable2D(position, size, color, texture), shader_(shader)
		{
			GLfloat vertices[] =
			{
				0, 0, 0,
				size_.x, 0, 0,
				size_.x, size_.y, 0,
				0, size_.y, 0
			};

			GLfloat colors[] =
			{
				color_.r, color_.g, color_.b, color_.a,
				color_.r, color_.g, color_.b, color_.a,
				color_.r, color_.g, color_.b, color_.a,
				color_.r, color_.g, color_.b, color_.a
			};

			GLfloat texture_coords[] =
			{
				0.0, 0.0,
				1.0, 0.0,
				1.0, 1.0,
				0.0, 1.0
			};

			GLuint indices[] =
			{
				0, 1, 2,
				2, 3, 0
			};

			vao_ = new VertexArray();
			ibo_ = new IndexBuffer(indices, 6);
			vao_->addBuffer(new VertexBuffer(vertices, 12, 3), 0);
			vao_->addBuffer(new VertexBuffer(texture_coords, 8, 2), 2);
			vao_->addBuffer(new VertexBuffer(colors, 16, 4), 4);
		}

		StaticSprite::~StaticSprite()
		{
			delete vao_;
			delete ibo_;
		}

	}
}