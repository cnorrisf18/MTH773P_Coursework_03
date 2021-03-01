#include "Date.h"
#include "Calendar.h"
#include <iostream>

using namespace std;

//main function for question 1

int main1()
{
	Date dt(9, 2, 2021);

	//test part (a)
	cout << "TESTING PART A" << endl;
	unsigned int d, m, y;
	dt.getDMY(d, m, y); //passed by reference
	unsigned int serial = dt.getSerial();
	cout << d << "/" << m << "/" << y <<"\t" <<  serial << endl;

	//test part (b)
	cout << "TESTING PART B" << endl;
	Date go_back(31, 3, 2021);
	go_back.addMonths(-3);
	go_back.getDMY(d, m, y);
	cout << d << "/" << m << "/" << y <<  ", Should be 31/12/2020" << endl;
	go_back.addDays(400);
	go_back.getDMY(d, m, y);
	cout << d << "/" << m << "/" << y << ", Should be 4/2/2022" << endl;
	Date go_forward(31, 10, 2022);
	go_forward.addMonths(4);
	go_forward.getDMY(d, m, y);
	cout << d << "/" << m << "/" << y  << ", Should be 28/2/2023" << endl;
	go_forward.addYears(1);
	go_forward.getDMY(d, m, y);
	cout << d << "/" << m << "/" << y  << ", Should be 28/2/2024" << endl;
	go_forward.addDays(1);
	go_forward.getDMY(d, m, y);
	cout << d << "/" << m << "/" << y << ", Should be 29/2/2024" << endl;
	go_forward.addYears(-1);
	go_forward.getDMY(d, m, y);
	cout << d << "/" << m << "/" << y << ", Should be 28/2/2023" << endl;

	//test part c
	cout << "TESTING PART C" << endl;
	cout << go_forward - go_back << ", Should be 389" << endl;
	cout << go_back - go_forward << ", Should be -389" << endl;

	//test part d
	cout << "TESTING PART D" << endl;
	cout << "Values should be Sunday-Sunday" << endl;
	for (int i = 7; i < 15; i++) {
		Date wdt(i, 2, 2021);
		wdt.printDate();
		wdt.printWeekday();
		cout << "Weekday is " << wdt.weekday() << endl;
	}
	Date gbdt(12, 2, 2021);
	Date gbdt2(29, 5, 2021);
	gbdt.rollToGBD();
	gbdt2.rollToGBD();
	gbdt.printDate();
	cout << "Should be 12/2/2021" << endl;
	gbdt2.printDate();
	cout << "Should be 31/5/2021" << endl;

	//test part e
	cout << "TESTING PART E" << endl;
	gbdt.addBusinessDays(10);
	gbdt.printDate();
	cout << "Should be 26/2/2021" << endl;

	//test part f
	cout << "TESTING PART F" << endl;
	Date edt1(2, 10, 2021);
	Date edt2(2, 11, 2021);
	++edt1;
	bool equal = edt1 != edt2;
	cout << "Whether dates are equal (should be true/1): " << equal << endl;

	//test part g
	cout << "TESTING PART G" << endl;
	Calendar testcal;
	testcal.addHoliday(edt1);
	cout << testcal.isHoliday(edt1) << ", should be 1, " << testcal.isHoliday(edt2) << ", should be 0" << endl;

	//test part h
	cout << "TESTING PART H" << endl;
	Date gbdc (2, 13, 2021);
	cout << gbdc.isGBD(testcal) << ", should be 0" << endl;
	gbdc.rollToGBD(testcal);
	cout << gbdc.isGBD(testcal) << ", should be 1" << endl;

	return 0;
}



//main() function for question 2
int main2()
{
	//Question 2 part a
	Date swapstart(9, 1, 2017);
	Calendar paymentcal;
	for (int i = 0; i < 10; i++)
	{
		for (int i = 0; i < 4; i++)
		{
			swapstart.addMonths(3);
			swapstart.rollToGBD();
			paymentcal.addHoliday(swapstart);
		}
	}
	//paymentcal.printCal();

	//Question 2 part b
	Date loopend(1, 1, 2000);
	Calendar first_sundays;
	int sunday_count = 0;
	for (Date loopstart(1, 1, 1950); loopstart != loopend; ++loopstart)
	{
		unsigned int d, m, y;
		loopstart.getDMY(d, m, y);
		if (d == 1)
		{
			if (loopstart.weekday() == SUNDAY)
			{
				++sunday_count;
				first_sundays.addHoliday(loopstart);
			}
		}
	}
	cout << sunday_count << endl;
	//first_sundays.printCal();

	//Question 2 part c
	Calendar HolidaysCal;
	vector<Date> BankHolidays = { Date(2,1,2017), Date(17,3,2017), Date(14,4,2017), Date(17,4,2017), Date(1,5,2017), Date(29,5,2017), Date(12,7,2017), Date(7,8,2017), Date(28,8,2017), Date(30,11,2017), Date(25,12,2017), Date(26, 12, 2017) };
	for (int i = 0; i < BankHolidays.size(); ++i)
	{
		HolidaysCal.addHoliday(BankHolidays[i]);
	}
	Date yearloop(1, 1, 2017);
	vector<int> gbdvec;
	for (int i = 1; i < 13; ++i)
	{
		int gbdcount = 0;
		unsigned int d, m, y;
		yearloop.getDMY(d, m, y);
		while (m == i)
		{
			if (yearloop.isGBD(HolidaysCal))
			{
				++gbdcount;
			}
			++yearloop;
			yearloop.getDMY(d, m, y);
		}
		//cout << gbdcount << endl;
		gbdvec.push_back(gbdcount);
	}
	int highest_gbd = 0;
	for (int i = 0; i < gbdvec.size(); ++i) ///loop over the vector twice, once to get the highest day number and second to get the actual months
	{
		if (gbdvec[i] > highest_gbd)
		{
			highest_gbd = gbdvec[i];
		}
	}
	vector<int> Highest_GBD_Months;
	for (int i = 0; i < gbdvec.size(); ++i)
	{
		if (highest_gbd == gbdvec[i])
		{
			Highest_GBD_Months.push_back(i + 1); //we need to add 1 since the indexing starts at 0, and we are starting at 1
		}
	}
	//print the final vector
	for (int i = 0; i < Highest_GBD_Months.size(); ++i)
	{
		cout << "The month " << Highest_GBD_Months[i] << " had the most good business days in 2017" << endl;
	}
	return 0;
}

int main()
{
	int question = 2;
	cout << "What question do you want to run?" << endl;
	cin >> question;
	switch (question)
	{
	case 1:
		main1();
		return 0;
	case 2:
		main2();
		return 0;
	default:
		main2();
		return 0;
	}
}