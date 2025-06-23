#include "mat4.h"

namespace delta
{
	namespace math
	{
		mat4::mat4()
		{
			data[0] = data[1] = data[2] = data[3] = 0;
			data[4] = data[5] = data[6] = data[7] = 0;
			data[8] = data[9] = data[10] = data[11] = 0;
			data[12] = data[13] = data[14] = data[15] = 0;
		}

		mat4::mat4(float v)
		{
			data[0] = data[5] = data[10] = data[15] = v;

			data[1] = data[2] = data[3] = 0;
			data[4] = data[6] = data[7] = 0;
			data[8] = data[9] =  data[11] = 0;
			data[12] = data[13] = data[14] = 0;
		}

		mat4::mat4(const vec4& column1, const vec4& column2, const vec4& column3, const vec4& column4)
		{
			columns[0] = column1, columns[1] = column2, columns[2] = column3, columns[3] = column4;
		}

		mat4& mat4::operator *=(const mat4& other)
		{
			mat4 mat;

			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					for (int k = 0; k < 4; k++)
						mat.data[j * 4 + i] += this->data[k * 4 + i] * other.data[j * 4 + k];
			return mat;
		}
	}
}