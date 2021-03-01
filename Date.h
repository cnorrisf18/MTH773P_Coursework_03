#pragma once
#include <set>

using namespace std;
class Calendar;

enum Weekday:int
{
	SUNDAY = 1,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};


class Date
{
public:
	//make sure to account for leap years
	Date(unsigned int day, unsigned int month, unsigned int year); //constructor should take three values for day, month, year and turn them into a serial number
	Date(unsigned int serial);
	void printDate();
	void printWeekday();
	int  operator-(Date rhs);
	Date operator++();
	bool operator!=(Date rhs);
	bool operator==(Date rhs);
	void addDays(int days);
	void addMonths(int months);
	void addYears(int years);
	Weekday weekday();
	bool isWeekend(); //check whether it's a weekend
	bool isGBD(); //check whether it's a good business day (whether markets are open or not)
	void rollToGBD();
	void addBusinessDays(int days);
	bool isGBD( Calendar& calendar); //overloading previous isGBD function 
	void rollToGBD( Calendar& calendar); //overload previous rollToGBD function
	void getDMY(unsigned int& date, unsigned int& month, unsigned int& year);
	unsigned int getSerial() { return m_serial; };
private:
	unsigned int m_serial;
};
