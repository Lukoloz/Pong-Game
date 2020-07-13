#pragma once
#include <chrono>

using namespace std::chrono;

class FrameTimer
{
public:
	FrameTimer()
	{
		last = steady_clock::now();
	}
	float Mark()
	{
		auto old = last;
		last = steady_clock::now();
		const duration<float> frameTime = last - old;
		return frameTime.count();
	}
private:
	steady_clock::time_point last;
};