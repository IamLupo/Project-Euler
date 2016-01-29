#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/*
	How many Sundays fell on the first of the month during the twentieth century
	(1 Jan 1901 to 31 Dec 2000)?
*/

enum Days { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };
char * daysOfWeek[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saterday" };
int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int daysPerYear = 365;

struct Date {
	int day;
	int month;
	int year;
};

int isLeapYear(int year) {
	if (year % 400 == 0) {
		return 1;
	} else if (year % 100 == 0) {
		return 0;
	} else if (year % 4 == 0) {
		return 1;
	} else {
		return 0;
	}
}

int cmpDate(struct Date* a, struct Date* b) {
	//Year
	if(a->year > b->year)	return 1;
	if(a->year < b->year)	return -1;
	
	//Month
	if(a->month > b->month)	return 1;
	if(a->month < b->month)	return -1;
	
	//Day
	if(a->day > b->day)	return 1;
	if(a->day < b->day)	return -1;
	
	return 0;
}

int getDaysByDates(struct Date* begin, struct Date* end) {
	int days;
	struct Date temp;
	bool ibm, sm;
	
	//Init
	days = 0;
	ibm = true;
	sm = false;
	
	temp.day = begin->day;
	temp.month = begin->month;
	temp.year = begin->year;
	
	//Look if begin date is before march
	if(begin->month > 2)
		ibm = false;
	
	//Look if begin and end date is in same month
	if(begin->month > 2)
		sm = true;
	
	//Add years
	while(temp.year != end->year) {
		/*
			A year must not be added because begin data has to high month
			begin:	1-2-2012
			end:	1-1-2013
		*/
		if(	temp.year + 1 == end->year &&
			begin->month > end->month)
			break;
		
		/*
			A year must not be added because begin month is the same
			and begin day is higher then the end day
			begin:	8-2-2012
			end:	1-2-2013
		*/
		if(	temp.year + 1 == end->year &&
			begin->month == end->month &&
			begin->day > end->day)
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
	while(temp.month != end->month || temp.year != end->year) {
		/*
			A month must not be added because begin day has a higher end day
			begin:	2-1-2013
			end:	1-2-2013
			
			begin:	2-12-2012
			end:	1-1-2013
		*/
		if(	(temp.month + 1 == end->month || temp.month - 11 == end->month) &&
			begin->day > end->day)
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
	while(temp.day != end->day || temp.month != end->month || temp.year != end->year) {
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

enum Days getDayByDate(struct Date* input) {
	int cmp;
	enum Days known_day = MONDAY;
	struct Date known_date = {1, 1, 2001};
	
	//Init
	cmp = cmpDate(input, &known_date);
	if(cmp < 0) {
		return ((7 + known_day) - (getDaysByDates(input, &known_date) % 7)) % 7;
	} else if(cmp > 0) {
		return (known_day + getDaysByDates(&known_date, input)) % 7;
	} else {
		return 0;
	}
}

int sumSundayFirstOfTheMonth(struct Date* begin, struct Date* end) {
	int sum;
	
	//Init
	sum = 0;
	
	while(cmpDate(begin, end) < 0) {
		if(getDayByDate(begin) == SUNDAY) {
			sum++;
			printf("%d-%d-%d %s\n", begin->day, begin->month, begin->year, daysOfWeek[SUNDAY]);
		}
		
		//Add Month
		if(begin->month != 12)
			begin->month++;
		else {
			begin->month = 1;
			begin->year++;
		}
	}
	
	return sum;
}

int main() {
	struct Date begin = {1, 1, 1901}; // Tuesday
	struct Date end = {31, 12, 2000}; // Sunday
	
	printf("Sundays = %d\n", sumSundayFirstOfTheMonth(&begin, &end));
	
	return 0;
}