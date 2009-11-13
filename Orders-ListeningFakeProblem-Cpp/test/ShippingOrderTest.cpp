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
#include <gtest/gtest.h>

#include "ShippingOrder.h"

class ShippingOrderTest : public testing::Test
{
protected:
	OrderPtr baseOrder;
	ShippingOrderPtr shippingOrder;
	ProductPtr largeProduct;
	ProductPtr smallProduct;
	LineItem oneLarge;
	LineItem oneSmall;
	const ShippingOption& option;

protected:
	ShippingOrderTest() :
		largeProduct(new Product("SKU001", "Large Widget", Money(123), Weight(6))),
		smallProduct(new Product("SKU002", "Small Widget", Money(4.56), Weight(0.10))),
		oneLarge(largeProduct, 1),
		oneSmall(smallProduct, 1),
		option(ShippingOption::AIR)
	{ }

	virtual void SetUp()
	{
		baseOrder = OrderPtr(new Order("ACCOUNTID"));
		shippingOrder = ShippingOrderPtr(new ShippingOrder(baseOrder, option));
	}
};

TEST_F(ShippingOrderTest, testShippingAmountSingle)
{
	baseOrder->add(oneLarge);
	shippingOrder->prepareToShip();
	ASSERT_EQ(option.rate(oneLarge.getExtendedWeight()), shippingOrder->getShippingTotal());
}

TEST_F(ShippingOrderTest, testShippingAmountMultiple)
{
	baseOrder->add(oneLarge);
	baseOrder->add(oneSmall);
	shippingOrder->prepareToShip();
	Weight weight = oneLarge.getExtendedWeight().add(oneSmall.getExtendedWeight());
	ASSERT_EQ(option.rate(weight), shippingOrder->getShippingTotal());
}
