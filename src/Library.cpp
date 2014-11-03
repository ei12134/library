#include "Library.h"
using namespace std;

Library::Library() {
	loadBooks();
	loadPersons();
	loadBorrowBooks();
	/* ...
	 * associations?
	 */
}

Library::~Library() {
	saveBooks();
	savePersons();
	SaveBorrows();
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
	for (size_t i = 0; i < borrows.size(); i++)
		if (borrows[i] == borrow) {
			borrows.erase(borrows.begin() + i);
			return true;
		}
	return false;
}
bool Library::removePerson(Person* person, Person* employee) {
	if (employee == NULL || employee == person)
		return false;
	for (size_t i = 0; i < persons.size(); i++)
		if (persons[i] == person) {
			persons.erase(persons.begin() + i);
			return true;
		}
	return false;
}

// --------------------------------------------------------------------------------------
// Load ---------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
void Library::loadPersons() {
	cout << "load persons" << endl;

// read employees
	ifstream file;
	file.open(EMPLOYEES_FILE);
	vector<Employee*> temp;
	if (file.is_open()) {
		while (file.good()) {
			Employee* employee = new Employee(file, false);

			//cout << employee->print() << endl;

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

						//cout << employee->print() << endl;

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

			//cout << reader->print() << endl;

			persons.push_back(reader);
		}
	}
	file.close();

}

void Library::loadBooks() {
	cout << "load books" << endl;

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
			unsigned int PosBook = -1;
			unsigned int PosEmplo = -1;
			unsigned int PosRead = -1;

			try {
				getline(file, data, ';');
				ss << data;
				ss >> bookID;
				ss.clear();
				data.clear();

				// book association
				for (unsigned x = 0; x < books.size(); x++)
					if (books[x]->getID() == bookID) {
						PosBook = x;
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

				// Reader association (nunca e zero)
				// Employee association (nunca e zero)
				for (unsigned x = 0; x < persons.size(); x++) {
					if (persons[x]->getNif() == EmpoyeeNIF) {
						PosEmplo = x;
					}
					if (persons[x]->getCard() == ReaderCard) {
						PosRead = x;
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

				if (PosBook == -1 || PosEmplo == -1 || PosRead == -1) {
					// checking error
				} else {
					// creating borrow
					Employee* emplo = dynamic_cast<Employee*>(persons[PosEmplo]);
					Reader* read = dynamic_cast<Reader*>(persons[PosRead]);

					if (emplo == NULL || read == NULL) {
						// error casting
					} else {
						Borrow* borrow = new Borrow(books[PosBook], emplo, read,
								dBorrow, dExpect, false);// false quando se faz DeliveredBook(dB) returned passa a true
						if (delivered == 1) {
							//cout << "delivered" << endl;

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

							borrow->DeliveredBook(dD);
						} else {// se nao tiver sido entrege e pk esta com o reader
							read->addBorrow(borrow);// add the borrow book to the reader
							books[PosBook]->setBorrowed(true);// set the book as borrowed
						}
						//cout << borrow->print() << endl;

						// ading borrow book to the vector
						borrows.push_back(borrow);
					}
				}
			} catch (Exception<int> &e) {
				cout << e.getValue() << endl;	// handle exeption
			}
		}
	}
	file.close();
// no final adicionar borrow books aos readers
}

// --------------------------------------------------------------------------------------
// save ---------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

void Library::saveBooks() {
	cout << "save books" << endl;

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
				<< books[i]->getIsbn() << ";" << books[i]->getTitle() << ";"
				<< books[i]->getID();
		if (i < ((int) books.size() - 1))
			pFile << endl;
	}
	pFile.close();
}

void Library::savePersons() {
	cout << "save person" << endl;

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
	cout << "save borrow" << endl;
	ofstream pFile(BORROWS_FILE);
	for (unsigned int x = 0; x < borrows.size(); x++) {
		borrows[x]->saveData(pFile);
		if (x < ((int) borrows.size() - 1))
			pFile << endl;
	}
	pFile.close();
}
