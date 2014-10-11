#include "Library.h"
using namespace std;

unsigned long int Library::readerID = 1;

Library::Library() {
//	loadBooks();
//	loadBorrows();
	loadReaders();
	loadEmployees();
	loadSupervisors();
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

void Library::setCurrentBorrows(vector<Current*> currentBorrows) {
	this->currentBorrows = currentBorrows;
}

void Library::setPreviousBorrows(vector<Previous*> previousBorrows) {
	this->previousBorrows = previousBorrows;
}

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

void Library::addPreviousBorrow(Previous* previousBorrow) {
	previousBorrows.push_back(previousBorrow);
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

bool Library::removePreviousBorrow(Previous* previousBorrow) {
	vector<Previous*>::iterator it;
	for (it = previousBorrows.begin(); it != previousBorrows.end(); it++) {
		if (*it == previousBorrow) {
			previousBorrows.erase(it);
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
	fstream file;
	file.open(READERS_FILE);

	if (file.is_open()) {
		while (file.good()) {
			stringstream ss;
			string name, email, sAge, sPhone, sCard;
			unsigned int age;
			unsigned long int phone, card;

			getline(file, name, ';');
			getline(file, sAge, ';');
			ss << sAge;
			ss >> age;

			getline(file, sPhone, ';');
			ss << sPhone;
			ss >> phone;

			getline(file, email, ';');

			getline(file, sCard); // read last input until newline
			ss << sCard;
			ss >> card;

			Reader *reader = new Reader(name, age, phone, email, card);
			addReader(reader);
			readerID++;
		}
	}
}

void Library::loadEmployees() {
	fstream file;
	file.open(EMPLOYEES_FILE);

	if (file.is_open()) {
		while (file.good()) {
			stringstream ss;
			string name, email, sAge, sPhone, sNif, sWage;
			unsigned int age;
			unsigned long int wage, phone, nif;

			getline(file, name, ';');
			getline(file, sAge, ';');
			ss << sAge;
			ss >> age;

			getline(file, sPhone, ';');
			ss << sPhone;
			ss >> phone;

			getline(file, email, ';');

			getline(file, sNif, ';');
			ss << sNif;
			ss >> nif;

			getline(file, sWage); // read last input until newline
			ss << sWage;
			ss >> wage;

			Employee *employee = new Employee(name, age, phone, email, nif,
					wage);
			addEmployee(employee);
		}
	}
}

void Library::loadSupervisors() {
	fstream file;
	file.open(EMPLOYEES_FILE);

	if (file.is_open()) {
		while (file.good()) {
			stringstream ss;
			string name, email, sAge, sPhone, sNif, sWage;
			unsigned int age;
			unsigned long int wage, phone, nif;

			getline(file, name, ';');
			getline(file, sAge, ';');
			ss << sAge;
			ss >> age;

			getline(file, sPhone, ';');
			ss << sPhone;
			ss >> phone;

			getline(file, email, ';');

			getline(file, sNif, ';');
			ss << sNif;
			ss >> nif;

			getline(file, sWage); // read last input until newline
			ss << sWage;
			ss >> wage;

			Supervisor *supervisor = new Supervisor(name, age, phone, email,
					nif, wage);
			addSupervisor(supervisor);
		}
	}
}
