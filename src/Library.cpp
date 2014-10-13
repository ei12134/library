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

vector<Current*> Library::getCurrentBorrows() const {
	return currentBorrows;
}

vector<Person*> Library::getPersons() const {
	return persons;
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

void Library::setPersons(vector<Person*> persons) {
	this->persons = persons;
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
//	if (file.is_open()) {
//		while (file.good()) {
//			Reader* ptr = new Reader(file);
//			persons.push_back(ptr);
//		}
//	}
	file.close();
}

//void Library::loadReaders() {
//	fstream file;
//	file.open(READERS_FILE);
//
//	if (file.is_open()) {
//		while (file.good()) {
//			stringstream ss;
//			string name, email, sAge, sPhone, sCard;
//			unsigned int age, phone, card;
//
//			getline(file, name, ';');
//			getline(file, sAge, ';');
//			ss << sAge;
//			ss >> age;
//			ss.clear();
//
//			getline(file, sPhone, ';');
//			ss << sPhone;
//			ss >> phone;
//			ss.clear();
//
//			getline(file, email, ';');
//
//			getline(file, sCard); // read last input until newline
//			ss << sCard;
//			ss >> card;
//			ss.clear();
//
//			Reader *reader = new Reader(name, age, phone, email, card);
//			addReader(reader);
//			readerID++;
//		}
//	}
//}
//
//void Library::loadEmployees() {
//	fstream file;
//	file.open(EMPLOYEES_FILE);
//
//	if (file.is_open()) {
//		while (file.good()) {
//			stringstream ss;
//			string name, email, sAge, sPhone, sNif, sWage;
//			unsigned int age, wage, phone, nif;
//
//			getline(file, name, ';');
//			getline(file, sAge, ';');
//			ss << sAge;
//			ss >> age;
//			ss.clear();
//
//			getline(file, sPhone, ';');
//			ss << sPhone;
//			ss >> phone;
//			ss.clear();
//
//			getline(file, email, ';');
//
//			getline(file, sNif, ';');
//			ss << sNif;
//			ss >> nif;
//			ss.clear();
//
//			getline(file, sWage); // read last input until newline
//			ss << sWage;
//			ss >> wage;
//			ss.clear();
//
//			Employee *employee = new Employee(name, age, phone, email, nif,
//					wage);
//			addEmployee(employee);
//		}
//	}
//}
//
//void Library::loadSupervisors() {
//	fstream file;
//	file.open(SUPERVISORS_FILE);
//
//	if (file.is_open()) {
//		while (file.good()) {
//			stringstream ss;
//			string name, email, sAge, sPhone, sNif, sWage;
//			unsigned int age, wage, phone, nif;
//
//			getline(file, name, ';');
//			getline(file, sAge, ';');
//			ss << sAge;
//			ss >> age;
//			ss.clear();
//
//			getline(file, sPhone, ';');
//			ss << sPhone;
//			ss >> phone;
//			ss.clear();
//
//			getline(file, email, ';');
//
//			getline(file, sNif, ';');
//			ss << sNif;
//			ss >> nif;
//			ss.clear();
//
//			getline(file, sWage); // read last input until newline
//			ss << sWage;
//			ss >> wage;
//			ss.clear();
//
//			Supervisor *supervisor = new Supervisor(name, age, phone, email,
//					nif, wage);
//			addSupervisor(supervisor);
//		}
//	}
//}
