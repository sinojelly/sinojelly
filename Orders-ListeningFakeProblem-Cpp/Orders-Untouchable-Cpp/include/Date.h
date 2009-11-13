
/// <summary>
/// ***************************************************************************
/// Copyright (c) 2006, Industrial Logic, Inc., All Rights Reserved.
///
/// This code is the exclusive property of Industrial Logic, Inc. It may ONLY be
/// used by students during Industrial Logic's workshops or by individuals
/// who are being coached by Industrial Logic on a project.
///
/// This code may NOT be copied or used for any other purpose without the prior
/// written consent of Industrial Logic, Inc.
/// ****************************************************************************
/// </summary>


#ifndef __DATE_H__
#define __DATE_H__


#include <stdlib.h>

class Date
{
public:
	Date(int year, int month, int day) : m_year(year), m_month(month), m_day(day)
	{}

	Date() : m_year(YEAR_MAX), m_month(MONTH_MAX), m_day(DAY_MAX)
	{}

	double operator - (const Date& earlierDate) const
	{
		return ::abs( getNumberOfDaysSinceDateMin() 
						- earlierDate.getNumberOfDaysSinceDateMin());
	}

	bool operator == (const Date& date) const
	{
		return isEqual(date);
	}

	bool operator != (const Date& date) const
	{
		return !isEqual(date);
	}

	static const int YEAR_MIN = 1900;
	static const int YEAR_MAX = 2999;
	static const int MONTH_MIN = 1;
	static const int MONTH_MAX = 12;
	static const int DAY_MIN = 1;
	static const int DAY_MAX = 31;


	// Private/Test interface below this point. Only public to allow unit testing

	int getNumberOfDaysSinceDateMin() const
	{
		int days = 0;
		days += getNumberOfDaysDueToYearsSinceYearMin();
		days += getNumberOfDaysDueToMonthSinceMonthMin();
		days += m_day - 1;
		return days;
	}

	int getNumberOfDaysDueToYearsSinceYearMin() const
	{
		int days = 0;

		for (int yearIndex = YEAR_MIN; yearIndex < m_year; yearIndex++)
		{
			if (isLeapYear(yearIndex))
				days += DAYS_IN_NON_LEAP_YEAR + 1;
			else 
				days += DAYS_IN_NON_LEAP_YEAR;
		}
		
		return days;
	}

	int getNumberOfDaysDueToMonthSinceMonthMin() const
	{
		int days = 0;

		int daysInMonthForNonLeapYear[] = {31, 28, 31, 30, 31, 30, 
											31, 31, 30, 31, 30, 31}; 

		for (int monthIndex = 1; monthIndex < m_month; monthIndex++)
		{
			days += daysInMonthForNonLeapYear[monthIndex - 1];
			
			if ((monthIndex == 2) && isLeapYear(m_year))
				days += 1;
		}

		return days;
	}

	static bool isLeapYear(int year)
	{
		// Leap Year as defined by Webster's New Universal Unabridged Dictionary
		return (year%4 == 0) && !((year%100 ==0) && (year%400 !=0));
	}

private:

	bool isEqual(const Date& date) const
	{
		return	(m_year == date.m_year) 
				&& (m_month == date.m_month)
				&& (m_day == date.m_day);
	};

	int m_year;
	int m_month; // 1-12
	int m_day; // 1-31

	static const int DAYS_IN_NON_LEAP_YEAR = 365;
};

#endif // __DATE_H__
