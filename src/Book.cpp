#include "Book.h"
using namespace std;

unsigned long int Book::bookID = 0;

Book::Book(vector<string> authors, bool borrowed, string quota,
		unsigned int pageNumber, string ISBN, string title,
		unsigned int editionYear) :
		authors(authors), borrowed(borrowed), quota(quota), pageNumber(
				pageNumber), ISBN(ISBN), title(title), editionYear(editionYear) {
	ID = ++bookID;
}

Book::~Book() {
}

Book::Book(stringstream& s) {
	stringstream ss;
	string book;
	string newAuthors, newBorrowed, newQuota, newPageNumber, newISBN, newTitle,
			newAuthor, newEditionYearStr, newIdStr;
	bool borrowed;
	unsigned int pageNumber, newId, editionYear;

	if (!getline(s, newAuthors, ';'))
		throw Exception<string>("Error reading authors", "Book");

	ss << newAuthors;
	while (getline(ss, newAuthor, ',')) {
		this->authors.push_back(newAuthor);
	}
	ss.clear();

	if (!getline(s, newBorrowed, ';'))
		throw Exception<string>("Error reading borrowed", "Book");

	ss << newBorrowed;
	ss >> borrowed;
	ss.clear();
	this->borrowed = borrowed;

	if (!getline(s, newQuota, ';'))
		throw Exception<string>("Error reading quota", "Book");
	this->quota = newQuota;

	if (!getline(s, newPageNumber, ';'))
		throw Exception<string>("Error reading page number", "Book");
	ss << newPageNumber;
	ss >> pageNumber;
	ss.clear();
	this->pageNumber = pageNumber;

	if (!getline(s, newISBN, ';'))
		throw Exception<string>("Error reading ISBN", "Book");
	this->ISBN = newISBN;

	if (!getline(s, newTitle, ';'))
		throw Exception<string>("Error reading title", "Book");
	this->title = newTitle;

	if (!getline(s, newEditionYearStr, ';'))
		throw Exception<string>("Error reading editionYear", "Book");
	ss << newEditionYearStr;
	ss >> editionYear;
	this->editionYear = editionYear;
	ss.clear();

	if (!getline(s, newIdStr))
		throw Exception<string>("Error reading title", "Book");
	ss << newIdStr;
	ss >> newId;
	this->ID = newId;
	ss.clear();

	if (this->ID > bookID)
		bookID = this->ID;
}

string Book::print() const {
	stringstream ss, authorsSs;

	ss << (title.size() > 30 ? title.substr(0, 30) : title);
	ss << (title.size() >= 30 ? "\t" : "");
	for (int i = 30 - title.size(); i > 0; i -= 8)
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

	ss << editionYear << "\t" << (borrowed == 1 ? "Borrowed" : "Available");
	return ss.str();
}

string Book::printAuthors() const {
	stringstream ss, authorsSs;

	if (authors.size() > 0) {
		authorsSs << authors.at(0);
		for (unsigned x = 1; x < authors.size(); x++)
			authorsSs << ", " << authors.at(x);
	}
	ss << authorsSs.str().substr(0, 34);

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

unsigned int Book::getPageNumber() const {
	return pageNumber;
}

void Book::setPageNumber(int pageNumber) {
	this->pageNumber = pageNumber;
}

string Book::getISBN() const {
	return ISBN;
}

unsigned int Book::getEditionYear() const {
	return editionYear;
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

void Book::setEditionYear(unsigned int editionYear) {
	this->editionYear = editionYear;
}

bool Book::operator<(const Book& b2) const {
	if (editionYear < b2.editionYear)
		return true;
	else if (title < b2.title)
		return true;
	else if (authors[0] < b2.authors[0])
		return true;
	else
		return ID < b2.ID;
}
