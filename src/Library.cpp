#include "Library.h"
using namespace std;

Library::Library() {
	loadBooks();
	loadPersons();
	loadBorrowBooks();
}

Library::~Library() {
	saveBooks();
	savePersons();
	saveBorrows();

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

vector<Book*> Library::getAvailableBooks() const {
	vector<Book*> available;
	for (size_t i = 0; i < books.size(); i++)
		if (!books[i]->getBorrowed())
			available.push_back(books[i]);

	return available;
}

vector<Borrow*> Library::getBorrowedBooksFromReader(Person* p) const {
	vector<Borrow*> b;
	if (p->getType() != 1)
		return b;
	for (unsigned int x = 0; x < borrows.size(); x++) {
		if (borrows[x]->getReader()->getCard() == p->getCard()
				&& borrows[x]->isReturned())
			b.push_back(borrows[x]);
	}
	return b;
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
vector<Person*> Library::getEmployeesNoSupervisors() const {
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
	if (book == NULL)
		return false;
	for (size_t i = 0; i < books.size(); i++)
		if (books[i] == book) {
			books.erase(books.begin() + i);
			return true;
		}
	return false;
}

bool Library::removeBorrow(Borrow* borrow) {
	if (borrow == NULL)
		return false;
	borrow->getBook()->setBorrowed(false);
	borrow->setReturned(borrow);
	return true;
}

bool Library::removeReader(Person* reader) {
	if (reader == NULL)
		return false;
	for (size_t i = 0; i < persons.size(); i++)
		if (persons[i] == reader) {
			if (reader->getBorrowedBooks().size() == 0) {
				persons.erase(persons.begin() + i);
				return true;
			}
		}
	return false;
}

bool Library::removeEmployee(Person* person, Person* employee) {
	if (employee == NULL || employee == person)
		return false;
	for (size_t i = 0; i < persons.size(); i++)
		if (persons[i] == person) {
			persons.erase(persons.begin() + i);
			return true;
		}
	return false;
}

bool Library::removeEmployeeFromSupervisors(Employee* employee) {
	if (employee == NULL)
		return false;
	for (size_t i = 0; i < persons.size(); i++)
		if (persons[i]->getType() == 3)
			persons[i]->removeEmplyee(employee);
	return true;
}

void Library::loadPersons() {
	string line;
	stringstream fs;
	persons.clear();
// read employees
	ifstream file;
	file.open(EMPLOYEES_FILE);
	vector<Employee*> temp;
	if (file.is_open()) {
		while (file.good()) {
			try {
				getline(file, line, '\n');
				fs << line;
				Employee* employee = new Employee(fs, false);
				temp.push_back(employee);

			} catch (Exception<string> &e) {
			}
			fs.clear();
		}
	}
	file.close();

// read supervisors
	string employs;
	string e;
	file.open(SUPERVISORS_FILE);
	if (file.is_open()) {
		while (file.good()) {
			try {
				getline(file, line, '\n');
				fs << line;
				Employee* employee = new Employee(fs, true);

				while (getline(fs, e, ',')) {
					for (unsigned x = 0; x < temp.size(); x++) {
						if (temp[x]->getName() == e) { // check if employee exists in memory
							employee->addEmplyee(temp[x]);
							break;
						}
					}
				}
				persons.push_back(employee);
			} catch (Exception<string> &e) {
			}
			fs.clear();
		}
	}
	file.close();

// add all employees to the main vector
	persons.insert(persons.end(), temp.begin(), temp.end());

// read readers
	file.open(READERS_FILE);
	if (file.is_open()) {
		while (file.good()) {
			try {
				getline(file, line, '\n');
				fs << line;
				Reader* reader = new Reader(fs);
				persons.push_back(reader);
				fs.clear();
			} catch (Exception<string> &e) {
			}

		}
	}
	file.close();

}

void Library::loadBooks() {
	books.clear();
	fstream file;
	string line;
	stringstream ss;
	file.open(BOOKS_FILE);
	if (file.is_open()) {
		while (file.good()) {
			try {
				ss.clear();
				getline(file, line, '\n');
				ss << line;
				Book* bk = new Book(ss);
				books.push_back(bk);
			} catch (Exception<string> &e) {
			}
		}
	}
	file.close();
}

void Library::loadBorrowBooks() {
	ifstream file;
	file.open(BORROWS_FILE);
	if (file.is_open()) {
		while (file.good()) {
			stringstream ss;
			stringstream temps;
			string data;
			unsigned long int bookID;
			unsigned long int EmpoyeeNIF;
			unsigned long int ReaderCard;
			unsigned int dia, mes, ano;
			int delivered;
			int posBook, posEmplo, posRead = -1;

			try {
				getline(file, data, ';');
				ss << data;
				ss >> bookID;
				ss.clear();
				data.clear();

				// book association
				for (unsigned x = 0; x < books.size(); x++)
					if (books[x]->getID() == bookID) {
						posBook = x;
						break;
					}

				getline(file, data, ';');
				ss << data;
				ss >> EmpoyeeNIF;
				ss.clear();
				data.clear();

				getline(file, data, ';');
				ss << data;
				ss >> ReaderCard;
				ss.clear();
				data.clear();

				// Reader association (shouldn't be 0)
				// Employee association (shouldn't be 0)
				for (unsigned x = 0; x < persons.size(); x++) {
					if (persons[x]->getNif() == EmpoyeeNIF) {
						posEmplo = x;
					}
					if (persons[x]->getCard() == ReaderCard) {
						posRead = x;
					}
				}

				getline(file, data, ',');
				ss << data;
				ss >> dia;
				ss.clear();
				data.clear();
				getline(file, data, ',');
				ss << data;
				ss >> mes;
				ss.clear();
				data.clear();
				getline(file, data, ';');
				ss << data;
				ss >> ano;
				ss.clear();
				data.clear();
				Date dBorrow(dia, mes, ano);

				getline(file, data, ',');
				ss << data;
				ss >> dia;
				ss.clear();
				data.clear();
				getline(file, data, ',');
				ss << data;
				ss >> mes;
				ss.clear();
				data.clear();
				getline(file, data, ';');
				ss << data;
				ss >> ano;
				ss.clear();
				data.clear();
				Date dExpect(dia, mes, ano);

				getline(file, data);
				ss << data;
				data.clear();

				getline(ss, data, ';');	// caso nao acabe em ; tira que le estiver
				temps << data;
				temps >> delivered;
				temps.clear();
				data.clear();

				if (posBook == -1 || posEmplo == -1 || posRead == -1) {
					// checking error
				} else {
					// creating borrow
					Person* employee = persons[posEmplo];
					Person* reader = persons[posRead];

					if (employee == NULL || reader == NULL) {
						// error casting
					} else {
						Borrow* borrow = new Borrow(books[posBook], employee,
								reader, dBorrow, dExpect);// false quando se faz DeliveredBook(dB) returned passa a true
						if (delivered == 1) {
							getline(ss, data, ',');
							temps << data;
							temps >> dia;
							temps.clear();
							data.clear();
							getline(ss, data, ',');
							temps << data;
							temps >> mes;
							temps.clear();
							data.clear();
							getline(ss, data);
							temps << data;
							temps >> ano;
							temps.clear();
							data.clear();
							ss.clear();
							Date dD(dia, mes, ano);

							borrow->deliveredBook(dD);
						} else {// se nao tiver sido entrege e pk esta com o reader
							reader->addBorrow(borrow);// add the borrow book to the reader
							books[posBook]->setBorrowed(true);// set the book as borrowed
						}

						// ading borrow book to the vector
						borrows.push_back(borrow);
					}
				}
			} catch (Exception<int> &e) {
			}
		}
	}
	file.close();
// at borrow to reader
}

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
				<< books[i]->getISBN() << ";" << books[i]->getTitle() << ";"
				<< books[i]->getID();
		if (i < (-1 + books.size()))
			pFile << endl;
	}
	pFile.close();
}

