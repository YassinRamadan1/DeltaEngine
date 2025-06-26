#pragma once

#include <FreeImage.h>

namespace delta
{
	bool loadImage(const char* image_path, unsigned char** image_data, unsigned int* width, unsigned int* height, unsigned int* bits_per_pixel, bool vertical_flip = true);
}