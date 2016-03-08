#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	How many Sundays fell on the first of the month during the twentieth century
	(1 Jan 1901 to 31 Dec 2000)?
*/

enum Day {
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

vector<string> daysOfWeek = {
	"Sunday", "Monday", "Tuesday", "Wednesday",
	"Thursday", "Friday", "Saterday"
};

vector<int> daysPerMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int daysPerYear = 365;

struct Date {
	int day;
	int month;
	int year;
};

bool isLeapYear(int y) {
	if(y % 400 == 0 || (y % 100 != 0 && y % 4 == 0))
		return true;
	
	return false;
}

/*
	1 = Date "a" is later date
	0 = a and b are the Same Date
	-1 = Date "b" is later date
*/
int cmp(const Date &a, const Date &b) {
	//Year
	if(a.year > b.year)	return 1;
	if(a.year < b.year)	return -1;
	
	//Month
	if(a.month > b.month)	return 1;
	if(a.month < b.month)	return -1;
	
	//Day
	if(a.day > b.day)	return 1;
	if(a.day < b.day)	return -1;
	
	return 0;
}

int getDaysByDates(const Date &begin, const Date &end) {
	int days;
	Date temp;
	bool ibm, sm;
	
	//Init
	days = 0;
	ibm = true;
	sm = false;
	
	temp.day = begin.day;
	temp.month = begin.month;
	temp.year = begin.year;
	
	//Look if begin date is before march
	if(begin.month > 2)
		ibm = false;
	
	//Look if begin and end date is in same month
	if(begin.month > 2)
		sm = true;
	
	//Add years
	while(temp.year != end.year) {
		/*
			A year must not be added because begin data has to high month
			begin:	1-2-2012
			end:	1-1-2013
		*/
		if(	temp.year + 1 == end.year &&
			begin.month > end.month)
			break;
		
		/*
			A year must not be added because begin month is the same
			and begin day is higher then the end day
			begin:	8-2-2012
			end:	1-2-2013
		*/
		if(	temp.year + 1 == end.year &&
			begin.month == end.month &&
			begin.day > end.day)
			break;
		
		//Add 365 days
		days += daysPerYear;
		
		//Look for leap years
		if(ibm && isLeapYear(temp.year))
			days++;
		else if(!ibm && isLeapYear(temp.year + 1))
			days++;
		
		temp.year++;
	}
	
	//Add Months
	while(temp.month != end.month || temp.year != end.year) {
		/*
			A month must not be added because begin day has a higher end day
			begin:	2-1-2013
			end:	1-2-2013
			
			begin:	2-12-2012
			end:	1-1-2013
		*/
		if(	(temp.month + 1 == end.month || temp.month - 11 == end.month) &&
			begin.day > end.day)
			break;
		
		days += daysPerMonth[temp.month - 1];
		
		//Add one day when Februari is in a Leap year
		if(temp.month == 2 && isLeapYear(temp.year))
			days++;
		
		if(temp.month != 12)
			temp.month++;
		else {
			temp.month = 1;
			temp.year++;
		}
	}
	
	//Add Day
	while(temp.day != end.day || temp.month != end.month || temp.year != end.year) {
		days++;
		
		temp.day++;
		
		if(temp.month == 2 && temp.day == 29 && isLeapYear(temp.year)) {
			
		}
		else if(temp.day > daysPerMonth[temp.month - 1]) {
			temp.day = 1;
			
			if(temp.month != 12)
				temp.month++;
			else {
				temp.month = 1;
				temp.year++;
			}
		}
	}
	
	return days;
}

Day getDay(const Date &d) {
	Day day = MONDAY;
	Date date = {1, 1, 2001};
	
	//Init
	switch(cmp(d, date)) {
		case 1:
			return (Day)((day + getDaysByDates(date, d)) % 7);
		break;
		case -1:
			return (Day)(((7 + day) - (getDaysByDates(d, date) % 7)) % 7);
		break;
	}
	
	return Day::SATURDAY;
}

int sumSundayFirstOfTheMonth(const Date &begin, const Date &end) {
	int r;
	Date t;
	
	//Init
	r = 0;
	t = begin;
	
	while(cmp(t, end) < 0) {
		if(getDay(t) == SUNDAY) {
			r++;
			
			//Debug
			//cout << t.day << "-" << t.month << "-" << t.year
			//	<< " " << daysOfWeek[Day::SUNDAY] << endl;
		}
		
		//Add Month
		if(t.month != 12)
			t.month++;
		else {
			t.month = 1;
			t.year++;
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << sumSundayFirstOfTheMonth({1, 1, 1901}, {31, 12, 2000}) << endl;
	
	return 0;
}