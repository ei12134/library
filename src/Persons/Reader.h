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
	unsigned long int cardID;

public:
	Reader(string name, unsigned int age, unsigned long int phoneNumber,
			string email, unsigned long int cardID);
	virtual ~Reader();
	vector<Current*> getCurrentBorrowedBooks() const;
	void setBooks(vector<Current*> currentlyBorrowedBooks);
	void addCurrentBorrow(Current* currentBorrow);
	bool removeCurrentBorrow(Current* currentBorrow);
	bool borrowLimit();
	string print();
};

#endif /* SRC_READER_H_ */
