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

#ifndef SHIPPER_H_
#define SHIPPER_H_

#include <string>
#include "Weight.h"
#include "ShippingOption.h"
#include "Money.h"
#include "counted_ptr.h"

class Shipper
{
public:
	Shipper(const std::string& orderId, const ShippingOption& option);
	virtual ~Shipper();

	virtual Money total() const;

	virtual void addItem(const std::string& sku, int quantity, const Weight& weight);

private:
	const ShippingOption& m_option;
	Weight m_weightAccumulator;

private:
	// declare unimplemented
	Shipper(const Shipper& rhs);
	Shipper& operator=(const Shipper& rhs);
};

typedef counted_ptr<Shipper> ShipperPtr;


#endif

