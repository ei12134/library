#include "Borrow.h"

Borrow::Borrow(Book* book, Employee* employee, Reader* reader, Date borrowDate,
		Date expectedDeliveryDate) :
		book(book), employee(employee), reader(reader), borrowDate(borrowDate), expectedDeliveryDate(
				expectedDeliveryDate), Returned { false } {
}

Book* Borrow::getBook() const {
	return book;
}

Employee* Borrow::getEmployee() const {
	return employee;
}

Reader* Borrow::getReader() const {
	return reader;
}

float Borrow::CalcFee() const {
	if (!Returned)
		return 0;
	int days { actuallyDeliveryDate - expectedDeliveryDate };
	if (days <= 0)
		return 0;
	if (days <= 7)
		return (days * 0.25);
	return (7 * 0.25 + (days - 7) * 0.5);
}

bool Borrow::DeliveredBook(Date d) {
	if (Returned)
		return false;
	Returned = true;
	this->actuallyDeliveryDate = d;
	return true;
}
