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

#ifndef WEIGHT_H_
#define WEIGHT_H_

#include "Money.h"

#include <string>
#include <algorithm>
#include <iostream>

class Weight
{
public:
	Weight();

	Weight(int amount);

	Weight(double amount);

	Weight(const Weight& v);

	double value() const;

	Weight add(const Weight& augend) const;

	Weight times(const Weight& amount) const;

	Money times(const Money& amount) const;

	Weight percentOf(const Weight& amount) const;

	static Weight zero();

	int compareTo(const Weight& o) const;

	bool equals(const Weight& obj) const;

	std::string toString() const;

private:
	static const double hundred;
	double m_value;
};

inline bool operator<(const Weight& lhs, const Weight& rhs)
{
	return lhs.compareTo(rhs) < 0;
}

inline bool operator<=(const Weight& lhs, const Weight& rhs)
{
	return lhs.compareTo(rhs) <= 0;
}

inline bool operator>(const Weight& lhs, const Weight& rhs)
{
	return lhs.compareTo(rhs) > 0;
}

inline bool operator>=(const Weight& lhs, const Weight& rhs)
{
	return lhs.compareTo(rhs) >= 0;
}

inline bool operator==(const Weight& lhs, const Weight& rhs)
{
	return lhs.equals(rhs);
}

inline bool operator!=(const Weight& lhs, const Weight& rhs)
{
	return lhs.equals(rhs);
}

inline Weight operator+(const Weight& lhs, const Weight& rhs)
{
	return lhs.add(rhs);
}

inline Weight operator*(const Weight& lhs, const Weight& rhs)
{
	return lhs.times(rhs);
}

inline Money operator*(const Weight& lhs, const Money& rhs)
{
	return lhs.times(rhs);
}

inline std::ostream& operator<<(std::ostream& ostr, const Weight& rhs)
{
	ostr << "Weight(" << rhs.value() << ")";
	return ostr;
}

#endif  // WEIGHT_H_
