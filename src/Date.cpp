#include <sstream>
#include "Date.h"
using namespace std;

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
	setDate(day, month, year);
}

string Date::imprime() const {
	stringstream st;
	st << getDay() << "-" << getMonth() << "-" << getYear();
	return st.str();
}

void Date::setDate(unsigned int day, unsigned int month, unsigned int year) {
//	if (month < 1 || month > 12)
//		throw Exception<int>("Invalid Month", month); // throw exception <int> because of the template
//	unsigned int days = GiveMonthDays(month, year);
//	if (days == 0 || day < 1 || day > days)
//		throw Exception<int>("Invalid Day", day); // throw exception <int> because of the template

	this->day = day;
	this->month = month;
	this->year = year;
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
