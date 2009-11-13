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

#include "Product.h"

Product::Product(const std::string& sku, 
			const std::string& description, 
			const Money& basePrice, 
			const Weight& baseWeight)
	: m_sku(sku),
	  m_description(description),
	  m_basePrice(basePrice),
	  m_baseWeight(baseWeight)
{
}

Product::~Product()
{
}

std::string Product::getSku() const
{
	return m_sku;
}

std::string Product::getDescription() const
{
	return m_description;
}

Money Product::getBasePrice() const
{
	return m_basePrice;
}

Weight Product::getBaseWeight() const
{
	return m_baseWeight;
}
