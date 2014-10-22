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
	Book(string author, bool borrowed, string quota, unsigned int pageNumber,
			string isbn, string title);
	virtual ~Book();
	string getAuthor();
	void setAuthor(string author);
	bool getBorrowed();
	void setBorrowed(bool borrowed);
	string getQuota();
	void setQuota(string quota);
	int getPageNumber();
	void setPageNumber(int pageNumber);
	string getIsbn();
	void setIsbn(string isbn);
	string getTitle();
	void setTitle(string title);

};

#endif /* BOOK_H_ */
