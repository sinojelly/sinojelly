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

#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <string>
#include "Money.h"
#include "Weight.h"
#include "counted_ptr.h"

class Product
{
public:
	Product(const std::string& sku, 
			const std::string& description, 
			const Money& basePrice, 
			const Weight& baseWeight);

	virtual ~Product();

	virtual std::string getSku() const;

	virtual std::string getDescription() const;

	virtual Money getBasePrice() const;

	virtual Weight getBaseWeight() const;

private:
	Weight m_baseWeight;
	Money m_basePrice;
	std::string m_sku;
	std::string m_description;
};

typedef counted_ptr<Product> ProductPtr;

#endif
