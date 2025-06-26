#include "texture.h"

namespace delta
{
	namespace graphics
	{
		Texture::Texture(const std::string& image_path, bool gamma_space)
		{
			glGenTextures(1, &texture_id_);

			unsigned char* image = nullptr;
			unsigned int width, height, bits_per_pixel;

			loadImage(image_path.c_str(), &image, &width, &height, &bits_per_pixel);
			if (!image)
			{
				std::cout << "Failed to load the image: " << image_path << '\n';
				return;
			}
			
			glBindTexture(GL_TEXTURE_2D, texture_id_);

			GLenum format;
			GLint internal_format;
			switch (bits_per_pixel)
			{
			case 24:
				format = GL_BGR;
				break;
			case 32:
				format = GL_BGRA;
				break;
			case 8:
				format = GL_RED;
				break;
			default:
				format = GL_RED;
				break;
			}

			switch (format)
			{
			case GL_BGR:
				internal_format = gamma_space ? GL_SRGB8 : GL_RGB8;
				break;
			case GL_BGRA:
				internal_format = gamma_space ? GL_SRGB8_ALPHA8 : GL_RGBA8;
				break;
			case GL_RED:
				internal_format = GL_R8;
				break;
			default:
				internal_format = GL_R8;
				break;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			delete[] image;
		}

		void Texture::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, texture_id_);
		}

		void Texture::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}