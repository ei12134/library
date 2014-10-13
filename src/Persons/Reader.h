#ifndef SRC_READER_H_
#define SRC_READER_H_

class Borrow;

#include "Person.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

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
};

#endif /* SRC_READER_H_ */
