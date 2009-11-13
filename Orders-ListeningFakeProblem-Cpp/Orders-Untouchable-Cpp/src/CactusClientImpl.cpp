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

#include "CactusClientImpl.h"
#include "SimulateAwkwardness.h"

// Well, we haven't *really* implemented credit card charging. The code
// here just simulates the awkwardness involved in connecting to such a
// service over the Internet.
// Moreover, all methods happily return "true" so it even looks like the
// tests are running!
bool CactusClientImpl::startSession(const std::string& merchantId)
{
	SimulateAwkwardness::delay(SimulateAwkwardness::randomNumber(7000, 10000));
	return true;
}

void CactusClientImpl::stopSession()
{
	SimulateAwkwardness::delay(SimulateAwkwardness::randomNumber(3000, 4000));
}

bool CactusClientImpl::hasSufficientFundsFor(const Money& totalAmount)
{
	SimulateAwkwardness::delay(SimulateAwkwardness::randomNumber(3000, 6000));
	int randomNumber = SimulateAwkwardness::randomNumber(-2000, 2000);
	return randomNumber > 0;
}

void CactusClientImpl::process(const TransactionInfo& transaction)
{
	SimulateAwkwardness::delay(SimulateAwkwardness::randomNumber(2000, 6000));
}

void CactusClientImpl::setHolderInfo(const HolderInfo& clientInfo)
{
	SimulateAwkwardness::delay(SimulateAwkwardness::randomNumber(1000, 6000));
}
