#ifndef DATA_H_
#define DATA_H_

#include "Exception.h"// to handle the data exceptions xD
#include <string>
#include <ctime>

using namespace std;

class Date {
private:
	unsigned int day, month, year;
public:
	Date();
	Date(unsigned int day, unsigned int month, unsigned int year);

	void setDate(unsigned int day, unsigned int month, unsigned int year);

	unsigned int getDay() const {
		return day;
	}
	unsigned int getMonth() const {
		return month;
	}
	unsigned int getYear() const {
		return year;
	}

	void addDays(unsigned int days);
	void addOneDay();

	string print() const;

	bool operator <(Date d2) const;
	bool operator >(Date d2) const;
	bool operator ==(Date d2) const;
	bool operator !=(Date d2) const;

};

bool isBissesto(unsigned int ano);
unsigned int GiveMonthDays(unsigned int month, unsigned int year);

#endif
