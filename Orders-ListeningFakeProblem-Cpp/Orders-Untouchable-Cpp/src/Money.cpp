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

#include "Money.h"
#include <sstream>
#include <iomanip>

using namespace std;

const double Money::hundred(100.0);

Money::Money() : m_value(0.0)
{
}

Money::Money(int amount) : m_value(amount)
{
}

Money::Money(double amount) : m_value(amount)
{
}

Money::Money(const Money& v) : m_value(v.m_value)
{
}

double Money::value() const
{
	return m_value;
}

Money Money::add(const Money& augend) const
{
	return Money(m_value + augend.m_value);
}

Money Money::times(const Money amount) const
{
	return Money(m_value * amount.m_value);
}

Money Money::times(double amount) const
{
	return Money(m_value * amount);
}

Money Money::percentOf(const Money& amount) const
{
	return Money(m_value * amount.m_value / hundred);
}

Money Money::zero()
{
	Money zero(0.0);
	return zero;
}

int Money::compareTo(const Money& o) const
{
	if (m_value < o.m_value)
		return -1;
	if (m_value > o.m_value)
		return 1;
	return 0;
}

bool Money::equals(const Money& obj) const
{
	return m_value == obj.m_value;
}

std::string Money::toString() const
{
	stringstream ss (stringstream::in | stringstream::out);	
	ss << setprecision(2);
	ss << m_value;
	return ss.str();
}

