/*
 * Reader.cpp
 *
 *  Created on: 08/10/2014
 *      Author: User
 */

#include "Reader.h"

Reader::Reader(string name, unsigned int age, unsigned int phoneNumber,
		string email, unsigned int card) :
		Person(name, age, phoneNumber, email) {
	this->card = card;
	currentlyBorrowedBooks.reserve(3); // limit to 3 borrowed books
}

Reader::Reader(fstream& s) : Person(s) {
	stringstream ss;
	string name, email, sAge, sPhone, sCard;
	unsigned int age, phone, card;

	getline(s, name, ';');
	getline(s, sAge, ';');
	ss << sAge;
	ss >> age;
	ss.clear();
	this->age = age;

	getline(s, sPhone, ';');
	ss << sPhone;
	ss >> phone;
	ss.clear();
	this->phone = phone;

	getline(s, email, ';');
	this->email = email;

	getline(s, sCard); // read last input until newline
	ss << sCard;
	ss >> card;
	ss.clear();
	this->card = card;

//	readerID++;
}

//vector<Current*> Reader::getCurrentBorrowedBooks() const {
//	return currentlyBorrowedBooks;
//}

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
	ss << Person::print() << " ; " << card;
	return ss.str();
}
