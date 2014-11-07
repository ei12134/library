#ifndef READER_H_
#define READER_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
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
	/// vector to Borrow pointer type objects
	vector<Borrow *> borrowedBooks;
	/// reader unique card id
	unsigned int card;

public:
	static unsigned long int readerID;
	/** Reader manual constructor*/
	Reader(string name, unsigned int age, unsigned int phone, string email);
	/** Reader automatic constructor with member data read from readers.csv file*/
	Reader(stringstream& s);
	virtual ~Reader();

	///@return borrows pointer vector
	vector<Borrow*> getBorrowedBooks() const;

	///@return card id
	unsigned int getCard() const;

	unsigned int getNif() const;

	unsigned int getWage() const;

	string printType() const;

	bool setBorrowedBooks(vector<Borrow*> borrowedBooks);

	bool addBorrow(Borrow* borrow);

	bool removeBorrow(Borrow* borrow);

	bool borrowLimit();

	/** saves reader data to output file stream buffer
	 */
	void saveData(ofstream &of);

	///@return formatted reader information
	string print() const;

	///@return person object type
	unsigned int getType() const;
};

#endif /* READER_H_ */
