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

#ifndef HOLDER_INFO_H_
#define HOLDER_INFO_H_

#include <string>

class HolderInfo
{
public:
	std::string nameOnCard;
	std::string expiration;
	std::string billingAddress;
};

inline bool operator==(const HolderInfo& lhs, const HolderInfo& rhs)
{
	return lhs.nameOnCard == rhs.nameOnCard &&
		lhs.expiration == rhs.expiration &&
		lhs.billingAddress == rhs.billingAddress;
}
#endif
