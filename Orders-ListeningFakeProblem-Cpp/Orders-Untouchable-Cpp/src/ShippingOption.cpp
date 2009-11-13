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

#include "ShippingOption.h"

const ShippingOption ShippingOption::AIR(Money(2.00));
const ShippingOption ShippingOption::GROUND(Money(1.25));
const ShippingOption ShippingOption::SUPER_SAVER(Money(0.28));
const ShippingOption ShippingOption::NEXT_DAY(Money(4.00));

ShippingOption::ShippingOption(const Money& rate) : m_rate(rate) 
{ }

Money ShippingOption::rate(const Weight& weight) const
{
	return weight.times(m_rate);
}
