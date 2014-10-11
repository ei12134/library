#ifndef DATA_H_
#define DATA_H_

//#include "Exception.h"// to handle the data exceptions xD
#include <string>
using namespace std;

class Data {
private:
	unsigned int day, month, year;
public:
	Data():day(1),month(1),year(2000){};
	Data(unsigned int day, unsigned int month, unsigned int year);

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

	string imprime() const;

	bool operator <(Data d2) const;
	bool operator >(Data d2) const;
	bool operator ==(Data d2) const;
	bool operator !=(Data d2) const;

};

bool isBissesto(unsigned int ano);
unsigned int GiveMonthDays(unsigned int month, unsigned int year);

#endif
