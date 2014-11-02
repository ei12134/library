#ifndef READER_H_
#define READER_H_

class Borrow;

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Person.h"
using namespace std;

static const unsigned int MAX_BORROWS = 3;

class Reader: public Person {

private:
	vector<Borrow *> borrowedBooks;
	unsigned int card;

public:
	Reader(string name, unsigned int age, unsigned int phone, string email,
			unsigned int card);
	Reader(fstream& s);
	virtual ~Reader();
	vector<Borrow*> getBorrowedBooks() const;
	unsigned int getCard() const;
	unsigned int getNif() const;
	unsigned int getWage() const;
	void setBorrowedBooks(vector<Borrow*> borrowedBooks);
	void addBorrow(Borrow* borrow);
	bool removeBorrow(Borrow* borrow);
	bool borrowLimit();
	string print();
	unsigned int getType();
	string printType();
};

#endif /* READER_H_ */
