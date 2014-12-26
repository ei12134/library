#ifndef READER_H_
#define READER_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../Algorithms.h"
#include "../Request.h"
#include "../Borrow.h"
#include "Person.h"

using namespace std;

static const unsigned int MAX_BORROWS = 3;

/**
 * Reader Class
 * stores each reader borrow and personal information
 */
class Reader: public Person {

private:
	/// vector containing Borrow pointer type objects
	vector<Borrow *> borrowedBooks;
	/// vector containing Request type objects
	vector<Request> requestedBooks;
	/// reader unique card id
	unsigned int card;

	// when new user is created this variable is set to true (there is no register year)
	// (because we have no borroed books to compare if he is really inactive by date)
	bool inactive;

	Date lastActiviteDate;
public:
	static unsigned long int readerID;
	/** Reader manual constructor*/
	Reader(string name, unsigned int age, unsigned int phone, string email);
	/** Reader automatic constructor with member data read from readers.csv file*/
	Reader(stringstream& s);
	virtual ~Reader();

	///@return borrows pointer vector
	vector<Borrow*> getBorrowedBooks() const;

	///@return borrows pointer vector
	vector<Request> getRequestedBooks() const;

	///@return card id
	unsigned int getCard() const;
	unsigned int getNif() const;
	unsigned int getWage() const;
	bool getInactive() const;
	void setInactive(bool inactive);
	string printType() const;
	bool setBorrowedBooks(vector<Borrow*> borrowedBooks);
	bool addBorrow(Borrow* borrow);
	bool addRequest(Request request);
	bool removeBorrow(Borrow* borrow);
	bool removeRequest(Request request);
	bool borrowLimit();

	bool checkInactiveByDate(const Date &d);

	/** saves reader data to output file stream buffer
	 */
	void saveData(ofstream &of);

	///@return formatted reader information
	string print() const;

	///@return person object type
	unsigned int getType() const;
};

#endif /* READER_H_ */
