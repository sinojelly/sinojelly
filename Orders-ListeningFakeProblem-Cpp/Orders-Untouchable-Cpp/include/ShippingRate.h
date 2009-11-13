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

#ifndef SHIPPING_RATE_H
#define SHIPPING_RATE_H

#include <string>
#include "Money.h"

class Weight;

class ShippingRate 
{
public:
	static const ShippingRate SUPER_SAVER;

	ShippingRate(const std::string& name, const Money& rate);
	virtual ~ShippingRate();

	virtual std::string getName();
	
	virtual Money calculate(const Weight& totalWeight);

private:
	std::string m_name;
	Money m_rate;
};

#endif // SHIPPING_RATE_H
