#pragma once

#include <GL/glew.h>
#include <iostream>
#include <deque>
#include "renderable_2d.h"

namespace delta
{
	namespace graphics
	{
		class Renderer2D
		{
		public:
			virtual ~Renderer2D() = default;
			virtual void submit(Renderable2D* object) = 0;
			virtual void flush() = 0;
		};
	}
}
