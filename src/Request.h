#ifndef REQUEST_H_
#define REQUEST_H_

#include "./Persons/Person.h"
#include "Book.h"
#include "Date.h"
using namespace std;

/**
 * Request Class
 * stores data concerning the request of a book unavailable at the library
 */
class Request {
	Book* book;
	Person* reader;
	Date request;
public:
	Request(Book* book, Person* reader, Date date);
	Request();
	Person* getReader() const;
	Book* getBook() const;
	Date getDate() const;
	string print() const;

	void setDate(Date d);
	bool changeReader(Person* reader);
	bool changeBook(Book* book);

	bool operator==(const Request& r2) const;
	bool operator<(const Request& r2) const;

	void saveData(ofstream &of);

//	friend ostream& operator<<(ostream& os, const Request& r);
};

#endif /* REQUEST_H_ */
