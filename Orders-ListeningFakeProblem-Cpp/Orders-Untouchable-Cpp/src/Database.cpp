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

#include "Database.h"
#include "SimulateAwkwardness.h"

void Database::touchDatabase()
{
	// Okay, okay, give us a break.  The name of the game is not to implement a real system, it's to teach you
	// how to extract and override, slip, and fake.
	int milliseconds = SimulateAwkwardness::randomNumber(2000, 6000);
	SimulateAwkwardness::delay(milliseconds);
}

