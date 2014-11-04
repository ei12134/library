#include "Interface.h"

Interface::Interface() {
	menu();
}

Interface::~Interface() {
}

void Interface::menu() {
	char input;
	string exitDialog = "Exit the program?";
	string header = "Library";
	bool exit = false;
	vector<Person*> persons = library.getPersons();
	do {
		clearScreen();
		displayHeader(header);
		cout << endl << TETRA_TAB << "[1] Login\n\n";
		cout << TETRA_TAB << "[2] Display\n\n";
		cout << TETRA_TAB << "[3] Quit\n\n" << TRI_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			dispatchPerson(searchPerson(library.getPersons()));
			break;
		case '2':
			displayMenu();
			break;
		case '3':
			if (confirmOperation(exitDialog)) {
				clearScreen();
				exit = true;
			}
			break;
		case ESCAPE_KEY:
			if (confirmOperation(exitDialog)) {
				clearScreen();
				exit = true;
			}
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::dispatchPerson(Person* person) {
	if (person != NULL) {
		switch (person->getType()) {
		case 1:
			readerMenu(person);
			break;
		case 2:
			employeeMenu(person);
			break;
		case 3:
			supervisorMenu(person);
			break;
		default:
			break;
		}
	}
}

void Interface::readerMenu(Person*reader) {
	char input;
	bool exit = false;
	string header = "Reader   " + reader->getName();

	do {
		clearScreen();
		displayHeader(header);

		cout << TRI_TAB << "Age:" << TAB << reader->getAge() << endl;
		cout << TRI_TAB << "Card:" << TAB << reader->getCard() << endl;
		cout << TRI_TAB << "Phone:" << TAB << reader->getPhone() << endl;
		cout << TRI_TAB << "Email:" << TAB << reader->getEmail() << endl;
		cout << endl << TRI_TAB << "[1] Borrowed books\n";
		cout << TRI_TAB << "[2] Return a book\n";
		cout << TRI_TAB << "[3] History\n";
		cout << TRI_TAB << "[4] Logout\n\n" << DOUBLE_TAB << TAB
				<< PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			clearScreen();
			genericDisplay(reader->getBorrowedBooks(), "Borrowed books", "a");
			break;
		case '2':
			break;
		case '3':
			break;
		case '4':
			clearScreen();
			exit = true;
			break;
		case ESCAPE_KEY:
			clearScreen();
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::employeeMenu(Person* employee) {
	char input;
	bool exit = false;
	string header = "Employee   " + employee->getName();

	do {
		clearScreen();
		displayHeader(header);
		cout << TRI_TAB << "Age:" << TAB << employee->getAge() << endl;
		cout << TRI_TAB << "Nif:" << TAB << employee->getNif() << endl;
		cout << TRI_TAB << "Phone:" << TAB << employee->getPhone() << endl;
		cout << TRI_TAB << "Email:" << TAB << employee->getEmail() << endl;
		cout << TRI_TAB << "Wage:" << TAB << employee->getWage() << " euros"
				<< endl;
		cout << endl << TRI_TAB << "[1] Borrow a book\n";
		cout << TRI_TAB << "[2] Manage readers\n";
		cout << TRI_TAB << "[3] Manage books\n";
		cout << TRI_TAB << "[4] Logout\n\n" << DOUBLE_TAB << TAB
				<< PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			clearScreen();
			break;
		case '2':
			break;
		case '3':
			manageBooks();
			break;
		case '4':
			clearScreen();
			exit = true;
			break;
		case ESCAPE_KEY:
			clearScreen();
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::supervisorMenu(Person* supervisor) {
	char input;
	bool exit = false;
	string header = "Supervisor   " + supervisor->getName();

	do {
		clearScreen();
		displayHeader(header);
		cout << TRI_TAB << "Age:" << TAB << supervisor->getAge() << endl;
		cout << TRI_TAB << "Nif:" << TAB << supervisor->getNif() << endl;
		cout << TRI_TAB << "Phone:" << TAB << supervisor->getPhone() << endl;
		cout << TRI_TAB << "Email:" << TAB << supervisor->getEmail() << endl;
		cout << TRI_TAB << "Wage:" << TAB << supervisor->getWage() << " euros"
				<< endl;
		cout << endl << TRI_TAB << "[1] Display employees team\n";
		cout << TRI_TAB << "[2] Manage employees\n";
		cout << TRI_TAB << "[3] Logout\n\n" << DOUBLE_TAB << TAB
				<< PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			clearScreen();
			break;
		case '2':
			manageEmployees(supervisor);
			break;
		case '3':
			clearScreen();
			exit = true;
			break;
		case ESCAPE_KEY:
			clearScreen();
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::manageBooks() {
	char input;
	bool exit = false;
	string header = "Manage books", message;
	Book* book;

	do {
		clearScreen();
		displayHeader(header);
		cout << endl << TETRA_TAB << "[1] Create book\n";
		cout << TETRA_TAB << "[2] Edit book\n";
		cout << TETRA_TAB << "[3] Remove book\n";
		cout << TETRA_TAB << "[4] Exit\n\n";
		if (message.size() > 0) {
			cout << TRI_TAB << message << endl << endl;
			message.clear();
		}
		cout << TRI_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			clearScreen();
			createBook();
			break;
		case '2':
			clearScreen();
			book = searchBook(library.getBooks());
			if (book != NULL) {
				editBook(book);
			} else
				message = "Error editing a book";
			break;
		case '3':
			if (library.removeBook(searchBook(library.getBooks())))
				message = "Book removed successfully";
			else
				message = "Error removing a book";
			break;
		case '4':
			clearScreen();
			exit = true;
			break;
		case ESCAPE_KEY:
			clearScreen();
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::manageEmployees(Person* supervisor) {
	char input;
	bool exit = false;
	string header = "Manage employees";
	string message;

	do {
		clearScreen();
		displayHeader(header);
		cout << endl << TRI_TAB << "[1] Create employee\n";
		cout << TRI_TAB << "[2] Edit employee\n";
		cout << TRI_TAB << "[3] Remove employee\n";
		cout << TRI_TAB << "[4] Exit\n\n";
		if (message.size() > 0) {
			cout << TRI_TAB << message << endl << endl;
			message.clear();
		}
		cout << TRI_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			clearScreen();
			createEmployee();
			break;
		case '2':
			editEmployee(searchPerson(library.getEmployees()));

			break;
		case '3':
			clearScreen();
			if (library.removePerson((searchPerson(library.getEmployees())),
					supervisor))
				message = "Employee removed successfully";
			else
				message = "Error removing an employee";
			break;
		case '4':
			clearScreen();
			exit = true;
			break;
		case ESCAPE_KEY:
			clearScreen();
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::createBook() {
	string header = "Create Book";
	string newAuthor, newPageNumberStr, newQuota, newIsbn, newTitle;
	stringstream ss;
	unsigned int newPageNumber;

	clearScreen();
	displayHeader(header);

	vector<string> authors = editAuthors();
	while (newQuota.size() == 0) {
		cout << TETRA_TAB << "Quota: ";
		getline(cin, newQuota, '\n');
	}
	while (newPageNumberStr.size() == 0 || !is_All_Number(newPageNumberStr)) {
		cout << TETRA_TAB << "PageNumber: ";
		getline(cin, newPageNumberStr, '\n');
	}
	while (newIsbn.size() == 0 || (newIsbn.size() != 13 && newIsbn.size() != 10)) {
		cout << TETRA_TAB << "Isbn: ";
		getline(cin, newIsbn, '\n');
	}
	while (newTitle.size() == 0) {
		cout << TETRA_TAB << "Title: ";
		getline(cin, newTitle, '\n');

	}
	cout << endl << TETRA_TAB << "Press S to save" << PROMPT_SYMBOL;
	char ch = cin.get();
	if (ch == 's' || ch == 'S') {
		ss << newPageNumberStr;
		ss >> newPageNumber;
		vector<Book*> books = library.getBooks();
		Book *b = new Book(authors, false, newQuota, newPageNumber, newIsbn,
				newTitle);
		library.addBook(b);
		cout << endl << TRI_TAB << newTitle << " successfully created.";
	} else
		cout << "Book creation cancelled\n";
	getKey();
}

void Interface::createEmployee() {
	string header = "Create Employee";
	string newName, newAgeStr, newPhoneStr, newEmail, newNifStr, newWageStr;
	string supervisorDialog = "\t\t\t\tSupervisor?";
	stringstream ss;
	unsigned int newAge, newPhone, newNif, newWage;
	bool supervisor = false;

	clearScreen();
	displayHeader(header);

	while (newName.size() == 0 || !is_All_ASCII_Letter(newName)) {
		cout << TETRA_TAB << "Name: ";
		getline(cin, newName, '\n');
	}
	while (newAgeStr.size() == 0 || !is_All_Number(newAgeStr)
			|| newAgeStr.size() > 2) {
		cout << TETRA_TAB << "Age: ";
		getline(cin, newAgeStr, '\n');
	}
	while (newPhoneStr.size() == 0 || !is_All_Number(newPhoneStr)
			|| newPhoneStr.size() < 6 || newPhoneStr.size() > 12) {
		cout << TETRA_TAB << "Phone: ";
		getline(cin, newPhoneStr, '\n');
	}
	while (newEmail.size() == 0 || newEmail.size() < 10) {
		cout << TETRA_TAB << "Mail: ";
		getline(cin, newEmail, '\n');
	}
	while (newNifStr.size() == 0 || !is_All_Number(newNifStr)
			|| newNifStr.size() != 9) {
		cout << TETRA_TAB << "NIF: ";
		getline(cin, newNifStr, '\n');
	}
	while (newWageStr.size() == 0 || !is_All_Number(newWageStr)) {
		cout << TETRA_TAB << "Wage: ";
		getline(cin, newWageStr, '\n');
	}

	if (confirmOperation(supervisorDialog))
		supervisor = true;

	cout << endl << TETRA_TAB << "Press S to save" << PROMPT_SYMBOL;
	char ch = cin.get();
	if (ch == 's' || ch == 'S') {
		ss << newAgeStr;
		ss >> newAge;
		ss.clear();
		ss << newPhoneStr;
		ss >> newPhone;
		ss.clear();
		ss << newNifStr;
		ss >> newNif;
		ss.clear();
		ss << newWageStr;
		ss >> newWage;
		ss.clear();

		vector<Person*> empl = library.getEmployees();
		Employee *s0 = new Employee(newName, newAge, newPhone, newEmail, newNif,
				newWage, supervisor);
		library.addPerson(s0);
		cout << endl << TRI_TAB << newName << " successfully created.";
	} else
		cout << "Employee creation cancelled\n";
	getKey();
}

void Interface::createReader() {

}

void Interface::editBook(Book* book) {
	char input;
	bool exit = false;
	string header = "Edit book";
	do {
		string newQuota, newTitle, newIsbn, newPageNumberStr, changesMessage;
		unsigned int newPageNumber;
		stringstream ss;
		istringstream s;

		clearScreen();
		displayHeader(header);
		cout << endl << TRI_TAB << "[1] Author" << TAB
				<< optParam(book->getAuthors()[0]) << endl;
		cout << TRI_TAB << "[2] Quota" << TAB << optParam(book->getQuota())
				<< endl;
		cout << TRI_TAB << "[3] Page number" << TAB <<
		optParam(book->getPageNumber()) << endl;
		cout << TRI_TAB << "[4] Isbn" << TAB << optParam(book->getIsbn())
				<< endl;
		cout << TRI_TAB << "[5] Title" << TAB
				<< (book->getTitle().size() > 16 ?
						optParam(book->getTitle().substr(0, 16)) :
						optParam(book->getTitle())) << endl; //
		cout << TRI_TAB << "[6] Exit" << endl;

		if (changesMessage.size() > 0) {
			cout << endl << TRI_TAB << changesMessage << endl;
			changesMessage.clear();
		}
		cout << endl << TRI_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {

		case '1':
			cout << endl;
			book->setAuthors(editAuthors());
			changesMessage = "Changes saved successfully";
			break;

		case '2':
			cout << endl;
			while (newQuota.size() == 0) {
				cout << TETRA_TAB << "Quota: ";
				getline(cin, newQuota, '\n');
			}
			book->setQuota(newQuota);
			changesMessage = "Changes saved successfully";
			break;

		case '3':
			cout << endl;
			while (newPageNumberStr.size() == 0
					|| !is_All_Number(newPageNumberStr)) {
				cout << TETRA_TAB << "Page number: ";
				getline(cin, newPageNumberStr, '\n');
			}
			ss << newPageNumberStr;
			ss >> newPageNumber;
			book->setPageNumber(newPageNumber);
			changesMessage = "Changes saved successfully";
			break;

		case '4':
			cout << endl;
			while (newIsbn.size() == 0
					|| (newIsbn.size() != 13 && newIsbn.size() != 10)) {
				cout << TETRA_TAB << "Isbn: ";
				getline(cin, newIsbn, '\n');
			}
			book->setIsbn(newIsbn);
			changesMessage = "Changes saved successfully";
			break;

		case '5':
			cout << endl;
			while (newTitle.size() == 0) {
				cout << TETRA_TAB << "Title: ";
				getline(cin, newTitle, '\n');
			}
			book->setTitle(newTitle);
			changesMessage = "Changes saved successfully";
			break;
		case '6':
			clearScreen();
			exit = true;
			break;
		case ESCAPE_KEY:
			clearScreen();
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::editEmployee(Person* employee) {
	char input;
	bool exit = false;
	string header = "Edit Employee";
	do {
		string newName, newAgeStr, newPhoneStr, newEmail, newNifStr, newWageStr,
				changesMessage;
		unsigned int newAge, newPhone, newNif, newWage;
		bool supervisor = false;
		char ch;
		stringstream ss;
		istringstream s;

		clearScreen();
		displayHeader(header);
		cout << endl << TRI_TAB << "[1] Name" << TAB << "["
				<< employee->getName().substr(0, 15) << "]" << endl;
		cout << TRI_TAB << "[2] Age" << TAB << "[" << employee->getAge() << "]";
		cout << endl;
		cout << TRI_TAB << "[3] Phone" << TAB << "[" << employee->getPhone()
				<< "]" << endl;
		cout << TRI_TAB << "[4] Email" << TAB << "[" << employee->getEmail()
				<< "]" << endl;
		cout << TRI_TAB << "[5] NIF" << TAB << "[" << employee->getNif() << "]"
				<< endl;
		cout << TRI_TAB << "[6] Wage" << TAB << "[" << employee->getWage()
				<< "]";
		cout << endl;
		cout << TRI_TAB << "[7] Promotions/Demotions" << TAB << "["
				<< employee->printType() << "]";
		cout << endl;
		cout << TRI_TAB << "[8] Exit" << endl;

		if (changesMessage != "") {
			cout << endl << TRI_TAB << changesMessage << endl;
			changesMessage.clear();
		}
		cout << TRI_TAB << endl << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {

		case '1':
			cout << endl;
			while (newName.size() == 0 || !is_All_ASCII_Letter(newName)) {
				cout << TETRA_TAB << "Name: ";
				getline(cin, newName, '\n');
			}
			employee->setName(newName);
			changesMessage = "Changes saved successfully";
			break;

		case '2':
			cout << endl;
			while (newAgeStr.size() == 0 || !is_All_Number(newAgeStr)
					|| newAgeStr.size() > 2) {
				cout << TETRA_TAB << "Age: ";
				getline(cin, newAgeStr, '\n');
			}
			ss << newAgeStr;
			ss >> newAge;
			employee->setAge(newAge);
			changesMessage = "Changes saved successfully";
			break;

		case '3':
			cout << endl;
			while (newPhoneStr.size() == 0 || !is_All_Number(newPhoneStr)
					|| newPhoneStr.size() < 6 || newPhoneStr.size() > 12) {
				cout << TETRA_TAB << "Phone: ";
				getline(cin, newPhoneStr, '\n');
			}
			ss << newPhoneStr;
			ss >> newPhone;
			employee->setPhone(newPhone);
			changesMessage = "Changes saved successfully";
			break;

		case '4':
			cout << endl;
			while (newEmail.size() == 0 || newEmail.size() < 10) {
				cout << TETRA_TAB << "Mail: ";
				getline(cin, newEmail, '\n');
			}
			employee->setEmail(newEmail);
			changesMessage = "Changes saved successfully";
			break;

		case '5':
			cout << endl;
			while (newNifStr.size() == 0 || !is_All_Number(newNifStr)
					|| newNifStr.size() != 9) {
				cout << TETRA_TAB << "NIF: ";
				getline(cin, newNifStr, '\n');
			}
			ss << newNifStr;
			ss >> newNif;
			employee->setNif(newNif);
			changesMessage = "Changes saved successfully";
			break;
		case '6':
			cout << endl;
			while (newWageStr.size() == 0 || !is_All_Number(newWageStr)) {
				cout << TETRA_TAB << "Wage: ";
				getline(cin, newWageStr, '\n');
			}
			ss << newWageStr;
			ss >> newWage;
			employee->setWage(newWage);
			changesMessage = "Changes saved successfully";
			break;
		case '7':
			cout << endl << TETRA_TAB
					<< "Press S to set as superviser or E as employee"
					<< PROMPT_SYMBOL;
			ch = cin.get();
			if (ch == 's' || ch == 'S') {
				supervisor = 1;
			} else if (ch == 'e' || ch == 'E') {
				supervisor = 0;
			}
			employee->setSupervisor(supervisor);
			changesMessage = "Changes saved successfully";
			break;
		case '8':
			clearScreen();
			exit = true;
			break;
		case ESCAPE_KEY:
			clearScreen();
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);

}
Person* Interface::searchPerson(vector<Person*> persons) {
	string query;
	string header = "Login";
	bool exit = false;
	int key;
	vector<Person*> matches;
	do {
		clearScreen();
		displayHeader(header);
		cout << endl;
		matches.clear();
		matches.reserve(6);
		if (query.size() > 0) {
			for (size_t i = 0, z = 1; i < persons.size() && z < 6; i++) {
				string name = persons[i]->getName();
				if (matchQuery(query, name)) {
					cout << TRI_TAB << "[" << z++ << "] "
							<< persons[i]->getName() << TAB
							<< persons[i]->printType() << endl << endl;
					matches.push_back(persons[i]);
				}
			}
		}

		cout << endl << DOUBLE_TAB << TAB
				<< "Enter person name [ESC to exit]\n\n" << DOUBLE_TAB << TAB
				<< PROMPT_SYMBOL << query;

		key = getKey();

		switch (key) {
		case BACSKPACE_KEY:
			if (query.length() > 0)
				query.erase(query.end() - 1);
			break;
		case '1':
			if (matches.size() > 0) {
				exit = true;
				return matches[0];
			}
			break;
		case '2':
			if (matches.size() > 1) {
				exit = true;
				return matches[1];
			}
			break;
		case '3':
			if (matches.size() > 2) {
				exit = true;
				return matches[2];
			}
			break;

		case '4':
			if (matches.size() > 3) {
				exit = true;
				return matches[3];
			}
			break;

		case '5':
			if (matches.size() > 4) {
				exit = true;
				return matches[4];
			}
			break;
		case RETURN_KEY:
			if (matches.size() > 0) {
				exit = true;
				return matches[0];
			}
			break;
		case ESCAPE_KEY:
			exit = true;
			break;
		case DELETE_KEY:
			query.clear();
			break;
		default:
			query += char(key);
			break;
		}
	} while (!exit);
	return NULL;
}

Book* Interface::searchBook(vector<Book*> books) {
	string query;
	string header = "Search books";
	bool exit = false;
	int key;
	vector<Book*> matches;
	do {
		clearScreen();
		displayHeader(header);
		cout << endl;
		matches.clear();
		matches.reserve(6);
		if (query.size() > 0) {
			for (size_t i = 0, z = 1; i < books.size() && z < 6; i++) {
				string title = books[i]->getTitle();
				vector<string> authors = books[i]->getAuthors();
				bool matchAuthor = false;
				for (size_t y = 0; y < authors.size(); y++)
					matchAuthor |= partialMatchQuery(query, authors[y]);

				if (partialMatchQuery(query, title) || matchAuthor) {
					cout << DOUBLE_TAB << "[" << z++ << "] "
							<< ((books[i]->getTitle()).size() > 32 ?
									books[i]->getTitle().substr(0, 32) :
									books[i]->getTitle()) << TAB
							<< (books[i]->getBorrowed() == 1 ?
									"[Borrowed]" : "[Available]") << endl
							<< endl;
					matches.push_back(books[i]);
				}
			}
		}
		cout << endl << DOUBLE_TAB << TAB
				<< "Enter book title [ESC to exit]\n\n" << DOUBLE_TAB << TAB
				<< PROMPT_SYMBOL << query;

		key = getKey();

		switch (key) {
		case BACSKPACE_KEY:
			if (query.length() > 0)
				query.erase(query.end() - 1);
			break;
		case '1':
			if (matches.size() > 0) {
				exit = true;
				return matches[0];
			}
			break;
		case '2':
			if (matches.size() > 1) {
				exit = true;
				return matches[1];
			}
			break;
		case '3':
			if (matches.size() > 2) {
				exit = true;
				return matches[2];
			}
			break;

		case '4':
			if (matches.size() > 3) {
				exit = true;
				return matches[3];
			}
			break;

		case '5':
			if (matches.size() > 4) {
				exit = true;
				return matches[4];
			}
			break;
		case RETURN_KEY:
			if (matches.size() > 0) {
				exit = true;
				return matches[0];
			}
			break;
		case ESCAPE_KEY:
			exit = true;
			break;
		case DELETE_KEY:
			query.clear();
			break;
		default:
			query += char(key);
			break;
		}
	} while (!exit);
	return NULL;
}

void Interface::displayMenu() {
	char input;
	bool exit = false;
	string header = "Display";

	do {
		clearScreen();
		displayHeader(header);
		cout << endl << TETRA_TAB << "[1] Persons\n\n";
		cout << TETRA_TAB << "[2] Readers\n\n";
		cout << TETRA_TAB << "[3] Employees\n\n";
		cout << TETRA_TAB << "[4] Supervisors\n\n";
		cout << TETRA_TAB << "[5] Books\n\n";
		cout << TETRA_TAB << "[6] Exit to menu\n\n\n" << TRI_TAB
				<< PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			clearScreen();
			genericDisplay(library.getPersons(), "Persons",
					"\tName\t\tAge\tPhone\t\tEmail\t\t\t[Id]");
			break;
		case '2':
			clearScreen();
			genericDisplay(library.getReaders(), "Readers",
					"\tName\t\tAge\tPhone\t\tEmail\t\t\tCard");
			break;
		case '3':
			clearScreen();
			genericDisplay(library.getEmployees(), "Employees",
					"\tName\t\tAge\tPhone\t\tEmail\t\t\tNif");
			break;
		case '4':
			clearScreen();
			genericDisplay(library.getSupervisors(), "Supervisors",
					"\tName\t\tAge\tPhone\t\tEmail\t\t\tNif");
			break;
		case '5':
			clearScreen();
			genericDisplay(library.getBooks(), "Books",
					"\tAuthors\t\tBorrowed\tQuota\tPageNumber\tISBN\tTitle");
			break;
		case '6':
			exit = true;
			break;
		case ESCAPE_KEY:
			clearScreen();
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::clearScreen() {
	system(CLEAR);
}

void Interface::displayHeader(string& header) {
	unsigned int size = header.size();
	unsigned int dynSizeLeft = ceil((31 - size) / 2);
	unsigned int dynSizeRight = dynSizeLeft;

	if (dynSizeLeft + dynSizeRight + size < 31)
		dynSizeRight++;

	cout << TRI_TAB << string(33, '#') << endl;
	cout << TRI_TAB << "#" << TETRA_TAB << "#" << endl;
	cout << TRI_TAB << "#" << string(dynSizeLeft, ' ') << header
			<< string(dynSizeRight, ' ') << "#" << endl;
	cout << TRI_TAB << "#" << TETRA_TAB << "#" << endl;
	cout << TRI_TAB << string(33, '#') << endl << endl;
}

bool Interface::confirmOperation(string& query) {
	cout << query << " [y] to confirm";
	char answer = getKey();

	if (answer == 'y' || answer == 'Y')
		return true;
	else
		return false;
}

template<typename T>
void Interface::genericDisplay(vector<T> vec, string listName, string labels) {
	unsigned int vecSize = vec.size(), pCount = 1, vLimit = 0, i = 0, progress;
	float pLimit = ceil(static_cast<float>(vecSize) / MAX_LINES);
	bool done = false;
	string vLimitMsg = " [ESC] to interrupt or any other key to continue...";
	char ch;

	while (i < vecSize && !done) {
		vLimit = 0;
		progress = ceil((19.0 / pLimit) * pCount);
		clearScreen();
		displayHeader(listName);
		cout << TRI_TAB << "Page " << pCount << " of " << pLimit << " ["
				<< string(progress, '#') << string((19 - progress), ' ') << "]"
				<< endl;
		cout << " " << string(77, '-') << " " << endl;
		cout << " " << labels << endl;
		cout << " " << string(77, '-') << " " << endl;

		while (vLimit < MAX_LINES && i < vecSize && !done) {
			cout << " " << vec[i]->print();
			cout << endl;
			i++;
			vLimit++;

			if (vLimit == MAX_LINES && i < vecSize) {
				pCount++;
				cout << " " << string(78, '-') << " " << vLimitMsg;
				ch = getKey();
				if (ch == ESCAPE_KEY)
					done = true;
			}
		}
	}
	if (i == vecSize) {
		cout << " " << string(78, '-') << " ";
		cout << " Press any key to continue...";
		getchar();
	}
}

char Interface::getKey() {
#ifdef _WIN32
	return getch();
#elif _WIN64
	return getch();
#else
//char buf[32] = { 0 };
//fgets(buf, sizeof(buf), stdin);
//return buf[0];

	static struct termios oldt, newt;

	/*tcgetattr gets the parameters of the current terminal
	 STDIN_FILENO will tell tcgetattr that it should write the settings
	 of stdin to oldt*/
	tcgetattr( STDIN_FILENO, &oldt);
	/*now the settings will be copied*/
	newt = oldt;

	/*ICANON normally takes care that one line at a time will be processed
	 that means it will return if it sees a "\n" or an EOF or an EOL*/
	newt.c_lflag &= ~(ICANON); //| ECHO);

	/*Those new settings will be set to STDIN
	 TCSANOW tells tcsetattr to change attributes immediately. */
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);

	/*This is your part:
	 I choose 'e' to end input. Notice that EOF is also turned off
	 in the non-canonical mode*/
	char key = getchar();

	/*restore the old settings*/
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	return key;
#endif
}

vector<string> Interface::editAuthors() {
	vector<string> authors;
	string newAuthor, authorsDialog = "\t\t\tAdd another author?";
	for (int i = 1; authors.size() == 0 || authors.size() < 8; i++) {
		while (newAuthor.size() == 0 || !is_All_ASCII_Letter(newAuthor)) {
			cout << TETRA_TAB << "Author " << i << ": ";
			getline(cin, newAuthor, '\n');
		}
		authors.push_back(newAuthor);
		newAuthor.clear();
		if (!confirmOperation(authorsDialog)) {
			cout << endl;
			break;
		}
		cout << endl;
	}
	return authors;
}

template<typename T>
string Interface::optParam(const T &p) {
	stringstream ss;
	ss << "[" << p << "]";
	return ss.str();
}
