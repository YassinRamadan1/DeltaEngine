#include "image_utils.h"

namespace delta
{
	bool loadImage(const char* image_path, unsigned char** image_data, unsigned int* width, unsigned int* height, unsigned int* bits_per_pixel, bool vertical_flip)
	{
		FREE_IMAGE_FORMAT format = FIF_UNKNOWN;

		FIBITMAP* image = nullptr;
		format = FreeImage_GetFileType(image_path, 0);
		if (format == FIF_UNKNOWN)
			format = FreeImage_GetFIFFromFilename(image_path);
		if (format == FIF_UNKNOWN)
			return false;

		if (FreeImage_FIFSupportsReading(format))
			image = FreeImage_Load(format, image_path, 0);
		if (!image)
			return false;
		
		if (vertical_flip)
			FreeImage_FlipVertical(image);

		*width = FreeImage_GetWidth(image);
		*height = FreeImage_GetHeight(image);
		*bits_per_pixel = FreeImage_GetBPP(image);
		unsigned int image_size = *height * FreeImage_GetPitch(image);
		*image_data = new unsigned char[image_size];
		memcpy(*image_data, FreeImage_GetBits(image), image_size);

		FreeImage_Unload(image);
		return true;
	}
}