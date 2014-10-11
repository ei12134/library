#include <iostream>
#include "Library.h"
using namespace std;

unsigned long int Library::personID = 0;

Library::Library() {
//	loadBooks();
//	loadBorrows();
	loadReaders();
//	loadEmployees();
//	loadSupervisors();
	/* ...
	 * associations?
	 */
}

Library::~Library() {
	// TODO Auto-generated destructor stub
}

vector<Book*> Library::getBooks() const {
	return books;
}

vector<Current*> Library::getCurrentBorrows() const {
	return currentBorrows;
}

vector<Reader*> Library::getReaders() const {
	return readers;
}

vector<Employee*> Library::getEmployees() const {
	return employees;
}

vector<Supervisor*> Library::getSupervisors() const {
	return supervisors;
}

void Library::setBooks(vector<Book*> books) {
	this->books = books;
}

//void Library::setBorrows(vector<Borrow*> borrows) {
//	this->borrows = borrows;
//}

void Library::setReaders(vector<Reader*> readers) {
	this->readers = readers;
}

void Library::setEmployees(vector<Employee*> employees) {
	this->employees = employees;
}

void Library::setSupervisors(vector<Supervisor*> supervisors) {
	this->supervisors = supervisors;
}

void Library::addBook(Book* book) {
	books.push_back(book);
}

void Library::addCurrentBorrow(Current* currentBorrow) {
	currentBorrows.push_back(currentBorrow);
}

void Library::addReader(Reader* reader) {
	readers.push_back(reader);
}

void Library::addEmployee(Employee* employee) {
	employees.push_back(employee);
}

void Library::addSupervisor(Supervisor* supervisor) {
	supervisors.push_back(supervisor);
}

bool Library::removeBook(Book* book) {
	vector<Book*>::iterator it;
	for (it = books.begin(); it != books.end(); it++) {
		if (*it == book) {
			books.erase(it);
			return true;
		}
	}
	return false;
}

bool Library::removeCurrentBorrow(Current* currentBorrow) {
	vector<Current*>::iterator it;
	for (it = currentBorrows.begin(); it != currentBorrows.end(); it++) {
		if (*it == currentBorrow) {
			currentBorrows.erase(it);
			return true;
		}
	}
	return false;
}

bool Library::removeReader(Reader* reader) {
	vector<Reader*>::iterator it;
	for (it = readers.begin(); it != readers.end(); it++) {
		if (*it == reader) {
			readers.erase(it);
			return true;
		}
	}
	return false;
}

bool Library::removeEmployee(Employee* employee) {
	vector<Employee*>::iterator it;
	for (it = employees.begin(); it != employees.end(); it++) {
		if (*it == employee) {
			employees.erase(it);
			return true;
		}
	}
	return false;
}

bool Library::removeSupervisor(Supervisor* supervisor) {
	vector<Supervisor*>::iterator it;
	for (it = supervisors.begin(); it != supervisors.end(); it++) {
		if (*it == supervisor) {
			supervisors.erase(it);
			return true;
		}
	}
	return false;
}

void Library::loadReaders() {

	string value;
	fstream file;
	file.open(READERS_FILE);

	if (file.is_open()) {
		if (!file.eof())
			getline(file, value);
		while (file.good()) {
			stringstream ss;
			string nome, email, num;
			unsigned int age;
			unsigned long int phone, cardID;

			getline(file, nome, ';');
			getline(file, num, ';');
			ss << num;
			ss >> age;

			num.clear();
			getline(file, num, ';');
			ss << num;
			ss >> phone;

			getline(file, email, ';');

			num.clear();
			getline(file, num); // read last input until newline
			ss << num;
			ss >> cardID;

			Reader *reader = new Reader(nome, age, phone, email, cardID);
			addReader(reader);
		}
	}
}
