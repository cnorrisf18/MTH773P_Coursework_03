#include "basic.h"
#include "Date.h"
#include "Calendar.h"
#include <iostream>
#include <map>
using namespace std;


//DATE CLASS
Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	unsigned int serial = DMY_to_serial(day, month, year);
	m_serial = serial;
}
Date::Date(unsigned int serial)
{
	m_serial = serial;
}
int Date::operator-(Date rhs)
{
	unsigned int rhs_serial = rhs.getSerial();
	int daysDiff = m_serial - rhs_serial;
	return daysDiff;
}
Date Date::operator++(){
	addDays(1);
	return *this;
}
bool Date::operator!=(Date rhs) {
	if (m_serial == rhs.getSerial())
	{
		return false;
	}
	return true;
}
bool Date::operator==(Date rhs)
{
	if (m_serial == rhs.getSerial())
	{
		return true;
	}
	return false;
}
void Date::printDate() {
	unsigned int d, m, y;
	getDMY(d, m, y);
	cout << d << "/" << m << "/" << y << endl;
}
void Date::printWeekday(){
	Weekday wd = weekday();
	const char* DayNames[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	cout << DayNames[wd-1] << endl;
}
void Date::addDays(int days)
{
	m_serial += days;
	return;
}
void Date::addMonths(int months)
{
	unsigned int d, m, y;
	getDMY(d, m, y);
	int feb_days = 28;
	//find out what month it will be after the addition/subtraction

	//separate the months value into years and months
	int num_years = months / 12;  //this will return the number of years, rounded down
	int num_months = months % 12; //this will return the remainder after dividing by 12, i.e. the number of months

	y = y + num_years;
	m = m + num_months;
	//do checks for odd situations
	if (m <= 0) //we are going back a year
	{
		y = y - 1;
		m = m + 12; //the month will be its negative value plus 12, to get an actual value for a month
	}
	if (m > 12) //we are going forward a year
	{
		y = y + 1;
		m = m - 12; //subtract m by 12 to get an actual month value
	}
	if (isLeapYear(y))
	{
		feb_days = 29;
	}
	if (d > feb_days && m == 2) //there may be a situation where simply adding a month would return a date in feb that doesn't exist 
	{
		d = feb_days;
	}
	if (d > 30 && (m == 4 || m == 6 || m == 9 || m == 11)) //the month is April, June, September, or November, which all have only 30 days
	{
		d = 30;
	}
	//get our serial number back
	m_serial = DMY_to_serial(d, m, y);
	return;
}
void Date::addYears(int years)
{
	addMonths(years * 12);
	return;
}

Weekday Date::weekday() {
	int week_int = m_serial % 7;
	if (week_int == 0) {
		week_int = 7;
	}
	Weekday returned_day = static_cast<Weekday>(week_int);
	return returned_day;
}

bool Date::isWeekend() {
	bool weekend = false;
	if (weekday() == SATURDAY || weekday() == SUNDAY)
	{
		weekend = true;
	}
	return weekend;
}

bool Date::isGBD() //check whether it's a good business day (whether markets are open or not)
{
	return (not isWeekend());
}
//bool isGBD(Calendar calendar); //overloading previous isGBD function

bool Date::isGBD(Calendar& calendar) {

	if (isWeekend() || calendar.isHoliday(*this))
	{
		return false;
	}
	return true;
}

void Date::rollToGBD()
{
	if (isGBD())
	{
		return;
	}
	else
	{
		bool gbd = false;
		while (not gbd)
		{
			m_serial += 1;
			gbd = isGBD();
		}
		return;
	}
}

void Date::rollToGBD(Calendar& calendar) {
	if (isGBD(calendar))
	{
		return;
	}
	else
	{
		bool gbd = false;
		while (not gbd)
		{
			m_serial += 1;
			gbd = isGBD(calendar);
		}
		return;
	}
}
void Date::addBusinessDays(int days)
{
	for (int i = 0; i < days; i++)
	{
		m_serial += 1;
		if (isWeekend())
		{
			rollToGBD();
		}
	}
	return;
}
void Date::getDMY(unsigned int& date, unsigned int& month, unsigned int& year) 
{
	serial_to_DMY(m_serial, date, month, year);
}