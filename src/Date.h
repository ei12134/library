#ifndef DATA_H_
#define DATA_H_

#include "Exception.h"// to handle the data exceptions xD#include <string>#include <ctime>using namespace std;
/**
 * Date Class
 * to handle dates in the program
 */
class Date {
private:
	/// day, month and year of the date hold by this class
	unsigned int day, month, year;
public:
	/** Date empty constructor gives the system date to the class */
	Date();

	/** Date constructor to initiate the date class with
	 * a specific date returns exception if date not valid*/
	Date(unsigned int day, unsigned int month, unsigned int year);

	/** changes the class date if date not valied returns exception
	 *@param unsigned int day, unsigned int month, unsigned int year
	 */
	void setDate(unsigned int day, unsigned int month, unsigned int year);

	///@return day
	unsigned int getDay() const {
		return day;
	}

	///@return month
	unsigned int getMonth() const {
		return month;
	}

	///@return year
	unsigned int getYear() const {
		return year;
	}

	/** add days to the class date
	 *@param unsigned int days
	 */
	void addDays(unsigned int days);

	/** return the number of days of a date since 1/1/2000 */
	int julianDays() const;

	/** add one day to the class date */
	void addOneDay();

	/** removes one day to the class date */
	void removeOneDay();

	/** returns string with the date of this class dd-mm-yyyy */
	string print() const;

	/*
	 * return the difference between dates in days
	 */
	int operator-(Date d2) const;

	/** check if date is lower that d2
	 *@param Date d2
	 */
	bool operator<(Date d2) const;

	/** check if date is bigger that d2
	 *@param Date d2
	 */
	bool operator>(Date d2) const;

	/** check if date is equal to d2
	 *@param Date d2
	 */
	bool operator==(Date d2) const;

	/** check if date is different of d2
	 *@param Date d2
	 */
	bool operator!=(Date d2) const;

	/** postfix operator increments date by one day
	 *@param postfix convention
	 */
	Date operator++(int);

	/** postfix operator decrements date by one day
	 *@param postfix convention
	 */
	Date operator--(int);
};

/** return true if ano is bissesto false if not
 *@param unsigned int ano
 */
bool isBissesto(unsigned int ano);

/** returns months in a given month of a year
 *@param unsigned int month, unsigned int year
 */
unsigned int GiveMonthDays(unsigned int month, unsigned int year);

#endif
