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

#include "Shipper.h"
#include "Database.h"

Shipper::~Shipper()
{
}

Shipper::Shipper(const std::string& orderId, const ShippingOption& option) 
: m_option(option), m_weightAccumulator(Weight::zero())
{
}

Money Shipper::total() const
{
	Database::touchDatabase();
	return m_option.rate(m_weightAccumulator);
}

void Shipper::addItem(const std::string& sku, int quantity, const Weight& weight)
{
	m_weightAccumulator = m_weightAccumulator.add(weight);
}
