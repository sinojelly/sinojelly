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

#include "WebServiceGateway.h"
#include "SimulateAwkwardness.h"

double WebServiceGateway::execute(const std::map<std::string, std::string>& /*parameters*/)
{
	// Made you look!

	// Normally, you'd find some code here to contact a web service and
	// get the current exchange rate fromCurrency toCurrency. Clearly,
	// that collaboration would be twice awkward: both slow and indeterminate.
	// To simulate the awkwardness, we have the following lines:
	SimulateAwkwardness::delay(SimulateAwkwardness::randomNumber(7000, 10000));
	return SimulateAwkwardness::randomNumber(3000, 8000) / 5000.0;
}

