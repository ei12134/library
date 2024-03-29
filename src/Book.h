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
#include "Exception.h"
#define BOOK 5
using namespace std;

class Book {
private:
	unsigned long int ID;
	vector<string> authors;
	bool borrowed;
	string quota;
	unsigned int pageNumber;
	string ISBN;
	string title;
	unsigned int editionYear;
	bool deleted;
public:
	static unsigned long int bookID;
	Book(vector<string> authors, bool borrowed, string quota,
			unsigned int pageNumber, string ISBN, string title,
			unsigned int editionYear, bool deleted);
	virtual ~Book();
	Book(stringstream& s);
	Book();
	string print() const;
	string printAuthors() const;
	vector<string> getAuthors() const;
	string getQuota() const;
	string getISBN() const;
	string getTitle() const;
	unsigned int getPageNumber() const;
	bool getBorrowed() const;
	unsigned long int getID() const;
	unsigned int getEditionYear() const;
	bool getDeleted() const;
	void addAuthor(string author);
	void setAuthors(vector<string> authors);
	void setBorrowed(bool borrowed);
	void setQuota(string quota);
	void setPageNumber(int pageNumber);
	void setISBN(string ISBN);
	void setTitle(string title);
	void setEditionYear(unsigned int editionYear);
	void setDeleted(bool deleted);
	bool operator<(const Book& b2) const;
};

#endif /* BOOK_H_ */
