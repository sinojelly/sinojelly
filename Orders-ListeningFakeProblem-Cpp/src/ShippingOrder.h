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

#ifndef SHIPPING_ORDER_H_
#define SHIPPING_ORDER_H_

#include "Money.h"
#include "Weight.h"
#include "ShippingOption.h"
#include "Order.h"

class ShippingOrder
{
public:
	ShippingOrder(OrderPtr baseOrder, const ShippingOption& option)
		: m_baseOrder(baseOrder), m_option(option), m_shippingTotal(Money::zero())
	{ }

	virtual ~ShippingOrder() { }

	virtual void prepareToShip();
	virtual Money getShippingTotal();
	virtual OrderPtr getBaseOrder();

private:
	OrderPtr m_baseOrder;
	const ShippingOption& m_option;
	Money m_shippingTotal;
};

typedef counted_ptr<ShippingOrder> ShippingOrderPtr;

#endif
