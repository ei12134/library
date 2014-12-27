#include "Request.h"

Request::Request(Book* book, Person* reader, Date date) :
		reader(reader), book(book), request(date) {
}

Person* Request::getReader() const {
	return reader;
}

Book* Request::getBook() const {
	return book;
}

Date Request::getDate() const {
	return request;
}

void Request::saveData(ofstream &of) {
	of << book->getID() << ";" << reader->getCard() << ";" << request.getDay()
			<< "," << request.getMonth() << "," << request.getYear();
}

bool Request::operator==(const Request& r2) const {
	return ((this->reader == r2.reader) && (this->book == r2.book));
}
bool Request::operator<(const Request& r2) const {
	if (request < r2.request)
		return false;
	else if (request > r2.request)
		return true;
	else if (reader->getAge() <= 12 && r2.reader->getAge() > 12)
		return false;
	else if (reader->getAge() > 12 && r2.reader->getAge() <= 12)
		return true;
	else if (reader->getAge() <= 23 && r2.reader->getAge() > 23)
		return false;
	else if (reader->getAge() > 23 && r2.reader->getAge() <= 23)
		return true;
	return true;
}

