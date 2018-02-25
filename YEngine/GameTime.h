#pragma once
#ifndef GAMETIME_H
#define GAMETIME_H

#include "IGameTime.h"

class GameTime : public IGameTime
{
private:
	// Variables
	double m_Frequency;
	__int64 m_CounterStart;
	__int64 m_PrevCount;
	double m_DeltaTime;

public:
	GameTime();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Starts the Game Timer.
	*/
	void StartTimer();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the total amount of time elapsed since the game was started.
	*/
	double GetTime();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Updates the 'deltaTime'(obj) since the last frame.
	*/
	void UpdateFrameTime();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the 'deltaTime'(obj).
	*/
	const double getDeltaTime();
};

#endif
