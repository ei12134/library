#include "Reader.h"

Reader::Reader(string name, unsigned int age, unsigned int phoneNumber,
		string email, unsigned int card) :
		Person(name, age, phoneNumber, email) {
	this->card = card;
	borrowedBooks.reserve(MAX_BORROWS); // limit to 3 borrowed books
}

Reader::Reader(fstream& s) :
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
//	readerID++;
}

void Reader::saveData(ofstream &of) {
	Person::saveData(of);
	of << card << ";";

	if (borrowedBooks.size() > 0)
		of << borrowedBooks[0]->getID();
	for (unsigned x = 1; x < borrowedBooks.size(); x++) {
		of << "," << borrowedBooks[x]->getID();
	}
	of << endl;
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
