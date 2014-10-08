/*
 * Library.cpp
 *
 *  Created on: 08/10/2014
 *      Author: User
 */

#include <vector>
#include "Library.h"
using namespace std;

unsigned long int Library::personID = 0;

Library::Library() {
	// TODO Auto-generated constructor stub

}

Library::~Library() {
	// TODO Auto-generated destructor stub
}

vector<Book*> Library::getBooks() const {
	return books;
}

vector<Borrow*> Library::getBorrows() const {
	return borrows;
}

vector<Person*> Library::getPersons() const {
	return persons;
}

void Library::setBooks(vector<Book*> books) {
	this->books = books;
}

void Library::setBorrows(vector<Borrow*> borrows) {
	this->borrows = borrows;
}

void Library::setPersons(vector<Person*> persons) {
	this->persons = persons;
}

void Library::addBook(Book* book) {
	books.push_back(book);
}

void Library::addBorrow(Borrow* borrow) {
	borrows.push_back(borrow);
}

void Library::addPerson(Person* person) {
	persons.push_back(person);
}

bool Library::removeBook(Book* book) {
	vector<Book*>::iterator it;
	for (it = books.begin(); it != books.end(); it++) {
		if (*it == book) {
			books.erase(it);
			return true;
		}
	}
	return false;
}

bool Library::removeBorrow(Borrow* borrow) {
	vector<Borrow*>::iterator it;
	for (it = borrows.begin(); it != borrows.end(); it++) {
		if (*it == borrow) {
			borrows.erase(it);
			return true;
		}
	}
	return false;
}

bool Library::removePerson(Person* person) {
	vector<Person*>::iterator it;
	for (it = persons.begin(); it != persons.end(); it++) {
		if (*it == person) {
			persons.erase(it);
			return true;
		}
	}
	return false;
}
