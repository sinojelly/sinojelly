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

#ifndef CACTUS_CLIENT_H_
#define CACTUS_CLIENT_H_

#include "Money.h"
#include "HolderInfo.h"
#include "TransactionInfo.h"
#include <string>

// CACTUS = Charge All Credit Transactions, Usually Simply
class CactusClient 
{
public:
	virtual ~CactusClient() { };

	virtual bool startSession(const std::string& merchantId) = 0;
	virtual void stopSession() = 0;

	virtual void setHolderInfo(const HolderInfo& holderInfo) = 0;
	virtual bool hasSufficientFundsFor(const Money& totalAmount) = 0;
	virtual void process(const TransactionInfo& transaction) = 0;
};

#endif
