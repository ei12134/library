#include "Book.h"
using namespace std;

unsigned long int Book::bookID = 0;

Book::Book(vector<string> authors, bool borrowed, string quota,
		unsigned int pageNumber, string isbn, string title) :
		authors(authors), borrowed(borrowed), quota(quota), pageNumber(
				pageNumber), isbn(isbn), title(title) {
	ID = ++bookID;
}

Book::~Book() {
}

Book::Book(fstream& s) {
	stringstream ss;
	string newAuthors, newBorrowed, newQuota, newPageNumber, newIsbn, newTitle,
			newAuthor, newIdStr;
	bool borrowed;
	unsigned int pageNumber, newId;

	getline(s, newAuthors, ';');
	ss << newAuthors;
	while (getline(ss, newAuthor, ',')) {
		this->authors.push_back(newAuthor);
	}
	ss.clear();

	getline(s, newBorrowed, ';');
	ss << newBorrowed;
	ss >> borrowed;
	ss.clear();
	this->borrowed = borrowed;

	getline(s, newQuota, ';');
	this->quota = newQuota;

	getline(s, newPageNumber, ';');
	ss << newPageNumber;
	ss >> pageNumber;
	ss.clear();
	this->pageNumber = pageNumber;

	getline(s, newIsbn, ';');
	this->isbn = newIsbn;

	getline(s, newTitle, ';');
	this->title = newTitle;

	getline(s, newIdStr);
	ss << newIdStr;
	ss >> newId;
	this->ID = newId;
	ss.clear();

	if (this->ID > bookID)
		bookID = this->ID;
}

string Book::print() const {
	stringstream ss;
	if (authors.size() > 0) {
		ss << authors.at(0);
		for (unsigned x = 1; x < authors.size(); x++)
			ss << ", " << authors.at(x);
	}
	ss << "   " << (borrowed == 1 ? "Borrowed" : "Available") << "   " << quota
			<< "   " << pageNumber << "   " << isbn << "   " << title;

	return ss.str();
}

unsigned long int Book::getID() const {
	return ID;
}

vector<string> Book::getAuthors() const {
	return authors;
}

void Book::setAuthors(vector<string> authors) {
	this->authors = authors;
}

void Book::addAuthor(string author) {
	this->authors.push_back(author);
}

bool Book::getBorrowed() const {
	return borrowed;
}

void Book::setBorrowed(bool borrowed) {
	this->borrowed = borrowed;
}

string Book::getQuota() const {
	return quota;
}

void Book::setQuota(string quota) {
	this->quota = quota;
}

int Book::getPageNumber() const {
	return pageNumber;
}
void Book::setPageNumber(int pageNumber) {
	this->pageNumber = pageNumber;
}
string Book::getIsbn() const {
	return isbn;
}
void Book::setIsbn(string isbn) {
	this->isbn = isbn;
}
string Book::getTitle() const {
	return title;
}
void Book::setTitle(string title) {
	this->title = title;
}

