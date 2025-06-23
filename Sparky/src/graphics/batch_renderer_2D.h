#pragma once

#include "renderer_2d.h"

namespace sparky
{
	namespace graphics
	{
#define RENDERER_MAX_SPRITES			60000
#define RENDERER_VERTEX_SIZE			sizeof(Vertex)
#define RENDERER_SPRITE_SIZE			RENDERER_VERTEX_SIZE * 4
#define RENDERER_VERTEX_BUFFER_SIZE		RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDEX_BUFFER_SIZE		RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX				0
#define SHADER_NORMAL_INDEX				1
#define SHADER_TEXTURE_COORDINATE_INDEX 2
#define SHADER_TEXTURE_ID_INDEX			3
#define SHADER_COLOR_INDEX				4

		class BatchRenderer2D : public Renderer2D
		{
			GLuint vao_;
			GLuint vbo_;
			GLuint index_count_;

			IndexBuffer* ibo_;
			Vertex* buffer_;
		public:

			BatchRenderer2D();
			~BatchRenderer2D();
			void begin();
			void submit(Renderable2D* object) override;
			void end();
			void flush() override;
		};
	}
}