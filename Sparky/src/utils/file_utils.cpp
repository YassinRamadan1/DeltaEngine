#include "file_utils.h"

namespace sparky
{
	std::string readFile(const char* file_path)
	{
		FILE* file = fopen(file_path, "rt");
		if (!file)
		{
			return std::string();
		}

		fseek(file, 0, SEEK_END);
		long file_size = ftell(file);
		char* data = new char[file_size + 1];
		memset(data, 0, file_size + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, file_size, file);
		std::string result(data);
		delete[] data;
		return result;
	}
}