#ifndef BORROW_H_
#define BORROW_H_

class Reader;
class Employee;

#include "Book.h"
#include "Date.h"
#include "./Persons/Person.h"
#include "./Persons/Employee.h"
using namespace std;

class Borrow {
protected:
	Book* book;
	Person* employee;
	Person* reader;
	Date borrowDate;
	Date returnDate;
	Date limitReturnDate;
	bool returned;
	unsigned long int ID;

public:
	Borrow(Book* book, Person* employee, Person* reader, Date borrowDate,
			Date limitReturnDate);
	static unsigned long int borrowID;
	unsigned long int getID() const;
	Book* getBook() const;
	Person* getEmployee() const;
	Person* getReader() const;
	void setReturned(bool returned);

	string print() const;
	string printShort() const;
	float CalcFee() const;
	bool isReturned() const;
	bool DeliveredBook(Date d); // false if already returned
	void saveData(ofstream &pFile);
};

#endif
