/*
 * Reader.h
 *
 *  Created on: 08/10/2014
 *      Author: User
 */

#ifndef SRC_READER_H_
#define SRC_READER_H_

#include <string>
#include <vector>
#include "Borrow.h"
using namespace std;

class Reader {

private:
	vector<Borrow *> borrowedBooks;
	// use cc id from person to identify?

public:
	Reader();
	virtual ~Reader();
	vector<Borrow*> getBorrowedBooks() const;
	void setBooks(vector<Borrow*> borrowedBooks);
	void addBorrow(Borrow* borrow);
	bool removeBorrow(Borrow* borrow);
	bool borrowLimit();
	string printInfo();
};

#endif /* SRC_READER_H_ */
