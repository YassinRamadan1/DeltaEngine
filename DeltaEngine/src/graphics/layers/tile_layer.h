#pragma once
#include "layer.h"
#include "../batch_renderer_2D.h"

namespace delta
{
	namespace graphics
	{
		class TileLayer : public Layer
		{
		public:

			TileLayer(Shader* shader, math::mat4 projection_matrix);
		};
	}
}