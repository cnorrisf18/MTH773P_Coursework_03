#include "Calendar.h"
#include "Date.h"
#include <iostream>
using namespace std;

//CALENDAR CLASS

Calendar::Calendar()
{
	//m_HolidayList = {};
}

void Calendar::addHoliday( Date date) {
	m_HolidayList.push_back(date);
	return;
}
void Calendar::printCal()
{
	for (int i = 0; i < m_HolidayList.size(); i++)
	{
		m_HolidayList[i].printDate();
	}
}
bool Calendar::isHoliday( Date date) {

	vector< Date>::iterator it;

	it = find(m_HolidayList.begin(), m_HolidayList.end(), date);

	if (it != m_HolidayList.end())
	{
		return true;
	}
	return false;

}




