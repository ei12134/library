#include "Library.h"
using namespace std;

unsigned long int Library::readerID = 1;

Library::Library() {
//	loadBooks();
//	loadBorrows();
	loadPersons();
	/* ...
	 * associations?
	 */
}

Library::~Library() {
	// save containers to files? then delete them
}

vector<Book*> Library::getBooks() const {
	return books;
}

vector<Borrow*> Library::getBorrows() const {
	return borrows;
}

vector<Person*> Library::getPersons() const {
	return persons;
}

void Library::setBooks(vector<Book*> books) {
	this->books = books;
}

void Library::setBorrows(vector<Borrow*> borrows) {
	this->borrows = borrows;
}

void Library::setPersons(vector<Person*> persons) {
	this->persons = persons;
}

void Library::addBook(Book* book) {
	books.push_back(book);
}

void Library::addBorrow(Borrow* borrow) {
	borrows.push_back(borrow);
}

void Library::addPerson(Person* person) {
	persons.push_back(person);
}

bool Library::removeBook(Book* book) {
	for (vector<Book*>::iterator it = books.begin(); it != books.end(); it++) {
		if (*it == book) {
			books.erase(it);
			return true;
		}
	}
	return false;
}

bool Library::removeBorrow(Borrow* borrow) {
	vector<Borrow*>::iterator it;
	for (it = borrows.begin(); it != borrows.end(); it++) {
		if (*it == borrow) {
			borrows.erase(it);
			return true;
		}
	}
	return false;
}

bool Library::removePerson(Person* person) {
	for (vector<Person*>::iterator it = persons.begin(); it != persons.end();
			it++) {
		if (*it == person) {
			persons.erase(it);
			return true;
		}
	}
	return false;
}

void Library::loadPersons() {
	fstream file;
	file.open(READERS_FILE);
	if (file.is_open()) {
		while (file.good()) {
			Reader* reader = new Reader(file);
			persons.push_back(reader);
		}
	}
	file.close();

	file.open(EMPLOYEES_FILE);
	if (file.is_open()) {
		while (file.good()) {
			Employee* employee = new Employee(file);
			persons.push_back(employee);
		}
	}
	file.close();

//	file.open(SUPERVISORS_FILE);
//	if (file.is_open()) {
//		while (file.good()) {
//			Supervisor* supervisor = new Supervisor(file);
//			persons.push_back(supervisor);
//		}
//	}
//	file.close();
}
