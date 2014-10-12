#ifndef SRC_READER_H_
#define SRC_READER_H_

class Current;

#include "Person.h"
#include "../Borrow/Current.h"
#include <string>
#include <vector>

using namespace std;

class Reader: public Person {

private:
	vector<Current *> currentlyBorrowedBooks;
	unsigned int card;

public:
	Reader(string name, unsigned int age, unsigned int phone,
			string email, unsigned int card);
	virtual ~Reader();
	vector<Current*> getCurrentBorrowedBooks() const;
	void setBooks(vector<Current*> currentlyBorrowedBooks);
	void addCurrentBorrow(Current* currentBorrow);
	bool removeCurrentBorrow(Current* currentBorrow);
	bool borrowLimit();
	string print();
};

#endif /* SRC_READER_H_ */
