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

#ifndef SHIPPING_OPTION_H_
#define SHIPPING_OPTION_H_

#include "Money.h"
#include "Weight.h"
#include "counted_ptr.h"

class ShippingOption 
{
	public:
		static const ShippingOption AIR;
		static const ShippingOption GROUND;
		static const ShippingOption SUPER_SAVER;
		static const ShippingOption NEXT_DAY;

		Money rate(const Weight& weight) const;

	private:
		Money m_rate;

		ShippingOption(const Money& rate);
};

#endif
