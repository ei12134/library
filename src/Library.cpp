#include "Library.h"
using namespace std;

bool compareName(const Person* p1, const Person* p2) {
	return p1->getName() < p2->getName();
}

bool compareAge(const Person* p1, const Person* p2) {
	return p1->getAge() < p2->getAge();
}

bool comparePhone(const Person* p1, const Person* p2) {
	return p1->getPhone() < p2->getPhone();
}

bool compareEmail(const Person* p1, const Person* p2) {
	return p1->getEmail() < p2->getEmail();
}

bool compareCard(const Person* p1, const Person* p2) {
	if (p1->getType() == 1 && p1->getType() == 1)
		return p1->getCard() < p2->getCard();
	else
		return false;
}

bool compareBorrow(const Person* p1, const Person* p2) {
	return p1->getBorrowedBooks().size() > p2->getBorrowedBooks().size();
}

bool compareTitle(Book* b1, Book* b2) {
	return b1->getTitle() < b2->getTitle();
}

bool compareAuthor(Book* b1, Book* b2) {
	return b1->getAuthors()[0] < b2->getAuthors()[0];
}

bool compareYear(Book* b1, Book* b2) {
	return b1->getEditionYear() < b2->getEditionYear();
}

bool compareStatus(Book* b1, Book* b2) {
	return b1->getBorrowed() < b2->getBorrowed();
}

Library::Library() :
		booksTree(compareBooks) {
	loadBooks();
	loadPersons();
	loadBorrows();
	loadRequests();
	buildHashTable();
	sort(persons.begin(), persons.end(), compareName);
}

