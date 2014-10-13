#ifndef BORROW_H_
#define BORROW_H_

#include "Book.h"
#include "Date.h"
#include "./Persons/Reader.h"
#include "./Persons/Employee.h"
using namespace std;

class Borrow {
protected:
	Date borrowDate;
	Date actuallyDeliveryDate;
	Date expectedDeliveryDate;

	Book* book;
	Employee* employee;
	Reader* reader;

public:
	Borrow(Book* book, Employee* employee, Reader* reader, Date borrowDate,
			Date expectedDeliveryDate);
	float CalcFee();
};

#endif
