/*
 * Library.h
 *
 *  Created on: 08/10/2014
 *      Author: User
 */

#ifndef SRC_LIBRARY_H_
#define SRC_LIBRARY_H_

#include <vector>
#include "Book.h"
#include "Borrow.h"
#include "Person.h"
using namespace std;

class Library {

private:
	vector<Book*> books;
	vector<Borrow*> borrows;
	vector<Person*> persons; // http://english.stackexchange.com/questions/62084/whats-the-correct-plural-of-person

public:
	Library();
	virtual ~Library();
	vector<Book*> getBooks() const;
	vector<Borrow*> getBorrows() const;
	vector<Person*> getPersons() const;
	void setBooks(vector<Book*> books);
	void setBorrows(vector<Borrow*> borrows);
	void setPersons(vector<Person*> persons);
	void addBook(Book* book);
	void addBorrow(Borrow* borrow);
	void addPerson(Person* person);
	bool removeBook(Book* book);
	bool removeBorrow(Borrow* borrow);
	bool removePerson(Person* person);
};

#endif /* SRC_LIBRARY_H_ */
