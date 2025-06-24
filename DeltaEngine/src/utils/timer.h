#pragma once

#include <Windows.h>

namespace delta
{
	class Timer
	{
		LARGE_INTEGER start_time_;
		double frequency_;
	public:
		
		Timer();

		void reset();
		double elapsed();
	};
}