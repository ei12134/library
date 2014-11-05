#include "Borrow.h"

unsigned long int Borrow::borrowID = 0;

Borrow::Borrow(Book* book, Person* employee, Person* reader, Date borrowDate,
		Date limitReturnDate) :
		book(book), employee(employee), reader(reader), borrowDate(borrowDate), limitReturnDate(
				limitReturnDate), returned(false) {
	ID = ++borrowID;
}

/*
 * borrowDate the empty constructor is automatically called when this instance is created
 * the empty constructor in the borrowDate and the LimitReturnDate gives the current system date
 **/
Borrow::Borrow(Book* book, Person* employee, Person* reader) :
		book(book), employee(employee), reader(reader) {
	limitReturnDate.addDays(7); // adds 7 days to the current system date
	ID = ++borrowID;
	returned = false;
}

Book* Borrow::getBook() const {
	return book;
}

Person* Borrow::getEmployee() const {
	return employee;
}

Person* Borrow::getReader() const {
	return reader;
}

unsigned long int Borrow::getID() const {
	return ID;
}

float Borrow::calcFee() const {
	Date d;
	if (returned)
		d = returnDate;
	int days = d - limitReturnDate;
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

bool Borrow::deliveredBook(Date d) {
	//used to read from the files to
	if (returned)
		return false;
	returned = true;
	this->returnDate = d;
	return true;
}

Date Borrow::getBorrowDate() {
	return borrowDate;
}

Date Borrow::getReturnDate() {
	if (!returned)
		throw Exception<bool>("Book not returned yet!", returned); // throw exception <bool> because of the template
	return returnDate;
}

Date Borrow::getLimitReturnDate() {
	return limitReturnDate;
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
	ss << "\t\t\t" << "    Limit return date: " << limitReturnDate.print()
			<< endl;
	ss << "\t\t\t" << "    Fee: " << calcFee() << " euros" << endl;
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
