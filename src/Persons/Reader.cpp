#include "Reader.h"

unsigned long int Reader::readerID { 0 };

Reader::Reader(string name, unsigned int age, unsigned int phoneNumber,
		string email) :
		Person(name, age, phoneNumber, email), card(++readerID) {
	borrowedBooks.reserve(MAX_BORROWS); // limit to 3 borrowed books
}

Reader::Reader(ifstream& s) :
		Person(s) {
	borrowedBooks.reserve(MAX_BORROWS);
	stringstream ss;
	string sCard;
	unsigned int card;

	getline(s, sCard); // read last input until newline
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
	//nao poem endl
}

Reader::~Reader() {

}

vector<Borrow*> Reader::getBorrowedBooks() const {
	return borrowedBooks;
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

void Reader::setBorrowedBooks(vector<Borrow*> borrowedBooks) {
	this->borrowedBooks = borrowedBooks;
}

void Reader::addBorrow(Borrow* borrow) {
	borrowedBooks.push_back(borrow);
}

bool Reader::removeBorrow(Borrow* borrow) {
	vector<Borrow*>::iterator it;
	for (it = borrowedBooks.begin(); it != borrowedBooks.end(); it++) {
		if (*it == borrow) {
			borrowedBooks.erase(it);
			return true;
		}
	}
	return false;
}

bool Reader::borrowLimit() {
	return borrowedBooks.size() >= MAX_BORROWS;
}

string Reader::print() {
	stringstream ss;
	ss << Person::print() << "   " << card;
	return ss.str();
}

unsigned int Reader::getType() {
	return 1;
}

string Reader::printType() {
	return "[Reader]";
}
