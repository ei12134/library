/*
 * Reader.cpp
 *
 *  Created on: 08/10/2014
 *      Author: User
 */

#include "Reader.h"

Reader::Reader(string name, unsigned int age, unsigned long int phoneNumber,
		string email, unsigned long int cardID) :
		Person(name, age, phoneNumber, email) {
	this->cardID = cardID;
	currentlyBorrowedBooks.reserve(3); // limit to 3 borrowed books
}

Reader::~Reader() {
	// TODO Auto-generated destructor stub
}

vector<Current*> Reader::getCurrentBorrowedBooks() const {
	return currentlyBorrowedBooks;
}

void Reader::setBooks(vector<Current*> currentlyBorrowedBooks) {
	this->currentlyBorrowedBooks = currentlyBorrowedBooks;
}

void Reader::addCurrentBorrow(Current* currentBorrow) {
	currentlyBorrowedBooks.push_back(currentBorrow);
}

bool Reader::removeCurrentBorrow(Current* currentBorrow) {
	vector<Current*>::iterator it;
	for (it = currentlyBorrowedBooks.begin();
			it != currentlyBorrowedBooks.end(); it++) {
		if (*it == currentBorrow) {
			currentlyBorrowedBooks.erase(it);
			return true;
		}
	}
	return false;
}

bool Reader::borrowLimit() {
	return currentlyBorrowedBooks.size() > 2;
}

string Reader::print() {
	stringstream ss;
	ss << Person::print() << " ; " << cardID;
	return ss.str();
}
