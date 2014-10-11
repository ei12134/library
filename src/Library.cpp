/*
 * Library.cpp
 *
 *  Created on: 08/10/2014
 *      Author: User
 */

#include "Library.h"
using namespace std;

unsigned long int Library::personID = 0;

Library::Library() {
	loadReaders();
	displayPersons();
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

vector<Person*> Library::getPersons() const {
	return persons;
}

void Library::setBooks(vector<Book*> books) {
	this->books = books;
}

//void Library::setBorrows(vector<Borrow*> borrows) {
//	this->borrows = borrows;
//}

void Library::setPersons(vector<Person*> persons) {
	this->persons = persons;
}

void Library::addBook(Book* book) {
	books.push_back(book);
}

void Library::addCurrentBorrow(Current* currentBorrow) {
	currentBorrows.push_back(currentBorrow);
}

void Library::addPerson(Person* person) {
	persons.push_back(person);
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

bool Library::removePerson(Person* person) {
	vector<Person*>::iterator it;
	for (it = persons.begin(); it != persons.end(); it++) {
		if (*it == person) {
			persons.erase(it);
			return true;
		}
	}
	return false;
}

// read from files
void Library::loadReaders() {

	string value;

	fstream file;
	file.open(READERS_FILE);
	if (file.is_open()) {
		if (!file.eof())
			getline(file, value);
		while (file.good()) {
			string nome, email, num;
			stringstream ss;
			unsigned int age;
			unsigned long int phone;
			unsigned long int cardID;

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
			getline(file, num, ';');
			ss << num;
			ss >> cardID;

			getline(file, value); //clear newline
			Reader *e = new Reader(nome, age, phone, email, cardID);
			persons.push_back(e);
		}
	}
}

void Library::displayPersons() {
	vector<Person*>::iterator it;
	for (it = persons.begin(); it != persons.end(); it++) {
		cout << (*it)->getName() << endl;
	}
}
