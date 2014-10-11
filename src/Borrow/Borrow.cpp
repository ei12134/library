#include "Borrow.h"

Borrow::Borrow(Book* book, Employee* employee, Reader* reader,
		Date borrowDate) {
	this->book = book;
	this->employee = employee;
	this->reader = reader;
	this->borrowDate = borrowDate;
}

Borrow::~Borrow() {
	// TODO Auto-generated destructor stub
}

