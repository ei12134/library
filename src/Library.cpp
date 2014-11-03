#include "Library.h"
using namespace std;

unsigned long int Library::readerID = 1;

Library::Library() {
	loadBooks();
	loadPersons();
//	loadBorrows();
	/* ...
	 * associations?
	 */
}

Library::~Library() {
	saveBooks();
	savePersons();
	// save containers to files? then delete them

	// destruir os pointer dos vectores
	for (unsigned x = 0; x < books.size(); x++)
		delete books[x];
	books.clear();
	for (unsigned x = 0; x < borrows.size(); x++)
		delete borrows[x];
	borrows.clear();
	for (unsigned x = 0; x < persons.size(); x++)
		delete persons[x];
	persons.clear();
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
		if (persons[i]->getType() == 2 || persons[i]->getType() == 3)
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

// --------------------------------------------------------------------------------------
// Load ---------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
void Library::loadPersons() {
//	cout << "load" << endl;

// read employees
	ifstream file;
	file.open(EMPLOYEES_FILE);
	vector<Employee*> temp;
	if (file.is_open()) {
		while (file.good()) {
			Employee* employee = new Employee(file, false);
			temp.push_back(employee);
		}
	}
	file.close();

// read supervisors
	stringstream ss;
	string employs;
	string e;
	file.open(SUPERVISORS_FILE);
	if (file.is_open()) {
		while (file.good()) {
			Employee* employee = new Employee(file, true);

			getline(file, employs);	// read last input until newline
			ss << employs;
			while (getline(ss, e, ',')) {
				for (unsigned x = 0; x < temp.size(); x++) {
					if (temp[x]->getName() == e) {// emplyee existe em memoria (se nao existir nao adiciona)
						employee->addEmplyee(temp[x]);
						break;
					}
				}
			}
			ss.clear();
			persons.push_back(employee);
		}
	}
	file.close();
// now add all the employees to the main vector
	persons.insert(persons.end(), temp.begin(), temp.end());

	/*cout
	 << endl << "************** printing all the date read**************  from files **************"
	 << endl << endl;
	 for (unsigned int x = 0; x < persons.size(); x++) {
	 cout << persons[x]->print() << endl;
	 }*/

	// read readers
	file.open(READERS_FILE);
	if (file.is_open()) {
		while (file.good()) {
			Reader* reader = new Reader(file);
			persons.push_back(reader);
		}
	}
	file.close();

}

void Library::loadBooks() {
	fstream file;
	file.open(BOOKS_FILE);
	if (file.is_open()) {
		while (file.good()) {
			Book* bk = new Book(file);
			books.push_back(bk);
		}
	}
	file.close();
}

void Library::loadBorrowBooks() {
	// no final adicionar borrow books aos readers
}

// --------------------------------------------------------------------------------------
// save ---------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

void Library::saveBooks() {
	ofstream pFile(BOOKS_FILE);

	for (unsigned int i = 0; i < books.size(); i++) {
		vector<string> authors = books[i]->getAuthors();
		if (authors.size() > 0) {
			pFile << authors.at(0);
			for (unsigned x = 1; x < authors.size(); x++)
				pFile << "," << authors.at(x);
		}
		pFile << ";" << books[i]->getBorrowed() << ";" << books[i]->getQuota()
				<< ";" << books[i]->getPageNumber() << ";"
				<< books[i]->getIsbn() << ";" << books[i]->getTitle();
		if (i < (books.size() - 1))
			pFile << endl;
	}
	pFile.close();
}

void Library::savePersons() {
//	cout << "save" << endl;

	// solution for the endl line in the final of the files
	bool notFistRead = false;
	bool notFistEmp = false;
	bool notFistSup = false;

	ofstream pFileEmplayees(EMPLOYEES_FILE);
	ofstream pFileSuperviseres(SUPERVISORS_FILE);
	ofstream pFileReaders(READERS_FILE);

	for (unsigned int i = 0; i < persons.size(); i++) {
//		cout << persons[i]->print() << endl;

		switch (persons[i]->getType()) {
		case 1:	// reader
			if (notFistRead)
				pFileReaders << endl;
			else
				notFistRead = true;

			persons[i]->saveData(pFileReaders);
			break;
		case 2:	// employee
			if (notFistEmp)
				pFileEmplayees << endl;
			else
				notFistEmp = true;

			persons[i]->saveData(pFileEmplayees);
			break;
		case 3: // supervisor
			if (notFistSup)
				pFileSuperviseres << endl;
			else
				notFistSup = true;

			persons[i]->saveData(pFileSuperviseres);
			break;
		default:
			break;
		}
	}

	pFileReaders.close();
	pFileSuperviseres.close();
	pFileEmplayees.close();

}

void Library::SaveBorrows() {
	ofstream pFile(BORROWS_FILE);
	pFile.close();
}
