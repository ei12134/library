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
	Person* reader;
	Book* book;
	Date request;
public:
	Request(Person* reader, Book* book, Date date);
	Person* getReader() const;
	Book* getBook() const;
	Date getDate() const {
		return request;
	}
	bool operator==(const Request& r2) const;
//	friend ostream& operator<<(ostream& os, const Request& r);
};

#endif /* REQUEST_H_ */
