#include "Library.h"
using namespace std;

unsigned long int Library::readerID = 1;

Library::Library() {
	loadBooks();
//	loadBorrows();
	loadPersons();
	/* ...
	 * associations?
	 */
}

void Library::saveBooks() {
	ofstream pFile("books.csv");
	//pFile<<"Author Borrowed Quota PageNumber Isbn Title";
	for (unsigned int i = 0; i < books.size(); i++) {
		pFile << books[i]->getAuthor() << ";" << books[i]->getBorrowed() << ";"
				<< books[i]->getQuota() << ";" << books[i]->getPageNumber()
				<< ";" << books[i]->getIsbn() << ";" << books[i]->getTitle()
				<< endl;
	}
	pFile.close();
}
void Library::saveEmployees() {
	ofstream pFile("employees.csv");
	//pFile<<"Author Borrowed Quota PageNumber Isbn Title";
	for (unsigned int i = 0; i < getEmployees().size(); i++) {
		pFile << getEmployees()[i]->getName() << ";"
				<< getEmployees()[i]->getAge() << ";"
				<< getEmployees()[i]->getEmail(); //remover este ";" e descomentar o resto
//
//				<< ";"
//				<< getEmployees()[i]->getnif<< ";" << getEmployees()[i]->getwage()
//				<<endl ;
	}
	pFile.close();
}

Library::~Library() {
	saveBooks();
	//savePersons etc...
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

vector<Person*> Library::getReaders() const {
	vector<Person*> readers;
	for (size_t i = 0; i < persons.size(); i++)
		if (persons[i]->getType() == 1)
			readers.push_back(persons[i]);
	return readers;
}

vector<Person*> Library::getEmployees() const {
	vector<Person*> employees;
	for (size_t i = 0; i < persons.size(); i++)
		if (persons[i]->getType() == 2)
			employees.push_back(persons[i]);
	return employees;
}

vector<Person*> Library::getSupervisors() const {
	vector<Person*> supervisors;
	for (size_t i = 0; i < persons.size(); i++)
		if (persons[i]->getType() == 3)
			supervisors.push_back(persons[i]);
	return supervisors;
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
}

void Library::loadBooks() {
	fstream file;
	file.open("books.csv");
	if (file.is_open()) {
		while (file.good()) {
			Book* bk = new Book(file);
			books.push_back(bk);
		}
	}
	file.close();
}