void Library::savePersons() {
	bool notFistRead = false;
	bool notFistEmp = false;
	bool notFistSup = false;

	ofstream pFileEmplayees(EMPLOYEES_FILE);
	ofstream pFileSuperviseres(SUPERVISORS_FILE);
	ofstream pFileReaders(READERS_FILE);

	for (unsigned int i = 0; i < persons.size(); i++) {
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

void Library::saveBorrows() {
	ofstream pFile(BORROWS_FILE);
	for (unsigned int x = 0; x < borrows.size(); x++) {
		borrows[x]->saveData(pFile);
		if (x < (-1 + borrows.size()))
			pFile << endl;
	}
	pFile.close();
}

void Library::SupervisorEmployeeRandom() {
	vector<Person*> sup = getSupervisors();
	vector<Person*> emp = getEmployeesNoSupervisors();

	for (unsigned int x = 0; x < sup.size(); x++) {
		Employee* e = dynamic_cast<Employee*>(sup[x]);
		if (e != NULL)
			e->removeAllEmplyee();
	}
	for (unsigned int x = 0; x < emp.size(); x++) {
		Employee* e = dynamic_cast<Employee*>(sup.at(x % sup.size()));
		if (e != NULL) {
			Employee* e2 = dynamic_cast<Employee*>(emp[x]);
			if (e2 != NULL)
				e->addEmplyee(e2);
		}
	}
}

bool compareName(const Person* p1, const Person* p2) {
	return p1->getName() < p2->getName();
}

bool compareAge(const Person* p1, const Person* p2) {
	return p1->getAge() < p2->getAge();
}

bool compareCard(const Person* p1, const Person* p2) {
	if (p1->getType() == 1 && p1->getType() == 1)
		return p1->getCard() < p2->getCard();
	else
		return false;
}

bool compareType(const Person* p1, const Person* p2) {
	return p1->getType() < p2->getType();
}

bool compareBorrow(const Person* p1, const Person* p2) {
	return p1->getBorrowedBooks().size() > p2->getBorrowedBooks().size();
}

bool compareTitle(const Book* b1, const Book* b2) {
	return b1->getTitle() < b2->getTitle();
}

bool compareISBN(const Book* b1, const Book* b2) {
	return b1->getISBN() < b2->getISBN();
}

void Library::sortByType() {
	sort(persons.begin(), persons.end(), compareType);
}

void Library::sortByName() {
	sort(persons.begin(), persons.end(), compareName);
}

void Library::sortByAge() {
	sort(persons.begin(), persons.end(), compareAge);
}

void Library::sortByBorrow() {
	sort(persons.begin(), persons.end(), compareBorrow);
}

void Library::sortByTitle() {
	sort(books.begin(), books.end(), compareTitle);
}

void Library::sortByISBN() {
	sort(books.begin(), books.end(), compareISBN);
}
