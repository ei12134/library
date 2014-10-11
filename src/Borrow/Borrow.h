#ifndef BORROW_H_
#define BORROW_H_

class Employee;
class Reader;

#include "../Book.h"
#include "../Date.h"
using namespace std;

class Borrow {
protected:
	Date borrowDate;
	Date actuallyDeliveryDate;

	Book* book;
	Employee* employee;
	Reader* reader;

public:
	Borrow(Book* book, Employee* employee, Reader* reader, Date borrowDate);
	virtual float CalcFee() = 0;
	virtual ~Borrow();
};

#endif
