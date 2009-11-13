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

#include "ShippingRate.h"
#include "Weight.h"

const ShippingRate ShippingRate::SUPER_SAVER("Super Saver", Money(2.04));

ShippingRate::~ShippingRate()
{
}

ShippingRate::ShippingRate(const std::string& name, const Money& rate) : m_name(name), m_rate(rate)
{
}

std::string ShippingRate::getName()
{
	return m_name;
}

Money ShippingRate::calculate(const Weight& totalWeight)
{
	return totalWeight.times(m_rate);
}

