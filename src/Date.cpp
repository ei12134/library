#include <sstream>
#include "Date.h"
using namespace std;

Date::Date() {
	time_t t = time(0); // get time now
	struct tm * now = localtime(&t);
	setDate((now->tm_mday), (now->tm_mon + 1), (now->tm_year + 1900));
	// e preciso free the now ?
}

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
	setDate(day, month, year);
}

string Date::print() const {
	stringstream st;
	st << getDay() << "-" << getMonth() << "-" << getYear();
	return st.str();
}

void Date::setDate(unsigned int day, unsigned int month, unsigned int year) {
	if (month < 1 || month > 12)
		throw Exception<int>("Invalid Month", month); // throw exception <int> because of the template
	unsigned int days = GiveMonthDays(month, year);
	if (days == 0 || day < 1 || day > days)
		throw Exception<int>("Invalid Day", day); // throw exception <int> because of the template
	if (year < 2000)
		throw Exception<int>("Invalid Year(because of the julianDays method)",
				year); // throw exception <int> because of the template

	this->day = day;
	this->month = month;
	this->year = year;
}

void Date::addDays(unsigned int days) {
	while (days-- > 0)
		addOneDay();
}
void Date::addOneDay() {
	if (GiveMonthDays(this->month, this->year) >= (this->day + 1))
		this->day++;
	else if (this->month < 12) {
		this->day = 1;
		this->month++;
	} else {
		this->year++;
		this->month = this->day = 1;
	}
}

int Date::julianDays() const { // julian days days since 1/1/2000
	int a = (14 - month) / 12;
	int y = year + 4800 - a;
	int m = month + 12 * a - 3;
	if (year > 1582 || (year == 1582 && month > 10)
			|| (year == 1582 && month == 10 && day >= 15))
		return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400
				- 32045;
	else
		return day + (153 * m + 2) / 5 + 365 * y + y / 4 - 32083;
}

int Date::operator-(Date d2) const {
	return (this->julianDays() - d2.julianDays());
}

bool Date::operator <(Date d2) const {
	if (this->year < d2.year)
		return true;
	else if (this->year > d2.year)
		return false;
	else if (this->month < d2.month)
		return true;
	else if (this->month > d2.month)
		return false;
	else if (this->day < d2.day)
		return true;
	return false;
}

bool Date::operator >(Date d2) const {
	return d2 < (*this);
}

bool Date::operator ==(Date d2) const {
	return (this->year == d2.year) && (this->month == d2.month)
			&& (this->day == d2.day);
}

bool Date::operator !=(Date d2) const {
	return !(*this == d2);
}

bool isBissesto(unsigned int ano) {
	return (ano % 4 == 0 && ((ano % 100 != 0) || (ano % 400 == 0)));
}

unsigned int GiveMonthDays(unsigned int month, unsigned int year) {
	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 2:
		return isBissesto(year) ? 29 : 28;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	default:
		return 0; // false
	}
}

