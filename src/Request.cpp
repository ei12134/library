#include "Request.h"

Request::Request(Book* book, Person* reader, Date date) :
		book(book), reader(reader), request(date) {
}

Request::Request() :
		book(NULL), reader(NULL) {
	Date d;
	request = d;
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

bool Request::changeReader(Person* reader) {
	if (reader != NULL) {
		this->reader = reader;
		return true;
	}
	return false;
}

bool Request::changeBook(Book* book) {
	if (book != NULL) {
		this->book = book;
		return true;
	}
	return false;
}

void Request::saveData(ofstream &of) {
	of << book->getID() << ";" << reader->getCard() << ";" << request.getDay()
			<< "," << request.getMonth() << "," << request.getYear();
}

bool Request::operator==(const Request& r2) const {
	return ((this->reader == r2.reader) && (this->book == r2.book)
			&& (request == r2.request));
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
	return reader->getAge() > r2.reader->getAge();
}

string Request::print() const {
	string readerName = reader->getName();
	unsigned int readerAge = reader->getAge();
	string bookTitle = book->getTitle();
	string requestDate = request.print();
	stringstream ss;

	ss << readerName.substr(0, 22);
	if (readerName.size() >= 23)
		ss << "\t";
	else
		for (int i = 23 - readerName.size(); i > 0; i -= 8)
			ss << "\t";

	ss << readerAge << "\t";

	ss << (bookTitle.size() > 32 ? bookTitle.substr(0, 32) : bookTitle);
	ss << (bookTitle.size() >= 32 ? "\t" : "");
	for (int i = 32 - bookTitle.size(); i > 0; i -= 8)
		ss << "\t";

	ss << requestDate;

	return ss.str();
}

