/// ***************************************************************************
/// Copyright (c) 2009, Industrial Logic, Inc., All Rights Reserved.
///
/// This code is the exclusive property of Industrial Logic, Inc. It may ONLY be
/// used by students during Industrial Logic's workshops or by individuals
/// who are being coached by Industrial Logic on a project.
///
/// This code may NOT be copied or used for any other purpose without the prior
/// written consent of Industrial Logic, Inc.
/// ****************************************************************************

#include "SimulateAwkwardness.h"
#include <stdio.h> // rand
#include <stdlib.h> // rand
#include <time.h>
#ifdef _MSC_VER
#include <Windows.h>  // Sleep
#else
#include <unistd.h>  // sleep
#endif

int SimulateAwkwardness::randomNumber(int lowEnd, int highEnd)
{
	return int(lowEnd + (rand() / (double) RAND_MAX) * (highEnd - lowEnd));
}

void SimulateAwkwardness::delay(int milliseconds)
{
#ifdef __MINGW32_VERSION
	_sleep(milliseconds);
#else
#ifdef _MSC_VER
	Sleep(milliseconds);
#else
#ifdef __CYGWIN__
	::usleep(milliseconds * 1000);
#else
	::usleep(1 + milliseconds / 1000);
#endif
#endif
#endif
}

void SimulateAwkwardness::randomDelay(int shortestDelay, int longestDelay)
{
	int milliseconds = randomNumber(shortestDelay, longestDelay);
	delay(milliseconds);
}

