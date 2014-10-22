#include "Book.h"
using namespace std;

Book::Book(string author, bool borrowed, string quota, unsigned int pageNumber,
		string isbn, string title) :
		author(author), borrowed(borrowed), quota(quota), pageNumber(
				pageNumber), isbn(isbn), title(title) {
}

Book::~Book() {

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

