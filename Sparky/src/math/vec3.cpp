#include "vec3.h"

namespace sparky
{
	namespace math
	{

		vec3::vec3()
		{
			this->x = 0.0f, this->y = this->z = 0.0f;
		}

		vec3::vec3(const float& v)
		{
			this->x = this->y = this->z = v;
		}

		vec3::vec3(const float& x, const float& y, const float& z)
		{
			this->x = x, this->y = y, this->z = z;
		}

		vec3& vec3::operator+=(const vec3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		vec3& vec3::operator-=(const vec3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}

		vec3& vec3::operator*=(const vec3 & other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}

		vec3& vec3::operator/=(const vec3& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;

			return *this;
		}

		std::ostream& operator<<(std::ostream& stream, const vec3& vec)
		{
			stream << "vec3: (" << vec.x << ", " << vec.y << ", " << vec.z << ')';
			return stream;
		}
	}
}