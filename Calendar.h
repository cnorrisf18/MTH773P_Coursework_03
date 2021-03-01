#pragma once

#include <vector>
#include "Date.h"

class Calendar
{
public:
	Calendar();
	void addHoliday( Date date);
	bool isHoliday( Date date);
	void printCal();
private:
	vector< Date> m_HolidayList;
};