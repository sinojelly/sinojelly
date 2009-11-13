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

#include "Order.h"
#include <iostream>

Order::Order(const std::string& accountId) : m_accountId(accountId)
{
}

Order::Order(const std::string& accountId, const std::string& orderId) 
	: m_orderId(orderId),
	m_accountId(accountId),
	m_netTotal(0),
	m_weight(0)
{
}

Order::~Order()
{
}

void Order::add(const LineItem& item)
{
	m_items.push_back(item);
	m_netTotal = m_netTotal.add(item.getExtendedAmount());
	m_weight = m_weight.add(item.getExtendedWeight());
	reserveProduct(item);
}

void Order::reserveProduct(const LineItem& item) const
{
	InventoryControl::get()->reserveProduct(getOrderId(), item.getSku(), item.getQuantity());
}

LineItemIterator Order::getItems() const
{
	return m_items.begin();
}

LineItemIterator Order::endItems() const
{
	return m_items.end();
}

Money Order::getNetTotal() const
{
	return m_netTotal;
}

Weight Order::getWeight() const
{
	return m_weight;
}

std::string Order::getOrderId() const
{
	if (m_orderId == "")
		m_orderId = getOrderIdFromGenerator();
	return m_orderId;
}

std::string Order::getOrderIdFromGenerator() const
{
	return IdGenerator::getOrderId(m_accountId);
}
