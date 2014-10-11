#ifndef BORROW_H_
#define BORROW_H_

class Employee;
class Reader;
class Data;

#include "../Persons/Employee.h"
#include "../Persons/Reader.h"
#include "../Book.h"
#include "../Data.h"
using namespace std;

class Borrow {
protected:
	Data borrowDate;
	Data actuallyDeliveryDate;

	Book* book;
	Employee* employee;
	Reader* reader;

public:
	Borrow(Book* book, Employee* employee, Reader* reader, Data borrowDate);
	virtual float CalcFee() = 0;
	virtual ~Borrow();
};

#endif
