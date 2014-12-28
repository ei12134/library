#include "Book.h"
using namespace std;

unsigned long int Book::bookID = 0;

Book::Book(vector<string> authors, bool borrowed, string quota,
		unsigned int pageNumber, string ISBN, string title,
		unsigned int editionYear, bool deleted) :
		authors(authors), borrowed(borrowed), quota(quota), pageNumber(
				pageNumber), ISBN(ISBN), title(title), editionYear(editionYear), deleted(
				deleted) {
	ID = ++bookID;
}

Book::Book(stringstream& s) {
	stringstream ss;
	string book;
	string newAuthors, newBorrowed, newQuota, newPageNumber, newISBN, newTitle,
			newAuthor, newEditionYearStr, newDeletedStr, newIdStr;
	bool borrowed, deleted;
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

	if (!getline(s, newDeletedStr, ';'))
		throw Exception<string>("Error reading deleted", "Book");
	ss << newDeletedStr;
	ss >> deleted;
	ss.clear();
	this->deleted = deleted;

	if (!getline(s, newIdStr))
		throw Exception<string>("Error reading title", "Book");
	ss << newIdStr;
	ss >> newId;
	this->ID = newId;
	ss.clear();

	if (this->ID > bookID)
		bookID = this->ID;
}

Book::Book() {
	this->borrowed = false;
	this->title = "";
	this->pageNumber = 0;
	this->editionYear = 0;
	this->ID = 0;
	this->deleted = false;
	addAuthor("");
}

Book::~Book() {
}

string Book::print() const {
	stringstream ss, authorsSs;

	ss << (title.size() > 30 ? title.substr(0, 30) : title);
	ss << (title.size() >= 31 ? "\t" : "");
	for (int i = 31 - title.size(); i > 0; i -= 8)
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

	ss << editionYear << "\t";
	if (deleted)
		ss << "Deleted";
	else
		ss << (borrowed == 1 ? "Borrowed" : "Available");
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

bool Book::getDeleted() const {
	return deleted;
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

void Book::setDeleted(bool deleted) {
	this->deleted = deleted;
}

bool Book::operator<(const Book& b2) const {
	if (editionYear < b2.editionYear)
		return true;
	if (editionYear > b2.editionYear)
		return false;

	if (title < b2.title)
		return true;
	if (title > b2.title)
		return false;

	for (size_t i = 0; i < authors.size() && i < b2.authors.size(); i++)
		if (authors[i] < b2.authors[i])
			return true;

	return ID < b2.ID;
}
