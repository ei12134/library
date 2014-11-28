#include "Request.h"

Request::Request(Person* reader, Book* book, Date date) :
		reader(reader), book(book), request(date) {
}

Person* Request::getReader() const {
	return reader;
}

Book* Request::getBook() const {
	return book;
}

bool Request::operator==(const Request& r2) const {
	return ((this->reader == r2.reader) && (this->book == r2.book));
}