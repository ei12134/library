#include "Borrow.h"

Borrow::Borrow(Book* book, Employee* employee, Reader* reader, Date borrowDate,
		Date expectedDeliveryDate) {
	this->book = book;
	this->employee = employee;
	this->reader = reader;
	this->borrowDate = borrowDate;
}

float Borrow::CalcFee() {
	return 0;
}
