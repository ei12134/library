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

class Reader: public Person {

private:

	vector<Borrow *> borrowedBooks;
	unsigned int card;
public:
	static unsigned long int readerID;

	Reader(string name, unsigned int age, unsigned int phone, string email);
	Reader(ifstream& s);
	virtual ~Reader();

	void saveData(ofstream &of);

	vector<Borrow*> getBorrowedBooks() const;
	unsigned int getCard() const;
	unsigned int getNif() const;
	unsigned int getWage() const;
	void setBorrowedBooks(vector<Borrow*> borrowedBooks);
	void addBorrow(Borrow* borrow);
	bool removeBorrow(Borrow* borrow);
	bool borrowLimit();
	string print() const;
	unsigned int getType() const;
	string printType() const;
};

#endif /* READER_H_ */
