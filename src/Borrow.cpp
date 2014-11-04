#include "Borrow.h"

Borrow::Borrow(Book* book, Employee* employee, Reader* reader, Date borrowDate,
		Date limitReturnDate, unsigned long int borrowId) :
		book(book), employee(employee), reader(reader), borrowDate(borrowDate), limitReturnDate(
				limitReturnDate), returned(false), id(borrowId) {
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
	if (!returned)
		return 0;
	int days = returnDate - limitReturnDate;
	if (days <= 0)
		return 0;
	if (days <= 7)
		return (days * 0.25);
	return (7 * 0.25 + (days - 7) * 0.5);
}

void Borrow::setReturned(bool returned) {
	Date d;
	if (returned)
		returnDate = d;
	this->returned = returned;
}

bool Borrow::DeliveredBook(Date d) {
	//used to read from the files to
	if (returned)
		return false;
	returned = true;
	this->returnDate = d;
	return true;
}

string Borrow::print() const {
	stringstream ss;
	ss << "Book: " << book->getTitle() << endl << endl;
	ss << "\t\t\t" << "Employee: " << employee->getName() << endl;
	ss << "\t\t\t" << "Reader: " << reader->getName() << endl;
	ss << "\t\t\t" << "Borrow date: " << borrowDate.print() << endl;
	ss << "\t\t\t" << "Limit return date: " << limitReturnDate.print() << endl;
	if (returned)
		ss << "Return date: " << returnDate.print() << endl;
	return ss.str();
}

string Borrow::printShort() const {
	stringstream ss;
	ss << "Book: " << book->getTitle() << endl;
	ss << "\t\t\t" << "    Borrow date: " << borrowDate.print() << endl;
	ss << "\t\t\t" << "    Limit return date: " << limitReturnDate.print() << endl;
	if (returned)
		ss << "Return date: " << returnDate.print() << endl;
	return ss.str();
}

void Borrow::saveData(ofstream &pFile) {
	pFile << book->getID() << ";" << employee->getNif() << ";"
			<< reader->getCard() << ";" << borrowDate.getDay() << ","
			<< borrowDate.getMonth() << "," << borrowDate.getYear() << ";"
			<< limitReturnDate.getDay() << "," << limitReturnDate.getMonth()
			<< "," << limitReturnDate.getYear() << ";" << returned;
	if (returned) {
		pFile << ";" << returnDate.getDay() << "," << returnDate.getMonth()
				<< "," << returnDate.getYear();
	}
}

bool Borrow::isReturned() const {
	return returned;
}
