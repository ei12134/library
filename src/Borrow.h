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
	Employee* employee;
	Reader* reader;
	Date borrowDate;
	Date returnDate;
	Date limitReturnDate;
	bool returned;
	unsigned long int id;

public:
	Borrow(Book* book, Employee* employee, Reader* reader, Date borrowDate,
			Date expectedDeliveryDate, unsigned long int borrowId);

	unsigned long int getID() const;
	Book* getBook() const;
	Employee* getEmployee() const;
	Reader* getReader() const;
	string print() const;
	float CalcFee() const;
	bool isReturned() const;
	bool DeliveredBook(Date d); // false if already returned
	void saveData(ofstream &pFile);
};

#endif
