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
	unsigned long int ID;

	vector<string> authors;
	bool borrowed;
	string quota;
	int pageNumber;
	string isbn;
	string title;
public:
	static unsigned long int bookID;

	Book(vector<string> authors, bool borrowed, string quota,
			unsigned int pageNumber, string isbn, string title);
	virtual ~Book();
	Book(fstream& s);
	string print() const;
	vector<string> getAuthors() const;
	string getQuota() const;
	string getIsbn() const;
	string getTitle() const;
	int getPageNumber() const;
	bool getBorrowed() const;
	unsigned long int getID() const;
	void addAuthor(string author);
	void setAuthors(vector<string> authors);
	void setBorrowed(bool borrowed);
	void setQuota(string quota);
	void setPageNumber(int pageNumber);
	void setIsbn(string isbn);
	void setTitle(string title);
};

#endif /* BOOK_H_ */
