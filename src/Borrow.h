#ifndef BORROW_H_
#define BORROW_H_

#include "Book.h"
#include "Date.h"
#include "./Persons/Reader.h"
#include "./Persons/Employee.h"
using namespace std;

class Borrow { // acho que era melhor ter uma subclass para livros nao emprestados xD
protected:
	bool Returned;
	Date borrowDate;
	Date actuallyDeliveryDate;
	Date expectedDeliveryDate;

	Book* book;
	Employee* employee;
	Reader* reader;

public:
	Borrow(Book* book, Employee* employee, Reader* reader, Date borrowDate,
			Date expectedDeliveryDate);

	Book* getBook() const;
	Employee* getEmployee() const;
	Reader* getReader() const;
	string print() const;

	float CalcFee() const;

	bool DeliveredBook(Date d); // false if already returned
};

#endif
