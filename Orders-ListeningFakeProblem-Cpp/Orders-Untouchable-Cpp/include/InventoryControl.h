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

#ifndef INVENTORY_CONTROL_H_
#define INVENTORY_CONTROL_H_

#include <string>

class InventoryControl
{
public:
	virtual ~InventoryControl();

	static InventoryControl* get();

	virtual void reserveProduct(const std::string& orderId, const std::string& sku, int quantity);
};

#endif
