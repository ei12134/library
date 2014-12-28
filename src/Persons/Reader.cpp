#include "Reader.h"

unsigned long int Reader::readerID = 0;

Reader::Reader(string name, unsigned int age, unsigned int phoneNumber,
		string email) :
		Person(name, age, phoneNumber, email), card(++readerID) {
	borrowedBooks.reserve(MAX_BORROWS); // limit to 3 borrowed books
	inactive = false;
}

Reader::Reader(stringstream& s) :
		Person(s) {
	borrowedBooks.reserve(MAX_BORROWS);
	stringstream ss;
	string sInactive, sCard, data;
	int dia, mes, ano;
	unsigned int card;
	bool inactive;

	if (!getline(s, sInactive, ';'))
		throw Exception<string>("Error reading inactive", "Reader");
	ss << sInactive;
	ss >> inactive;
	ss.clear();
	this->inactive = inactive;

	// ***********************************************************
	// read lastActiveDate ***************************************
	// ***********************************************************

	if (!getline(s, data, ','))
		throw Exception<string>("Error reading day", "Borrow");
	ss << data;
	ss >> dia;
	ss.clear();
	data.clear();
	if (!getline(s, data, ','))
		throw Exception<string>("Error reading month", "Borrow");
	ss << data;
	ss >> mes;
	ss.clear();
	data.clear();
	if (!getline(s, data, ';'))
		throw Exception<string>("Error reading year", "Borrow");
	ss << data;
	ss >> ano;
	ss.clear();
	data.clear();
	this->lastActivity = Date(dia, mes, ano);

	// ***********************************************************
	// ***********************************************************
	// ***********************************************************

	if (!getline(s, sCard)) // read last input until newline
		throw Exception<string>("Error reading card", "Reader");
	ss << sCard;
	ss >> card;
	ss.clear();
	this->card = card;

	if (card > readerID) // give the biggest card read from files to the unique id
		readerID = card;
}

void Reader::saveData(ofstream &of) {
	Person::saveData(of);
	of << inactive << ";" << lastActivity.getDay() << ","
			<< lastActivity.getMonth() << "," << lastActivity.getYear() << ";"
			<< card;
}

Reader::~Reader() {

}

vector<Borrow*> Reader::getBorrowedBooks() const {
	return borrowedBooks;
}

vector<Request> Reader::getRequestedBooks() const {
	return requestedBooks;
}

unsigned int Reader::getCard() const {
	return card;
}

unsigned int Reader::getNif() const {
	return 0;
}

unsigned int Reader::getWage() const {
	return 0;
}

Date Reader::getLastActivity() const{
	return lastActivity;
}

bool Reader::setBorrowedBooks(vector<Borrow*> borrowedBooks) {
	if (MAX_BORROWS > borrowedBooks.size())
		return false;
	this->borrowedBooks = borrowedBooks;
	return true;
}

bool Reader::addBorrow(Borrow* borrow) {
//	if (borrow->getBook()->getBorrowed())// livro ja esta emprestado
//		return false;
	if (borrowedBooks.size() >= MAX_BORROWS)
		return false;
	else
		borrowedBooks.push_back(borrow);

	lastActivity = borrow->getBorrowDate();
	inactive = false;

	return true;
}

bool Reader::addRequest(Request request) {
	if (sequentialSearch(requestedBooks, request) != -1)
		return false;
	else
		requestedBooks.push_back(request);

	lastActivity = request.getDate();
	inactive = false;

	return true;
}

bool Reader::removeBorrow(Borrow* borrow) {
	for (size_t i = 0; i < borrowedBooks.size(); i++) {
		if (borrowedBooks[i] == borrow) {
			borrowedBooks.erase(borrowedBooks.begin() + i);
			return true;
		}
	}
	return false;
}

bool Reader::removeRequest(Request request) {
	int index = sequentialSearch(requestedBooks, request);
	if (index == -1)
		return false;
	else
		requestedBooks.erase(requestedBooks.begin() + index);
	return true;
}

bool Reader::borrowLimit() {
	return borrowedBooks.size() >= MAX_BORROWS;
}

string Reader::print() const {
	stringstream ss;
	ss << Person::print();

	if (email.size() >= 22)
		ss << "\t";
	else
		for (int i = 24 - email.size(); i > 0; i -= 8)
			ss << "\t";

	ss << card;
	return ss.str();
}

unsigned int Reader::getType() const {
	return READER;
}

string Reader::printType() const {
	return "[Reader]";
}

bool Reader::getInactive() const {
	return inactive;
}

void Reader::setInactive(bool inactive) {
	this->inactive = inactive;
	if (!this->inactive)
		lastActivity = Date();
}

void Reader::setLastActivity(Date d){
	this->lastActivity = d;
}

bool Reader::checkInactiveByDate(const Date &d) {
	inactive = (d - lastActivity) >= 365;
	return inactive;
}

