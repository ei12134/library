/*
 * Reader.cpp
 *
 *  Created on: 08/10/2014
 *      Author: User
 */

#include "Reader.h"

Reader::Reader() {
	borrowedBooks.reserve(3); // limit to 3 borrows
}

Reader::~Reader() {
	// TODO Auto-generated destructor stub
}

vector<Borrow*> Reader::getBorrowedBooks() const {
	return borrowedBooks;
}

void Reader::setBooks(vector<Borrow*> borrowedBooks) {
	this->borrowedBooks = borrowedBooks;
}

void Reader::addBorrow(Borrow* borrowedBook) {
	borrowedBooks.push_back(borrowedBook);
}

bool Reader::removeBorrow(Borrow* borrowedBook) {
	vector<Borrow*>::iterator it;
	for (it = borrowedBooks.begin(); it != borrowedBooks.end(); it++) {
		if (*it == borrowedBook) {
			borrowedBooks.erase(it);
			return true;
		}
	}
	return false;
}

bool Reader::borrowLimit() {
	return borrowedBooks.size() > 2;
}

string Reader::printInfo() {
	return NULL;
	//return Person::printInfo;
}
