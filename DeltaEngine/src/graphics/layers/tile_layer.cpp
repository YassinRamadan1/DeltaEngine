#include "tile_layer.h"

namespace delta
{
	namespace graphics
	{
		TileLayer::TileLayer(Shader* shader, math::mat4 projection_matrix)
			: Layer(new BatchRenderer2D(), shader, projection_matrix)
		{ }
	}
}