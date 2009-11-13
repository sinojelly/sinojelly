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

#include "Money.h"
#include "Weight.h"
#include "Product.h"
#include "LineItem.h"

class TestableOrder : public Order
{
public:
	TestableOrder(const std::string& accountId) : Order(accountId)
	{ }

protected:
	virtual std::string getOrderIdFromGenerator() const
	{
		return m_accountId + ":10001";
	}

	virtual void reserveProduct(const LineItem& item) const
	{
	}
};

class OrderTest : public testing::Test
{
protected:
	OrderPtr order;
	ProductPtr largeProduct;
	ProductPtr smallProduct;
	LineItem oneLarge;
	LineItem oneSmall;
	LineItem threeSmall;

protected:
	OrderTest() :
		largeProduct(new Product("SKU001", "Large Widget", Money(123), Weight(6))),
		smallProduct(new Product("SKU002", "Small Widget", Money(4.56), Weight(0.10))),
		oneLarge(largeProduct, 1),
		oneSmall(smallProduct, 1),
		threeSmall(smallProduct, 3)
	{
	}

	virtual void SetUp()
	{
		order = OrderPtr(new TestableOrder("ACCOUNTID"));
	}

private:
	OrderTest(const OrderTest& rhs);
	OrderTest& operator=(const OrderTest& rhs);
};

TEST_F(OrderTest, testOrderId)
{
	ASSERT_TRUE(order->getOrderId() != "");
}

TEST_F(OrderTest, testEmpty)
{
	ASSERT_EQ(Money::zero(), order->getNetTotal());
	ASSERT_EQ(Weight::zero(), order->getWeight());
}

TEST_F(OrderTest, testSingleItemQuantityOne)
{
	order->add(oneLarge);
	ASSERT_EQ(Money(123), order->getNetTotal());
	ASSERT_EQ(Weight(6), order->getWeight());
}

TEST_F(OrderTest, testSingleItemQuantityThree)
{
	order->add(threeSmall);
	ASSERT_NEAR(13.68, order->getNetTotal().value(), 0.01);
	ASSERT_NEAR(0.3, order->getWeight().value(), 0.01);
}

TEST_F(OrderTest, testMultipleItemsSameQuantity)
{
	order->add(oneSmall);
	order->add(oneLarge);
	ASSERT_EQ(Money(127.56), order->getNetTotal());
	ASSERT_EQ(Weight(6.1), order->getWeight());
}

TEST_F(OrderTest, testMultipleItemsDifferentQuantities)
{
	order->add(threeSmall);
	order->add(oneLarge);
	ASSERT_EQ(Money(136.68), order->getNetTotal());
	ASSERT_EQ(Weight(6.3), order->getWeight());
}
