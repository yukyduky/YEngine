#include "GameTime.h"
#include <dwrite.h>


GameTime::GameTime()
{
	m_Frequency = 0.0;
	m_CounterStart = 0;
	m_PrevCount = 0;
	m_DeltaTime = 0.0;
}

void GameTime::StartTimer()
{
	LARGE_INTEGER currentCount;
	// Gets the frequency of the performance counter which is fixed at boot and only needed to be stored once
	QueryPerformanceFrequency(&currentCount);
	m_Frequency = double(currentCount.QuadPart);

	// Get the current value of the performance counter since boot
	QueryPerformanceCounter(&currentCount);
	m_CounterStart = currentCount.QuadPart;
}

double GameTime::GetTime()
{
	LARGE_INTEGER currentCount;

	QueryPerformanceCounter(&currentCount);
	return double(currentCount.QuadPart - m_CounterStart) / m_Frequency;
}

void GameTime::UpdateFrameTime()
{
	LARGE_INTEGER currentCount;
	__int64 frameCount = (__int64)0.0;

	QueryPerformanceCounter(&currentCount);

	// Gets the count since last frame
	frameCount = currentCount.QuadPart - m_PrevCount;
	// Stores the current count for the next frame
	m_PrevCount = currentCount.QuadPart;

	// Should never happen
	if (frameCount < 0.0f)
	{
		frameCount = (__int64)0.0;
	}

	// Count divided by frequency equals time in milliseconds
	m_DeltaTime = frameCount / m_Frequency;
}

const double GameTime::getDeltaTime()
{
	return m_DeltaTime;
}
