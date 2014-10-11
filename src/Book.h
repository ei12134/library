#ifndef BOOK_H_
#define BOOK_H_

#include <string>
using namespace std;

class Book {
private:
	string author;
	bool borrowed;
	string quota;
	int pageNumber;
	string isbn;
	string title;
public:
	Book(string author, bool borrowed, string quota, int pageNumber,
			string isbn, string title);
	virtual ~Book();
};

#endif /* BOOK_H_ */
