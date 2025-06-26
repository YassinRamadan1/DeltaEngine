#pragma once

#include <GL/glew.h>
#include <iostream>
#include <string>
#include "../utils/image_utils.h"

namespace delta
{
	namespace graphics
	{
		class Texture
		{
			GLuint texture_id_;
		public:

			Texture(const std::string& image_path, bool gamma_space = true);

			void bind() const;
			void unbind() const;
			inline const GLuint& getID() const { return texture_id_; }
		};
	}
}