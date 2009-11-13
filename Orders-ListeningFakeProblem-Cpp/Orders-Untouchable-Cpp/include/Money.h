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

#ifndef MONEY_H_
#define MONEY_H_

#include <string>
#include <iostream>

class Money  // implements Comparable<Money> {
{
public:
	Money();
	
	Money(int amount);
	
	Money(double amount);
	
	Money(const Money& v);

	double value() const;
   
	Money add(const Money& augend) const;

	Money times(const Money amount) const;
	
	Money times(double amount) const;
	
	Money percentOf(const Money& amount) const;
	
	static Money zero();

	int compareTo(const Money& o) const;

	bool equals(const Money& obj) const;

	std::string toString() const;

private:
	static const double hundred;

	double m_value;
};

inline bool operator<(const Money& lhs, const Money& rhs)
{
	return lhs.compareTo(rhs) < 0;
}

inline bool operator<=(const Money& lhs, const Money& rhs)
{
	return lhs.compareTo(rhs) <= 0;
}

inline bool operator>(const Money& lhs, const Money& rhs)
{
	return lhs.compareTo(rhs) > 0;
}

inline bool operator>=(const Money& lhs, const Money& rhs)
{
	return lhs.compareTo(rhs) >= 0;
}

inline bool operator==(const Money& lhs, const Money& rhs)
{
	return lhs.equals(rhs);
}

inline bool operator!=(const Money& lhs, const Money& rhs)
{
	return lhs.equals(rhs);
}

inline std::ostream& operator<<(std::ostream& ostr, const Money& rhs)
{
	ostr << "Money(" << rhs.value() << ")";
	return ostr;
}

#endif  // MONEY_H_
