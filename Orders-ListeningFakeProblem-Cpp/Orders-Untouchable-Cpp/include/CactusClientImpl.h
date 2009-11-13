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

#ifndef CACTUS_CLIENT_IMPL_H_
#define CACTUS_CLIENT_IMPL_H_

#include "Money.h"
#include "CactusClient.h"
#include <string>

class CactusClientImpl : public CactusClient 
{
public:
	virtual bool startSession(const std::string& merchantId);

	virtual void stopSession();

	virtual bool hasSufficientFundsFor(const Money& totalAmount);

	virtual void process(const TransactionInfo& transaction);

	virtual void setHolderInfo(const HolderInfo& clientInfo);
};

#endif