Library::~Library() {
	saveBooks();
	savePersons();
	saveBorrows();
	saveRequests();

	booksTree.clear();
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

bool Library::removeReaderFromHashTable(Person* reader) {
	iteratorH it = inactiveReaders.find(reader);
	if (it != inactiveReaders.end()) {
		inactiveReaders.erase(it);
		return true;
	}
	return false;
}

bool Library::addReaderToHashTable(Person* reader) {
	pair<iteratorH, bool> it = inactiveReaders.insert(reader);
	return it.second;
}

string Library::borrowQueuedRequest(Borrow* b) {
	if (b == NULL)
		return "";
	string readerName = "";
	stack<Request> temp;
	while (!requestsQueue.empty()) {
		Request req = requestsQueue.top();
		requestsQueue.pop();
		Reader* r = static_cast<Reader*>(req.getReader());
		if (req.getBook()->getID() == b->getBook()->getID()) {
			Borrow* borrow = new Borrow(b->getBook(), b->getEmployee(), r);
			if (r->addBorrow(borrow)) {
				addBorrow(borrow);
				readerName = r->getName();
				break;
			} else
				delete borrow;
		}
		temp.push(req);
	}
	while (!temp.empty()) {
		requestsQueue.push(temp.top());
		temp.pop();
	}
	return readerName;
}

void Library::updateInactiveReaders() {
	inactiveReaders.clear();
	vector<Person*> readers = getReaders();
	for (size_t i = 0; i < readers.size(); i++) {
		Reader *r = static_cast<Reader*>(readers[i]);
		if (r->checkInactiveByDate()) // returns true if is incative by date
			inactiveReaders.insert(readers[i]);
	}
}

vector<Book*> Library::getBooks() const {
	vector<Book*> availableBooks;
	for (size_t i = 0; i < books.size(); i++)
		if (!books[i]->getDeleted())
			availableBooks.push_back(books[i]);

	return availableBooks;
}

set<Book*, bool (*)(const Book*, const Book*)> Library::getBooksTree() const {
	return booksTree;
}

vector<Book*> Library::getAvailableBooks() const {
	vector<Book*> available;
	for (size_t i = 0; i < books.size(); i++)
		if (!books[i]->getBorrowed() && !books[i]->getDeleted())
			available.push_back(books[i]);

	return available;
}

vector<Borrow*> Library::getReaderBorrows(Person* p) const {
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

vector<Book*> Library::getBorrowedBooks() const {
	vector<Book*> available;
	for (size_t i = 0; i < books.size(); i++)
		if (books[i]->getBorrowed() && !books[i]->getDeleted())
			available.push_back(books[i]);

	return available;
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

vector<Person*> Library::getEmployees(bool supervisors) const {
	vector<Person*> employees;
	for (size_t i = 0; i < persons.size(); i++) {
		if (persons[i]->getType() == 2
				|| (persons[i]->getType() == 3 && supervisors))
			employees.push_back(persons[i]);
	}
	return employees;
}

vector<Person*> Library::getSupervisors() const {
	vector<Person*> supervisors;
	for (size_t i = 0; i < persons.size(); i++)
		if (persons[i]->getType() == 3)
			supervisors.push_back(persons[i]);
	return supervisors;
}

priority_queue<Request> Library::getRequests() const {
	return requestsQueue;
}

vector<string> Library::getSortedPrint(int type, int sortFunc) {
	switch (type) {
	case PERSON:
		return sortPersons(getPersons(), sortFunc);
		break;
	case READER:
		return sortPersons(getReaders(), sortFunc);
		break;
	case EMPLOYEE:
		return sortPersons(getEmployees(false), sortFunc);
		break;
	case SUPERVISOR:
		return sortPersons(getSupervisors(), sortFunc);
		break;
	case EMPLOYEE_OR_SUPERVISOR:
		return sortPersons(getEmployees(true), sortFunc);
		break;
	case BOOK:
		return sortBooks(sortFunc);
		break;
	default:
		break;
	}
	vector<string> print;
	return print;
}

vector<string> Library::getBooksTreePrint() const {
	vector<string> print;
	for (set<Book*, bool (*)(const Book*, const Book*)>::const_iterator it =
			booksTree.begin(); it != booksTree.end(); it++)
		print.push_back((*it)->print());
	return print;
}

vector<string> Library::getBooksTreePrintByYear(unsigned int year) const {
	vector<string> print;
	Book* b = new Book;
	Book* b2 = new Book;
	b->setEditionYear(year);
	b2->setEditionYear(year + 1);

	set<Book*, bool (*)(const Book*, const Book*)>::const_iterator lower =
			booksTree.upper_bound(b);

	set<Book*, bool (*)(const Book*, const Book*)>::const_iterator upper =
			booksTree.lower_bound(b2);

	for (set<Book*, bool (*)(const Book*, const Book*)>::const_iterator it =
			lower; it != upper && it != booksTree.end(); it++) {
		print.push_back((*it)->print());
	}

	return print;
}

vector<string> Library::getBooksTreePrintByTitle(string title) const {
	vector<string> print;
	for (set<Book*, bool (*)(const Book*, const Book*)>::const_iterator it =
			booksTree.begin(); it != booksTree.end(); it++) {
		if (partialMatchQueryPermissive(title, (*it)->getTitle()))
			print.push_back((*it)->print());
	}

	return print;
}

vector<string> Library::getBooksTreePrintByAuthor(string author) const {
	vector<string> print;
	for (set<Book*, bool (*)(const Book*, const Book*)>::const_iterator it =
			booksTree.begin(); it != booksTree.end(); it++) {
		vector<string> authors = (*it)->getAuthors();
		for (size_t i = 0; i < authors.size(); i++)
			if (partialMatchQueryPermissive(author, authors[i])) {
				print.push_back((*it)->print());
				break;
			}
	}

	return print;
}

vector<string> Library::getPriorityQueuePrint() const {
	vector<string> print;
	priority_queue<Request> copy = requestsQueue;
	while (!copy.empty()) {
		print.push_back(copy.top().print());
		copy.pop();
	}

	return print;
}

vector<string> Library::getPriorityQueuePrintByReader(Person* reader) const {
	vector<string> print;
	priority_queue<Request> copy = requestsQueue;
	while (!copy.empty()) {
		if (copy.top().getReader() == reader)
			print.push_back(copy.top().print());
		copy.pop();
	}

	return print;
}

vector<string> Library::getHashTablePrint() const {
	vector<string> print;
	for (cIteratorH it = inactiveReaders.begin(); it != inactiveReaders.end();
			it++) {
		print.push_back((*it)->print());
	}

	return print;
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

void Library::addTreeBook(Book* book) {
	booksTree.insert(book);
}

void Library::addBorrow(Borrow* borrow) {
	Person* reader = borrow->getReader();
	Book* book = borrow->getBook();
	if (reader != NULL)
		removeReaderFromHashTable(reader);
	if (book != NULL)
		book->setBorrowed(true);
	borrows.push_back(borrow);
	saveBorrows();
}

void Library::addPerson(Person* person) {
	persons.push_back(person);
}

bool Library::addRequest(Request request) {
	priority_queue<Request> copy = requestsQueue;
	while (!copy.empty()) {
		if (copy.top() == request) {
			return false;
		}
		copy.pop();
	}
	requestsQueue.push(request);
	return true;
}

bool Library::removeBook(Book* book) {
	if (book == NULL)
		return false;
	for (size_t i = 0; i < books.size(); i++)
		if (books[i] == book) {
			set<Book*, bool (*)(const Book*, const Book*)>::const_iterator it =
					booksTree.find(book);
			if (it != booksTree.end()) {
				booksTree.erase(it);
				removeRequestByBook(books[i]);
				books[i]->setDeleted(true);
				return true;
			}
		}
	return false;
}

bool Library::removeTreeBook(Book* book) {
	set<Book*, bool (*)(const Book*, const Book*)>::iterator it =
			booksTree.find(book);
	if (it == booksTree.end())
		return false;
	else
		booksTree.erase(book);
	return true;
}

bool Library::removeBorrow(Borrow* borrow) {
	if (borrow == NULL)
		return false;
	borrow->getBook()->setBorrowed(false);
	borrow->setReturned(true);
	return true;
}

bool Library::removeReader(Person* reader) {
	if (reader == NULL)
		return false;
	for (size_t i = 0; i < persons.size(); i++)
		if (persons[i] == reader) {
			if (reader->getBorrowedBooks().size() == 0) {
				removeReaderFromHashTable(persons[i]);
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
			persons[i]->removeEmployee(employee);
	return true;
}

bool Library::removeRequestByBook(Book* book) {
	stack<Request> temp;
	bool success = false;

	while (!requestsQueue.empty()) {
		Request req = requestsQueue.top();
		requestsQueue.pop();
		if (req.getBook()->getID() == book->getID()) {
			success = true;
		} else
			temp.push(req);
	}
	while (!temp.empty()) {
		requestsQueue.push(temp.top());
		temp.pop();
	}
	return success;
}

bool Library::removeRequestByReader(Person* reader) {
	stack<Request> temp;
	bool success = false;
	vector<Person*> employees = getEmployees(true);
	if (employees.size() == 0)
		return success;
	Person* employee = employees[0];

	while (!requestsQueue.empty()) {
		Request req = requestsQueue.top();
		requestsQueue.pop();
		if (req.getReader()->getCard() == reader->getCard()) {
			if (!req.getBook()->getBorrowed()) {
				Borrow* borrow = new Borrow(req.getBook(), employee, reader);
				reader->addBorrow(borrow);
				addBorrow(borrow);
				success = true;
				break;
			}
		} else
			temp.push(req);
	}
	while (!temp.empty()) {
		requestsQueue.push(temp.top());
		temp.pop();
	}
	return success;
}

bool Library::removeRequest(const Request &request) {
	stack<Request> temp;
	bool success = false;
	while (!requestsQueue.empty()) {
		Request req = requestsQueue.top();
		requestsQueue.pop();
		if (req.getBook()->getID() == request.getBook()->getID()
				&& req.getReader()->getCard()
						== request.getReader()->getCard()) {
			success = true;
			break;
		} else
			temp.push(req);
	}
	while (!temp.empty()) {
		requestsQueue.push(temp.top());
		temp.pop();
	}
	return success;
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
							employee->addEmployee(temp[x]);
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
				if (!bk->getDeleted())
					booksTree.insert(bk);
			} catch (Exception<string> &e) {
			}
		}
	}
	file.close();
}

void Library::loadBorrows() {
	ifstream file;
	string line;
	stringstream bf;
	file.open(BORROWS_FILE);
	if (file.is_open()) {
		while (file.good()) {
			bf.clear();
			getline(file, line, '\n');
			bf << line;
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
				if (!getline(bf, data, ';'))
					throw Exception<string>("Error reading bookID", "Borrow");
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

				if (!getline(bf, data, ';'))
					throw Exception<string>("Error reading employee Nif",
							"Borrow");
				ss << data;
				ss >> EmpoyeeNIF;
				ss.clear();
				data.clear();

				if (!getline(bf, data, ';'))
					throw Exception<string>("Error reading reader card",
							"Borrow");
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

				if (!getline(bf, data, ','))
					throw Exception<string>("Error reading day", "Borrow");
				ss << data;
				ss >> dia;
				ss.clear();
				data.clear();
				if (!getline(bf, data, ','))
					throw Exception<string>("Error reading month", "Borrow");
				ss << data;
				ss >> mes;
				ss.clear();
				data.clear();
				if (!getline(bf, data, ';'))
					throw Exception<string>("Error reading year", "Borrow");
				ss << data;
				ss >> ano;
				ss.clear();
				data.clear();
				Date dBorrow(dia, mes, ano);

				if (!getline(bf, data, ','))
					throw Exception<string>("Error reading day", "Borrow");
				ss << data;
				ss >> dia;
				ss.clear();
				data.clear();
				if (!getline(bf, data, ','))
					throw Exception<string>("Error reading month", "Borrow");
				ss << data;
				ss >> mes;
				ss.clear();
				data.clear();
				if (!getline(bf, data, ';'))
					throw Exception<string>("Error reading year", "Borrow");
				ss << data;
				ss >> ano;
				ss.clear();
				data.clear();
				Date dExpect(dia, mes, ano);

				getline(bf, data, ';');

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
							if (!getline(bf, data, ','))
								throw Exception<string>("Error reading day",
										"Borrow");
							temps << data;
							temps >> dia;
							temps.clear();
							data.clear();
							if (!getline(bf, data, ','))
								throw Exception<string>("Error reading month",
										"Borrow");
							temps << data;
							temps >> mes;
							temps.clear();
							data.clear();
							if (!getline(bf, data))
								throw Exception<string>("Error reading year",
										"Borrow");
							temps << data;
							temps >> ano;
							temps.clear();
							data.clear();
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
			} catch (Exception<string> &e) {
//				cout << e.getMessage();
			} catch (Exception<int> &e) {
			}
		}
	}
	file.close();
// at borrow to reader
}

void Library::loadRequests() {
// book id ; reader card ; day , month , year
	ifstream file;
	string line;
	stringstream bf;
	file.open(REQUESTS_FILE);
	if (file.is_open()) {
		while (file.good()) {
			bf.clear();
			getline(file, line, '\n');
			bf << line;
			stringstream ss;
			stringstream temps;
			string Values;
			unsigned long int ReaderCard;
			unsigned long int bookID;
			unsigned int dia, mes, ano;
			int posBook, posRead = -1;

			try {
				if (!getline(bf, Values, ';'))
					throw Exception<string>("Error reading bookID", "Request");
				ss << Values;
				ss >> bookID;
				ss.clear();
				Values.clear();

				// book association
				for (unsigned x = 0; x < books.size(); x++)
					if (books[x]->getID() == bookID) {
						posBook = x;
						break;
					}

				if (!getline(bf, Values, ';'))
					throw Exception<string>("Error reading reader card",
							"Request");
				ss << Values;
				ss >> ReaderCard;
				ss.clear();
				Values.clear();

				// Reader association (shouldn't be 0)
				for (unsigned x = 0; x < persons.size(); x++) {
					if (persons[x]->getCard() == ReaderCard) {
						posRead = x;
					}
				}

				if (!getline(bf, Values, ','))
					throw Exception<string>("Error reading day", "Request");
				ss << Values;
				ss >> dia;
				ss.clear();
				Values.clear();
				if (!getline(bf, Values, ','))
					throw Exception<string>("Error reading month", "Request");
				ss << Values;
				ss >> mes;
				ss.clear();
				Values.clear();
				if (!getline(bf, Values, ';'))
					throw Exception<string>("Error reading year", "Request");
				ss << Values;
				ss >> ano;
				ss.clear();
				Values.clear();
				Date requestDate(dia, mes, ano);

				if (posBook == -1 || posRead == -1) {
					// checking error
				} else {
					// creating Request
					Person* reader = persons[posRead];

					if (reader == NULL) {
						// error casting
					} else {
						Request request(books[posBook], reader, requestDate);
						// adding Request Book to the priority queue
						requestsQueue.push(request);
					}
				}
			} catch (Exception<string> &e) {
			} catch (Exception<int> &e) {
			}
		}
	}
	file.close();
}

void Library::buildHashTable() {
	vector<Person*> readers = getReaders();
	for (size_t i = 0; i < readers.size(); i++) {
		Reader *r = static_cast<Reader*>(readers[i]);
		if (r->getInactive())
			inactiveReaders.insert(readers[i]);
	}
}

void Library::saveRequests() {
	ofstream pFile(REQUESTS_FILE);
	priority_queue<Request> copy = requestsQueue;
	while (!copy.empty()) {
		Request tempR = copy.top();
		tempR.saveData(pFile);
		copy.pop();
		if (!copy.empty())
			pFile << endl;
	}
	pFile.close();
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
				<< books[i]->getEditionYear() << ";" << books[i]->getDeleted()
				<< ";" << books[i]->getID();
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
		case 3:	// supervisor
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

void Library::assignEmployees() {
	vector<Person*> sup = getSupervisors();
	vector<Person*> emp = getEmployees(false);

	for (unsigned int x = 0; x < sup.size(); x++) {
		Employee* e = dynamic_cast<Employee*>(sup[x]);
		if (e != NULL)
			e->clearEmployeesTeam();
	}
	for (unsigned int x = 0; x < emp.size(); x++) {
		Employee* e = dynamic_cast<Employee*>(sup.at(x % sup.size()));
		if (e != NULL) {
			Employee* e2 = dynamic_cast<Employee*>(emp[x]);
			if (e2 != NULL)
				e->addEmployee(e2);
		}
	}
}

vector<string> Library::sortPersons(vector<Person*> vec, size_t compareType) {
	vector<Person*> vecCpy = vec;
	switch (compareType) {
	case 0:
		sort(vecCpy.begin(), vecCpy.end(), compareName);
		break;
	case 1:
		sort(vecCpy.begin(), vecCpy.end(), compareAge);
		break;
	case 2:
		sort(vecCpy.begin(), vecCpy.end(), comparePhone);
		break;
	case 3:
		sort(vecCpy.begin(), vecCpy.end(), compareEmail);
		break;
	case 4:
		sort(vecCpy.begin(), vecCpy.end(), compareCard);
		break;
	default:
		break;
	}
	return getContainerPtrPrint(vecCpy);
}

vector<string> Library::sortBooks(size_t compareType) {
	vector<Book*> vec = books;
	switch (compareType) {
	case 0:
		sort(vec.begin(), vec.end(), compareTitle);
		break;
	case 1:
		sort(vec.begin(), vec.end(), compareAuthor);
		break;
	case 2:
		sort(vec.begin(), vec.end(), compareYear);
		break;
	case 3:
		sort(vec.begin(), vec.end(), compareStatus);
		break;
	default:
		break;
	}
	return getContainerPtrPrint(vec);
}
