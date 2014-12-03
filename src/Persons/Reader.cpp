#include "Reader.h"

unsigned long int Reader::readerID = 0;

Reader::Reader(string name, unsigned int age, unsigned int phoneNumber,
		string email) :
		Person(name, age, phoneNumber, email), card(++readerID) {
	borrowedBooks.reserve(MAX_BORROWS); // limit to 3 borrowed books
}

Reader::Reader(stringstream& s) :
		Person(s) {
	borrowedBooks.reserve(MAX_BORROWS);
	stringstream ss;
	string sCard;
	unsigned int card;

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
	of << card;
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

bool Reader::setBorrowedBooks(vector<Borrow*> borrowedBooks) {
	if (MAX_BORROWS > borrowedBooks.size())
		return false;
	this->borrowedBooks = borrowedBooks;
	return true;
}

bool Reader::addBorrow(Borrow* borrow) {
	if (borrowedBooks.size() >= MAX_BORROWS)
		return false;
	else
		borrowedBooks.push_back(borrow);
	return true;
}

bool Reader::addRequest(Request request) {
	if (sequentialSearch(requestedBooks, request) != -1)
		return false;
	else
		requestedBooks.push_back(request);
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
