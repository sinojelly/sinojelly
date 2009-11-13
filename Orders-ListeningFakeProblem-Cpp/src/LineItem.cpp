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

#include "LineItem.h"


LineItem::LineItem(ProductPtr product, int quantity) 
	: m_product(product), m_quantity(quantity)
{ }

LineItem::~LineItem()
{
}

int LineItem::getQuantity() const 
{
	return m_quantity;
}

std::string LineItem::getText() const
{
	return m_product->getSku() + ": " + m_product->getDescription();
}

Money LineItem::getItemAmount() const
{
	return m_product->getBasePrice();
}

Money LineItem::getExtendedAmount() const 
{
	return Money(m_quantity).times(m_product->getBasePrice());
}

Weight LineItem::getExtendedWeight() const 
{
	return Weight(m_quantity).times(m_product->getBaseWeight());
}

std::string LineItem::getSku() const
{
	return m_product->getSku();
}

