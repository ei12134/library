#include "Book.h"
using namespace std;

unsigned long int Book::bookID = 0;

Book::Book(vector<string> authors, bool borrowed, string quota,
		unsigned int pageNumber, string ISBN, string title) :
		authors(authors), borrowed(borrowed), quota(quota), pageNumber(
				pageNumber), ISBN(ISBN), title(title) {
	ID = ++bookID;
}

Book::~Book() {
}

Book::Book(fstream& s) {
	stringstream ss;
	string newAuthors, newBorrowed, newQuota, newPageNumber, newISBN, newTitle,
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

	getline(s, newISBN, ';');
	this->ISBN = newISBN;

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
	stringstream ss, authorsSs;

	ss << (title.size() > 22 ? title.substr(0, 22) : title);
	ss << (title.size() >= 22 ? "\t" : "");
	for (int i = 22 - title.size(); i > 0; i -= 8)
		ss << "\t";

	if (authors.size() > 0) {
		authorsSs << authors.at(0);
		for (unsigned x = 1; x < authors.size(); x++)
			authorsSs << ", " << authors.at(x);
	}

	ss
			<< (authorsSs.str().size() > 22 ?
					authorsSs.str().substr(0, 22) : authorsSs.str());
	ss << (authorsSs.str().size() >= 22 ? "\t" : "");
	for (int i = 24 - authorsSs.str().size(); i > 0; i -= 8)
		ss << "\t";

	ss << ISBN << "\t" << (borrowed == 1 ? "Borrowed" : "Available");
	return ss.str();
}

string Book::printShort() const {
	stringstream ss, authorsSs;

	ss << (title.size() > 42 ? title.substr(0, 42) : title) << " ";
	ss << (borrowed == 1 ? "[Borrowed]" : "[Available]") << "\n";

	if (authors.size() > 0) {
		authorsSs << authors.at(0);
		for (unsigned x = 1; x < authors.size(); x++)
			authorsSs << ", " << authors.at(x);
	}
	ss << "\t\t"
			<< (authorsSs.str().size() > 42 ?
					authorsSs.str().substr(0, 42) : authorsSs.str());

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
string Book::getISBN() const {
	return ISBN;
}
void Book::setISBN(string ISBN) {
	this->ISBN = ISBN;
}
string Book::getTitle() const {
	return title;
}
void Book::setTitle(string title) {
	this->title = title;
}

