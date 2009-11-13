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

#include "ShippingOrder.h"
#include "Shipper.h"

void ShippingOrder::prepareToShip()
{
	Shipper shipper(getBaseOrder()->getOrderId(), m_option);
	for (LineItemIterator items = getBaseOrder()->getItems(); items != getBaseOrder()->endItems(); items++)
	{
		LineItem item = *items;
		shipper.addItem(item.getSku(), item.getQuantity(), item.getExtendedWeight());
	}
	m_shippingTotal = shipper.total();
}

Money ShippingOrder::getShippingTotal()
{
	return m_shippingTotal;
}

OrderPtr ShippingOrder::getBaseOrder()
{
	return m_baseOrder;
}
