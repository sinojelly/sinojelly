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

#ifndef TRANSACTION_INFO_H_
#define TRANSACTION_INFO_H_

#include "Money.h"

class TransactionInfo
{
public:
	Money m_amount;
	std::string m_itemDescription;
	std::string m_date;

	TransactionInfo(const Money& amount,
					const std::string& itemDescription,
					const std::string& date)
		: m_amount(amount), m_itemDescription(itemDescription), m_date(date)
	{
	}
};

inline bool operator==(const TransactionInfo& lhs, const TransactionInfo& rhs)
{
	return lhs.m_amount == rhs.m_amount &&
		lhs.m_itemDescription == rhs.m_itemDescription &&
		lhs.m_date == rhs.m_date;
}
#endif
