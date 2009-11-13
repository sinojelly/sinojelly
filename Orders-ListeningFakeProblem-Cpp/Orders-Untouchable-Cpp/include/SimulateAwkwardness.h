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

#ifndef SIMULATE_AWKWARDNESS_H_
#define SIMULATE_AWKWARDNESS_H_

class SimulateAwkwardness
{
public:
	static int randomNumber(int lowEnd, int highEnd);

	static void delay(int milliseconds);

	static void randomDelay(int shortestDelay, int longestDelay);
};

#endif
