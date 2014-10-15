#ifndef READER_H_
#define READER_H_

class Borrow;

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Person.h"
using namespace std;

class Reader: public Person {

private:
	vector<Borrow *> borrowedBooks;
	unsigned int card;

public:
	Reader(string name, unsigned int age, unsigned int phone, string email,
			unsigned int card);
	Reader(fstream& s);
	virtual ~Reader();
	vector<Borrow*> getBorrowBorrowedBooks() const;
	void setBorrowedBooks(vector<Borrow*> borrowedBooks);
	void addBorrow(Borrow* borrow);
	bool removeBorrow(Borrow* borrow);
	bool borrowLimit();
	string print();
	unsigned int getType();
};

#endif /* READER_H_ */
