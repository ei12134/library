#include "Book.h"
using namespace std;

Book::Book(string author, bool borrowed, string quota, unsigned int pageNumber,
		string isbn, string title) :
		author(author), borrowed(borrowed), quota(quota), pageNumber(
				pageNumber), isbn(isbn), title(title) {
}

Book::~Book() {

}
Book::Book(fstream& s) {
	{
		stringstream ss;

		string newauthor;
		string nborrowed;
		string newquota;
		string newpageNumber;

		string newisbn;
		string newtitle;

		string author;
		bool borrowed;
		string quota;
		unsigned int pageNumber;
		string isbn;
		string title;

		getline(s, newauthor, ';');
		ss << newauthor;
		ss >> author;
		ss.clear();
		this->author = author;

		getline(s, nborrowed, ';');
		ss << nborrowed;
		ss >> borrowed;
		ss.clear();
		this->borrowed = borrowed;

		getline(s, newquota, ';');
		ss << newquota;
		ss >> quota;
		ss.clear();
		this->quota = quota;

		getline(s, newpageNumber, ';');
		ss << newpageNumber;
		ss >> pageNumber;
		ss.clear();
		this->pageNumber = pageNumber;

		getline(s, newisbn, ';');
		ss << newisbn;
		ss >> isbn;
		ss.clear();
		this->isbn = isbn;

		getline(s, newtitle); // read last input until newline
		ss << newtitle;
		ss >> title;
		ss.clear();
		this->title = title;
	}
}

string Book::print() {
	stringstream ss;
	ss << author << "   " << borrowed << "   " << quota << "   " << pageNumber
			<< "   " << isbn << "   " << title;

	return ss.str();
}

string Book::getAuthor() {
	return author;
}
void Book::setAuthor(string author) {
	this->author = author;
}
bool Book::getBorrowed() {
	return borrowed;
}
void Book::setBorrowed(bool borrowed) {
	this->borrowed = borrowed;
}
string Book::getQuota() {
	return quota;
}
void Book::setQuota(string quota) {
	this->quota = quota;
}

int Book::getPageNumber() {
	return pageNumber;
}
void Book::setPageNumber(int pageNumber) {
	this->pageNumber = pageNumber;
}
string Book::getIsbn() {
	return isbn;
}
void Book::setIsbn(string isbn) {
	this->isbn = isbn;
}
string Book::getTitle() {
	return title;
}
void Book::setTitle(string title) {
	this->title = title;
}

