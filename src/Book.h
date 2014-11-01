#ifndef BOOK_H_
#define BOOK_H_

#include <string>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
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
	Book(string author, bool borrowed, string quota, unsigned int pageNumber,
			string isbn, string title);
	virtual ~Book();
	Book(fstream& s);
	string print();
	string getAuthor();
	string getQuota();
	string getIsbn();
	string getTitle();
	int getPageNumber();
	bool getBorrowed();
	void setAuthor(string author);
	void setBorrowed(bool borrowed);
	void setQuota(string quota);
	void setPageNumber(int pageNumber);
	void setIsbn(string isbn);
	void setTitle(string title);
};

#endif /* BOOK_H_ */
