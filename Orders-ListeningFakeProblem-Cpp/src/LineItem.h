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

#ifndef LINE_ITEM_H_
#define LINE_ITEM_H_

#include "Money.h"
#include "Weight.h"
#include "Product.h"
#include "counted_ptr.h"
#include <string>

class LineItem 
{
public:
	LineItem(ProductPtr product, int quantity);
	
	virtual ~LineItem();

	virtual int getQuantity() const;

	virtual std::string getText() const;

	virtual Money getItemAmount() const;

	virtual Money getExtendedAmount() const;

	virtual Weight getExtendedWeight() const;

	virtual std::string getSku() const;

private:
	int m_quantity;
	ProductPtr m_product;
};

#endif
