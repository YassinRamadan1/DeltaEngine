#include "vec2.h"

namespace delta
{
	namespace math
	{

		vec2::vec2()
		{
			this->x = 0.0f, this->y = 0.0f;
		}

		vec2::vec2(const float& v)
		{
			this->x = this->y = v;
		}

		vec2::vec2(const float& x, const float& y)
		{
			this->x = x, this->y = y;
		}

		vec2& vec2::operator+=(const vec2& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		vec2& vec2::operator-=(const vec2& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		vec2& vec2::operator*=(const vec2 & other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		vec2& vec2::operator/=(const vec2& other)
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}

		std::ostream& operator<<(std::ostream& stream, const vec2& vec)
		{
			stream << "vec2: (" << vec.x << ", " << vec.y << ')';
			return stream;
		}
	}
}