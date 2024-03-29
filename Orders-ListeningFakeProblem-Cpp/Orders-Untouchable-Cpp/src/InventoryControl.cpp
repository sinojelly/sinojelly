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

#include "InventoryControl.h"
#include "Database.h"

InventoryControl::~InventoryControl()
{
}

InventoryControl* InventoryControl::get()
{
	return new InventoryControl;
}

void InventoryControl::reserveProduct(const std::string& /*orderId*/, 
		            const std::string& /*sku*/,
                    int /*quantity*/)
{
	Database::touchDatabase();
}

