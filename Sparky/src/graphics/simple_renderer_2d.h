#pragma once
#include "renderer_2d.h"
#include "static_sprite.h"

namespace delta
{
	namespace graphics
	{
		class SimpleRenderer2D : public Renderer2D
		{
			std::deque<Renderable2D*> render_queue_;
		public:

			SimpleRenderer2D() = default;
			void submit(Renderable2D* object) override;
			void flush() override;
		};
	}
}