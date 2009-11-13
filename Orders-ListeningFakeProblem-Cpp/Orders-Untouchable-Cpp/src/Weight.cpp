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

#include <sstream>
#include <iomanip>

#include "Weight.h"
#include "Money.h"

using namespace std;

const double Weight::hundred(100.0);

Weight::Weight() : m_value(0.0)
{
}

Weight::Weight(int amount) : m_value(amount)
{
}

Weight::Weight(double amount) : m_value(amount)
{
}

Weight::Weight(const Weight& v) : m_value(v.m_value)
{
}

double Weight::value() const
{
	return m_value;
}

Weight Weight::add(const Weight& augend) const
{
	return Weight(m_value + augend.m_value);
}

Weight Weight::times(const Weight& amount) const
{
	return Weight(m_value * amount.m_value);
}

Money Weight::times(const Money& amount) const
{
	return Money(m_value * amount.value());
}

Weight Weight::percentOf(const Weight& amount) const
{
	return Weight(m_value * amount.m_value / hundred);
}

Weight Weight::zero()
{
	Weight zero(0.0);
	return zero;
}

int Weight::compareTo(const Weight& o) const
{
	if (m_value < o.m_value)
		return -1;
	if (m_value> o.m_value)
		return 1;
	return 0;
}

bool Weight::equals(const Weight& obj) const
{
	return m_value == obj.m_value;
}

std::string Weight::toString() const
{
	stringstream ss (stringstream::in | stringstream::out);	
	ss << setprecision(2);
	ss << m_value;
	return ss.str();
}
