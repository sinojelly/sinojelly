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

#ifndef ORDER_H_
#define ORDER_H_

#include <vector>
#include <string>

#include "IdGenerator.h"
#include "InventoryControl.h"
#include "Money.h"
#include "Weight.h"
#include "LineItem.h"
#include "counted_ptr.h"

typedef std::vector<LineItem> LineItemVector;
typedef LineItemVector::const_iterator LineItemIterator;

class Order 
{
public:
	Order(const std::string& accountId);

	Order(const std::string& accountId, const std::string& orderId);

	virtual ~Order();

	virtual void add(const LineItem& item);

	virtual LineItemIterator getItems() const;

	virtual LineItemIterator endItems() const;

	virtual Money getNetTotal() const;

	virtual Weight getWeight() const;

	virtual std::string getOrderId() const;

protected:
	virtual void reserveProduct(const LineItem& item) const;

	virtual std::string getOrderIdFromGenerator() const;

private:
	Money m_netTotal;
	Weight m_weight;
	LineItemVector m_items;

protected:
	std::string m_accountId;
	mutable std::string m_orderId;
};

typedef counted_ptr<Order> OrderPtr;

#endif
