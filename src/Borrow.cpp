#include "Borrow.h"

Borrow::Borrow(Book* book, Employee* employee, Reader* reader, Date borrowDate,
		Date expectedDeliveryDate, unsigned long int borrowId) :
		book(book), employee(employee), reader(reader), borrowDate(borrowDate), expectedDeliveryDate(
				expectedDeliveryDate), Returned { false }, id(borrowId) {
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
unsigned long int Borrow::getID() const {
	return id;
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
	//used to read from the files to
	if (Returned)
		return false;
	Returned = true;
	this->actuallyDeliveryDate = d;
	return true;
}

string Borrow::print() const {
	stringstream ss;
	ss << "Book: " << book->print() << endl;
	ss << "Employee: " << employee->print() << endl;
	ss << "Reader: " << reader->print() << endl;
	ss << "Borrow date: " << borrowDate.print() << endl;
	ss << "Expected date: " << expectedDeliveryDate.print() << endl;
	if (Returned)
		ss << "Returned date: " << actuallyDeliveryDate.print() << endl;
	return ss.str();
}

void Borrow::saveData(ofstream &pFile) {
	pFile << book->getID() << ";" << employee->getNif() << ";"
			<< reader->getCard() << ";" << borrowDate.getDay() << ","
			<< borrowDate.getMonth() << "," << borrowDate.getYear() << ";"
			<< expectedDeliveryDate.getDay() << ","
			<< expectedDeliveryDate.getMonth() << ","
			<< expectedDeliveryDate.getYear() << ";" << Returned;
	if (Returned) {
		pFile << ";" << actuallyDeliveryDate.getDay() << ","
				<< actuallyDeliveryDate.getMonth() << ","
				<< actuallyDeliveryDate.getYear();
	}
}
