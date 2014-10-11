#include "Previous.h"

Previous::Previous(Book* book, Employee* employee, Reader* reader,
		Date borrowDate, Date expectedDeliveryDate, float fee) :
		Borrow(book, employee, reader, borrowDate) {
	this->fee = fee;
}

Previous::~Previous() {
	// TODO Auto-generated destructor stub
}

float Previous::CalcFee() {
	return 0.0f;
}

