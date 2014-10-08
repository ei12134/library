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

/**
 * Library Class
 * stores containers used in the library management
 */

class Library {

private:
	/// pointer vector to book type objects
	vector<Book*> books;
	/// pointer vector to borrow type objects
	vector<Borrow*> borrows;
	/// pointer vector to person type objects
	vector<Person*> persons; // http://english.stackexchange.com/questions/62084/whats-the-correct-plural-of-person

public:
	/// All personnel unique identifier
	static unsigned long int personID;
	/** Library constructor reads *.csv files and stores
	 * pointers to each object in their dedicated container */
	Library();
	virtual ~Library();

	///@return books
	vector<Book*> getBooks() const;

	///@return borrows
	vector<Borrow*> getBorrows() const;

	///@return persons
	vector<Person*> getPersons() const;

	/** replaces existing books pointer vector
	 *@param books Book pointer vector
	 */
	void setBooks(vector<Book*> books);

	/** replaces existing borrows pointer vector
	 *@param borrows Borrow pointer vector
	 */
	void setBorrows(vector<Borrow*> borrows);

	/** replaces existing persons pointer vector
	 *@param persons Persons pointer vector
	 */
	void setPersons(vector<Person*> persons);

	/** adds new book to the library
	 *@param book Book pointer
	 */
	void addBook(Book* book);

	/** adds new borrow to the library
	 *@param borrow Borrow pointer
	 */
	void addBorrow(Borrow* borrow);

	/** adds new person to the library
	 *@param person Person pointer
	 */
	void addPerson(Person* person);

	/** removes a book from the library
	 *@param book Book pointer
	 */
	bool removeBook(Book* book);

	/** removes a borrow from the library
	 *@param borrow Borrow pointer
	 */
	bool removeBorrow(Borrow* borrow);

	/** removes a person from the library
	 *@param person Person pointer
	 */
	bool removePerson(Person* person);
};

#endif /* SRC_LIBRARY_H_ */
