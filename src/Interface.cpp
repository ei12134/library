#include "Interface.h"

Interface::Interface() {
#if defined(_WIN32) || defined (_WIN64)
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitleA("Library");
#endif
	setColor(FGGREEN_BGBLACK);
	menu();
}

Interface::~Interface() {
#if defined(_WIN32) || defined(_WIN64)
	setColor(FGGRAY_BGBLACK);
#else
	cout << "\033[0m";
#endif
	clearScreen();
}

void Interface::menu() {
	char input;
	bool exit = false;
	bool tab = false;
	vector<string> menuStr;
	menuStr.push_back("Login");
	menuStr.push_back("Display");
	menuStr.push_back("Quit");
	string spacing = string((80 - menuStr[1].size()) / 2, ' ');
	string exitDialog = "Quit?";
	string noSupervisors = "Create supervisor?\n\t\t\t      ";
	string header = "Library";
	string query;
	size_t selected = 0;

	do {
		clearScreen();
		displayHeader(header);

		if (query.size() > 0)
			for (size_t i = 0; i < menuStr.size(); i++)
				if (matchQuery(query, menuStr[i])) {
					if (tab) {
						query = menuStr[i];
						selected = i;
					}
				}
		tab = false;

		for (size_t i = 0; i < menuStr.size(); i++)
			colorMsg(spacing, menuStr[i],
					(selected == i ? FGBLACK_BGGREEN : FGGREEN_BGBLACK), 2);
		cout << THREE_TABS << HALF_TAB << PROMPT_SYMBOL;
		if (exit)
			if (confirmOperation(exitDialog))
				break;
			else {
				input = 0;
				exit = false;
			}
		else {
			cout << query;
			input = getKey();
		}

		switch (input) {
		case 0:
			break;

		case RETURN_KEY:
			switch (selected) {
			case 0:
				query.clear();
				library.sortByName();
				if (library.getSupervisors().size() != 0)
					dispatchPerson(searchPerson(library.getPersons()));
				else if (confirmOperation(noSupervisors))
					createEmployee();
				break;
			case 1:
				query.clear();
				displayMenu();
				break;
			case 2:
				exit = true;
				break;
			default:
				break;
			}
			break;

		case TAB_KEY:
			tab = true;
			break;
		case BACKSPACE_KEY:
			if (query.length() > 0)
				query.erase(query.end() - 1);
			break;
		case DELETE_KEY:
			query.clear();
			break;
		case ARROW_DOWN:
			selected++;
			selected %= menuStr.size();
			break;
		case ARROW_UP:
			if (selected == 0)
				selected = menuStr.size() - 1;
			else
				selected--;
			break;
		case ESCAPE_KEY:
			exit = true;
			break;
		default:
			query += (char) input;
			break;
		}
	} while (1);
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

void Interface::displayMenu() {
	char input;
	bool exit = false;
	string header = "Display";
	vector<Person*> persons;

	string persStr[] = { "type", "name", "age" };
	LibraryGetFn persGetFunc = &Library::getPersons;
	LibraryMemFn persFuncs[] = { &Library::sortByType, &Library::sortByName,
			&Library::sortByAge };

	string readerStr[] = { "name", "age", "borrows" };
	LibraryGetFn rdrGetFunc = &Library::getReaders;
	LibraryMemFn readerFuncs[] = { &Library::sortByName, &Library::sortByAge,
			&Library::sortByBorrow };

	string emplStr[] = { "name", "age" };
	LibraryGetFn emplGetFunc = &Library::getEmployees;
	LibraryMemFn emplFuncs[] = { &Library::sortByName, &Library::sortByAge };

	string supStr[] = { "name", "age" };
	LibraryGetFn supGetFunc = &Library::getSupervisors;
	LibraryMemFn supFuncs[] = { &Library::sortByName, &Library::sortByAge };

	string booksStr[] = { "title", "ISBN" };
	LibraryGetBkFn booksGetFunc = &Library::getBooks;
	LibraryMemFn booksFuncs[] = { &Library::sortByTitle, &Library::sortByISBN };

	do {
		clearScreen();
		displayHeader(header);
		cout << FOUR_TABS << "[1] Persons" << endl;
		cout << FOUR_TABS << "[2] Readers" << endl;
		cout << FOUR_TABS << "[3] Employees" << endl;
		cout << FOUR_TABS << "[4] Supervisors" << endl;
		cout << FOUR_TABS << "[5] Books" << endl << endl;
		cout << FOUR_TABS << "[6] Exit to menu" << endl << endl;
		cout << THREE_TABS << HALF_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			personsDisplayPtr(persGetFunc, "Persons",
					"\tName\t\tAge\tPhone\t\tEmail\t\t\t[Id]", persStr,
					persFuncs, 3);
			break;
		case '2':
			personsDisplayPtr(rdrGetFunc, "Readers",
					"\tName\t\tAge\tPhone\t\tEmail\t\t\tCard", readerStr,
					readerFuncs, 3);
			break;
		case '3':
			personsDisplayPtr(emplGetFunc, "Employees",
					"\tName\t\tAge\tPhone\t\tEmail\t\t\tNif", emplStr,
					emplFuncs, 2);
			break;
		case '4':
			personsDisplayPtr(supGetFunc, "Supervisors",
					"\tName\t\tAge\tPhone\t\tEmail\t\t\tNif", supStr, supFuncs,
					2);
			break;
		case '5':
			booksDisplayPtr(booksGetFunc, "Books",
					"\tTitle\t\t\tAuthors\t\tISBN\t\tStatus", booksStr,
					booksFuncs, 2);
			break;
		case '6':
			exit = true;
			break;
		case ESCAPE_KEY:
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::readerMenu(Person *reader) {
	char input;
	bool exit = false;
	string header;
	string infMsg;

	do {
		header = "Reader   " + reader->getName();
		clearScreen();
		displayHeader(header);
		setColor(FGWHITE_BGBLACK);
		cout << THREE_TABS << HALF_TAB << "Age: " << reader->getAge() << endl;
		cout << THREE_TABS << HALF_TAB << "Card: " << reader->getCard() << endl;
		cout << THREE_TABS << HALF_TAB << "Phone: " << reader->getPhone()
				<< endl;
		cout << THREE_TABS << HALF_TAB << "Email: " << reader->getEmail()
				<< endl;
		resetColor();
		cout << endl << THREE_TABS << HALF_TAB << "[1] Display borrows" << endl;
		cout << THREE_TABS << HALF_TAB << "[2] Borrow history" << endl << endl;
		cout << THREE_TABS << HALF_TAB << "[3] Logout" << endl << endl;

		vector<Borrow*> borrowedBooks = reader->getBorrowedBooks();
		for (size_t i = 0; i < borrowedBooks.size(); i++)
			if (borrowedBooks[i]->calcFee() > 0)
				infMsg = "A book has the borrow date expired";
		if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}
		cout << THREE_TABS << HALF_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			editBorrow(reader);
			break;
		case '2':
			genericDisplay(library.getBorrowedBooksFromReader(reader),
					"Borrow history", "\tTitle\t\t\t\tBorrowed\tReturned\tID");
			break;
		case '3':
			exit = true;
			break;
		case ESCAPE_KEY:
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
	string header;

	do {
		header = "Employee   " + employee->getName();
		clearScreen();
		displayHeader(header);
		setColor(FGWHITE_BGBLACK);
		cout << THREE_TABS << HALF_TAB << "Age: " << employee->getAge() << endl;
		cout << THREE_TABS << HALF_TAB << "Nif: " << employee->getNif() << endl;
		cout << THREE_TABS << HALF_TAB << "Phone: " << employee->getPhone()
				<< endl;
		cout << THREE_TABS << HALF_TAB << "Email: " << employee->getEmail()
				<< endl;
		cout << THREE_TABS << HALF_TAB << "Wage: " << employee->getWage()
				<< " EUR" << endl;
		resetColor();
		cout << endl << THREE_TABS << HALF_TAB << "[1] Borrow a book" << endl;
		cout << THREE_TABS << HALF_TAB << "[2] Manage readers" << endl;
		cout << THREE_TABS << HALF_TAB << "[3] Manage books" << endl << endl;
		cout << THREE_TABS << HALF_TAB << "[4] Logout" << endl << endl
				<< THREE_TABS << HALF_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			createBorrow(employee);
			break;
		case '2':
			manageReaders();
			break;
		case '3':
			manageBooks();
			break;
		case '4':
			exit = true;
			break;
		case ESCAPE_KEY:
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
	string header;

	do {
		if (supervisor->getType() != 3) {
			employeeMenu(supervisor);
			break;
		}

		header = "Supervisor   " + supervisor->getName();
		clearScreen();
		displayHeader(header);
		setColor(FGWHITE_BGBLACK);
		cout << THREE_TABS << HALF_TAB << "Age: " << supervisor->getAge()
				<< " years" << endl;
		cout << THREE_TABS << HALF_TAB << "Nif: " << supervisor->getNif()
				<< endl;
		cout << THREE_TABS << HALF_TAB << "Phone: " << supervisor->getPhone()
				<< endl;
		cout << THREE_TABS << HALF_TAB << "Email: " << supervisor->getEmail()
				<< endl;
		cout << THREE_TABS << HALF_TAB << "Wage: " << supervisor->getWage()
				<< " EUR" << endl;
		resetColor();
		cout << endl << THREE_TABS + HALF_TAB << "[1] Borrow a book" << endl;
		cout << THREE_TABS << HALF_TAB << "[2] Manage books" << endl;
		cout << THREE_TABS << HALF_TAB << "[3] Manage readers" << endl;
		cout << THREE_TABS << HALF_TAB << "[4] Manage employees" << endl;
		cout << THREE_TABS << HALF_TAB << "[5] Auto-assign teams" << endl;
		cout << THREE_TABS << HALF_TAB << "[6] Employees team" << endl << endl;
		cout << THREE_TABS << HALF_TAB << "[7] Logout" << endl << endl
				<< THREE_TABS << HALF_TAB << PROMPT_SYMBOL;
		input = getKey();
		switch (input) {
		case '1':
			createBorrow(supervisor);
			break;
		case '2':
			manageBooks();
			break;
		case '3':
			manageReaders();
			break;
		case '4':
			manageEmployees(supervisor);
			break;
		case '5':
			library.SupervisorEmployeeRandom();
			library.savePersons();
			cout << "Employees were evenly assigned";
			getKey();
			break;
		case '6':
			genericDisplay(supervisor->getEmployeeTeam(), "Employees team",
					"\tName\t\tAge\tPhone\t\tEmail\t\t\tNif");
			break;
		case '7':

			exit = true;
			break;
		case ESCAPE_KEY:
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
	string header = "Manage books", errMsg, infMsg;
	string confirmRemove = "Remove book?";
	Book* book;

	do {
		clearScreen();
		displayHeader(header);
		cout << FOUR_TABS << "[1] Create book\n";
		cout << FOUR_TABS << "[2] Edit book\n";
		cout << FOUR_TABS << "[3] Remove book\n";
		cout << FOUR_TABS << "[4] Exit\n\n";

		if (errMsg.size() > 0) {
			errorMsg(errMsg);
			cout << endl << endl;
			errMsg.clear();
		} else if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}
		cout << THREE_TABS << HALF_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			createBook();
			break;
		case '2':
			book = searchBook(library.getBooks());
			if (book != NULL) {
				editBook(book);
			} else
				errMsg = "Error editing a book";
			break;
		case '3':
			book = searchBook(library.getBooks());
			if (book != NULL && !book->getBorrowed()
					&& confirmOperation(confirmRemove)) {
				if (library.removeBook(book)) {
					infMsg = "Book removed successfully";
					library.saveBooks();
				} else
					errMsg = "Error removing a book";
			} else
				errMsg = "Error removing a book";
			break;
		case '4':
			exit = true;
			break;
		case ESCAPE_KEY:
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::manageReaders() {
	char input;
	bool exit = false;
	string header = "Manage readers";
	string errMsg, infMsg;
	Person* reader;

	do {
		clearScreen();
		displayHeader(header);
		cout << FOUR_TABS << "[1] Create reader\n";
		cout << FOUR_TABS << "[2] Edit reader\n";
		cout << FOUR_TABS << "[3] Remove reader\n";
		cout << FOUR_TABS << "[4] Exit\n\n";
		if (errMsg.size() > 0) {
			errorMsg(errMsg);
			cout << endl << endl;
			errMsg.clear();
		} else if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}
		cout << THREE_TABS << HALF_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':

			createReader();
			break;
		case '2':
			reader = searchPerson(library.getReaders());
			if (reader != NULL)
				editReader(reader);
			else
				errMsg = "Error editing a reader";
			break;
		case '3':

			if (library.removeReader(searchPerson(library.getReaders()))) {
				library.savePersons();
				infMsg = "Reader removed successfully";
			} else
				errMsg = "Error removing a reader";
			break;
		case '4':
			exit = true;
			break;
		case ESCAPE_KEY:
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
	string errMsg, infMsg;
	Person* employee;

	do {
		clearScreen();
		displayHeader(header);
		cout << FOUR_TABS << "[1] Create employee\n";
		cout << FOUR_TABS << "[2] Edit employee\n";
		cout << FOUR_TABS << "[3] Remove employee\n";
		cout << FOUR_TABS << "[4] Exit\n\n";
		if (errMsg.size() > 0) {
			errorMsg(errMsg);
			cout << endl << endl;
			errMsg.clear();
		} else if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}
		cout << THREE_TABS << HALF_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':

			createEmployee();
			break;
		case '2':
			employee = searchPerson(library.getEmployees());
			if (employee != NULL)
				editEmployee(employee);
			else
				errMsg = "Error editing an employee";
			break;
		case '3':

			if (library.removeEmployee((searchPerson(library.getEmployees())),
					supervisor)) {
				library.savePersons();
				infMsg = "Employee removed successfully";
			} else
				errMsg = "Error removing an employee";
			break;
		case '4':
			exit = true;
			break;
		case ESCAPE_KEY:
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::createBook() {
	string header = "Create Book";
	string newAuthor, newPageNumberStr, newQuota, newISBN, newTitle;
	stringstream ss;
	unsigned int newPageNumber;

	clearScreen();
	displayHeader(header);

	vector<string> authors = editAuthors();
	while (newQuota.size() == 0) {
		cout << THREE_TABS << "Quota: ";
		getline(cin, newQuota, '\n');
	}
	while (newPageNumberStr.size() == 0 || !is_All_Number(newPageNumberStr)) {
		cout << THREE_TABS << "PageNumber: ";
		getline(cin, newPageNumberStr, '\n');
	}
	while (newISBN.size() == 0 || (newISBN.size() != 13 && newISBN.size() != 10)) {
		cout << THREE_TABS << "ISBN: ";
		getline(cin, newISBN, '\n');
	}
	while (newTitle.size() == 0) {
		cout << THREE_TABS << "Title: ";
		getline(cin, newTitle, '\n');

	}
	cout << endl << THREE_TABS << "Press S to save" << PROMPT_SYMBOL;
	char ch = cin.get();
	if (ch == 's' || ch == 'S') {
		ss << newPageNumberStr;
		ss >> newPageNumber;
		vector<Book*> books = library.getBooks();
		Book *b = new Book(authors, false, newQuota, newPageNumber, newISBN,
				newTitle);
		library.addBook(b);
		library.saveBooks();
		cout << endl << THREE_TABS << newTitle << " successfully created.";
	} else
		cout << endl << THREE_TABS << "Book creation cancelled";
	getKey();
	cin.ignore();
}

void Interface::createReader() {
	string header = "Create Reader";
	string newName, newAgeStr, newPhoneStr, newEmail;
	stringstream ss;
	unsigned int newAge, newPhone;

	clearScreen();
	displayHeader(header);

	while (newName.size() == 0 || !is_All_ASCII_Letter(newName)) {
		cout << THREE_TABS << "Name: ";
		getline(cin, newName, '\n');
	}
	while (newAgeStr.size() == 0 || !is_All_Number(newAgeStr)
			|| newAgeStr.size() > 3) {
		cout << THREE_TABS << "Age: ";
		getline(cin, newAgeStr, '\n');
	}
	while (newPhoneStr.size() == 0 || !is_All_Number(newPhoneStr)
			|| newPhoneStr.size() < 6 || newPhoneStr.size() > 12) {
		cout << THREE_TABS << "Phone: ";
		getline(cin, newPhoneStr, '\n');
	}
	while (newEmail.size() == 0 || newEmail.size() < 7) {
		cout << THREE_TABS << "Mail: ";
		getline(cin, newEmail, '\n');
	}

	cout << endl << THREE_TABS << "Press S to save" << PROMPT_SYMBOL;
	char ch = cin.get();
	if (ch == 's' || ch == 'S') {
		ss << newAgeStr;
		ss >> newAge;
		ss.clear();
		ss << newPhoneStr;
		ss >> newPhone;
		ss.clear();

		Person *reader = new Reader(newName, newAge, newPhone, newEmail);
		library.addPerson(reader);
		library.savePersons();
		cout << endl << THREE_TABS << newName << " successfully created.";
	} else
		cout << endl << THREE_TABS << "Reader creation cancelled";
	getKey();
	cin.ignore();
}

void Interface::createEmployee() {
	string header = "Create Employee";
	string newName, newAgeStr, newPhoneStr, newEmail, newNifStr, newWageStr;
	string supervisorDialog = "\n\t\t\tSupervisor?";
	stringstream ss;
	unsigned int newAge, newPhone, newNif, newWage;
	bool supervisor = false;

	clearScreen();
	displayHeader(header);

	while (newName.size() == 0 || !is_All_ASCII_Letter(newName)) {
		cout << THREE_TABS << "Name: ";
		getline(cin, newName, '\n');
	}
	while (newAgeStr.size() == 0 || !is_All_Number(newAgeStr)
			|| newAgeStr.size() > 3) {
		cout << THREE_TABS << "Age: ";
		getline(cin, newAgeStr, '\n');
	}
	while (newPhoneStr.size() == 0 || !is_All_Number(newPhoneStr)
			|| newPhoneStr.size() < 6 || newPhoneStr.size() > 12) {
		cout << THREE_TABS << "Phone: ";
		getline(cin, newPhoneStr, '\n');
	}
	while (newEmail.size() == 0 || newEmail.size() < 7) {
		cout << THREE_TABS << "Mail: ";
		getline(cin, newEmail, '\n');
	}
	while (newNifStr.size() == 0 || !is_All_Number(newNifStr)
			|| newNifStr.size() != 9 || seekNIF(newNifStr)) {
		cout << THREE_TABS << "NIF: ";
		getline(cin, newNifStr, '\n');
	}
	while (newWageStr.size() == 0 || !is_All_Number(newWageStr)) {
		cout << THREE_TABS << "Wage: ";
		getline(cin, newWageStr, '\n');
	}

	if (library.getPersons().size() == 0)
		supervisor = true;
	else if (confirmOperation(supervisorDialog))
		supervisor = true;

	cout << endl << THREE_TABS << "Press S to save" << PROMPT_SYMBOL;
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
		library.savePersons();
		cout << endl << THREE_TABS << newName << " successfully created.";
	} else
		cout << endl << THREE_TABS << "Employee creation cancelled";
	getKey();
	cin.ignore();
}

void Interface::createBorrow(Person* employee) {
	char input;
	bool exit = false;
	string header = "Create borrow";
	string errMsg, infMsg;
	Person* reader = NULL;
	Book* book = NULL;

	do {
		clearScreen();
		displayHeader(header);

		if (reader != NULL)
			cout << THREE_TABS << "Reader name: " << reader->getName() << endl;
		if (book != NULL)
			cout << THREE_TABS << "Book title: " << book->getTitle() << endl;

		cout << endl << FOUR_TABS << "[1] Select reader" << endl;
		cout << FOUR_TABS << "[2] Select book" << endl;
		cout << FOUR_TABS << "[3] Create borrow" << endl;
		cout << FOUR_TABS << "[4] Exit" << endl << endl;

		if (errMsg.size() > 0) {
			errorMsg(errMsg);
			cout << endl << endl;
			errMsg.clear();
		} else if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}

		cout << THREE_TABS << "Select book to return [ESC exits]" << endl
				<< endl << THREE_TABS << HALF_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			reader = searchPerson(library.getReaders());
			if (reader == NULL) {
				reader = NULL;
				errMsg = "Select another reader";
			}
			break;
		case '2':
			book = searchBook(library.getAvailableBooks());
			if (book == NULL || book->getBorrowed()) {
				book = NULL;
				errMsg = "Select another book";
			}
			break;
		case '3':
			if (reader != NULL && book != NULL) {
				Borrow* borrow = new Borrow(book, employee, reader);
				if (reader->addBorrow(borrow)) {
					library.addBorrow(borrow);
					book->setBorrowed(true);
					infMsg = "Borrow created successfully";
					library.saveBorrows();
				} else {
					errMsg = "Select another reader";
					delete borrow;
				}
				book = NULL;
			} else
				errMsg = "Select a reader and a book";
			break;
		case '4':

			exit = true;
			break;
		case ESCAPE_KEY:

			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::editBook(Book* book) {
	char input;
	bool exit = false;
	bool edited = false;
	string header = "Edit book";
	Book backup = *book;
	do {
		string newQuota, newTitle, newISBN, newPageNumberStr, changesMessage;
		unsigned int newPageNumber;
		stringstream ss;
		istringstream s;

		clearScreen();
		displayHeader(header);
		cout << endl << THREE_TABS << "[1] Author: " << book->getAuthors()[0]
				<< endl;
		cout << THREE_TABS << "[2] Quota: " << book->getQuota() << endl;
		cout << THREE_TABS << "[3] Page number: " << book->getPageNumber()
				<< endl;
		cout << THREE_TABS << "[4] ISBN: " << book->getISBN() << endl;
		cout << THREE_TABS << "[5] Title: " << book->getTitle().substr(0, 20)
				<< endl << endl;
		cout << THREE_TABS << "[6] Discard changes" << endl;
		cout << THREE_TABS << "[7] Save" << endl;

		if (changesMessage.size() > 0) {
			cout << endl << THREE_TABS << changesMessage << endl;
			changesMessage.clear();
		}
		cout << endl << THREE_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {

		case '1':
			cout << endl;
			book->setAuthors(editAuthors());
			edited = true;
			break;

		case '2':
			cout << endl;
			while (newQuota.size() == 0) {
				cout << THREE_TABS << "Quota: ";
				getline(cin, newQuota, '\n');
			}
			book->setQuota(newQuota);
			edited = true;
			break;

		case '3':
			cout << endl;
			while (newPageNumberStr.size() == 0
					|| !is_All_Number(newPageNumberStr)) {
				cout << THREE_TABS << "Page number: ";
				getline(cin, newPageNumberStr, '\n');
			}
			ss << newPageNumberStr;
			ss >> newPageNumber;
			book->setPageNumber(newPageNumber);
			edited = true;
			break;

		case '4':
			cout << endl;
			while (newISBN.size() == 0
					|| (newISBN.size() != 13 && newISBN.size() != 10)) {
				cout << THREE_TABS << "ISBN: ";
				getline(cin, newISBN, '\n');
			}
			book->setISBN(newISBN);
			edited = true;
			break;

		case '5':
			cout << endl;
			while (newTitle.size() == 0) {
				cout << THREE_TABS << "Title: ";
				getline(cin, newTitle, '\n');
			}
			book->setTitle(newTitle);
			edited = true;
			break;
		case '6':
			if (edited)
				*book = backup;
			exit = true;
			break;
		case '7':

			if (edited)
				library.saveBooks();
			exit = true;
			break;
		case ESCAPE_KEY:
			if (edited)
				*book = backup;
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::editReader(Person* reader) {
	char input;
	bool exit = false;
	bool edited = false;
	string header = "Edit Reader";
	Reader* dReader = dynamic_cast<Reader*>(reader);
	Reader backup = *dReader;

	do {
		string newName, newAgeStr, newPhoneStr, newEmail, changesMessage;
		unsigned int newAge, newPhone;
		stringstream ss;

		clearScreen();
		displayHeader(header);
		cout << THREE_TABS << "[1] Name: " << reader->getName().substr(0, 20)
				<< endl;
		cout << THREE_TABS << "[2] Age: " << reader->getAge() << " years"
				<< endl;
		cout << THREE_TABS << "[3] Phone: " << reader->getPhone() << endl;
		cout << THREE_TABS << "[4] Email: " << reader->getEmail().substr(0, 20)
				<< endl << endl;
		cout << THREE_TABS << "[5] Discard changes" << endl;
		cout << THREE_TABS << "[6] Save" << endl;

		if (changesMessage != "") {
			cout << endl << THREE_TABS << changesMessage << endl;
			changesMessage.clear();
		}
		cout << endl << THREE_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {

		case '1':
			cout << endl;
			while (newName.size() == 0 || !is_All_ASCII_Letter(newName)) {
				cout << THREE_TABS << "Name: ";
				getline(cin, newName, '\n');
			}
			reader->setName(newName);
			edited = true;
			break;

		case '2':
			cout << endl;
			while (newAgeStr.size() == 0 || !is_All_Number(newAgeStr)
					|| newAgeStr.size() > 3) {
				cout << THREE_TABS << "Age: ";
				getline(cin, newAgeStr, '\n');
			}
			ss << newAgeStr;
			ss >> newAge;
			reader->setAge(newAge);
			edited = true;
			break;

		case '3':
			cout << endl;
			while (newPhoneStr.size() == 0 || !is_All_Number(newPhoneStr)
					|| newPhoneStr.size() < 6 || newPhoneStr.size() > 12) {
				cout << THREE_TABS << "Phone: ";
				getline(cin, newPhoneStr, '\n');
			}
			ss << newPhoneStr;
			ss >> newPhone;
			reader->setPhone(newPhone);
			edited = true;
			break;

		case '4':
			cout << endl;
			while (newEmail.size() == 0 || newEmail.size() < 7) {
				cout << THREE_TABS << "Mail: ";
				getline(cin, newEmail, '\n');
			}
			reader->setEmail(newEmail);
			edited = true;
			break;
		case '5':

			if (edited)
				*reader = backup;
			exit = true;
			break;
		case '6':

			if (edited)
				library.savePersons();
			exit = true;
			break;
		case ESCAPE_KEY:

			if (edited)
				*reader = backup;
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
	bool edited = false;
	string header = "Edit Employee";
	Employee* dEmployee = dynamic_cast<Employee*>(employee);
	Employee backup = *dEmployee;

	do {
		string newName, newAgeStr, newPhoneStr, newEmail, newNifStr, newWageStr,
				changesMessage;
		unsigned int newAge, newPhone, newNif, newWage;
		char ch;
		stringstream ss;
		istringstream s;

		clearScreen();
		displayHeader(header);
		cout << THREE_TABS << "[1] Name: " << employee->getName().substr(0, 20)
				<< endl;
		cout << THREE_TABS << "[2] Age: " << employee->getAge() << " years"
				<< endl;
		cout << THREE_TABS << "[3] Phone: " << employee->getPhone() << endl;
		cout << THREE_TABS << "[4] Email: "
				<< employee->getEmail().substr(0, 20) << endl;
		cout << THREE_TABS << "[5] NIF: " << employee->getNif() << endl;
		cout << THREE_TABS << "[6] Wage: " << employee->getWage() << endl;
		cout << THREE_TABS << "[7] Hierarchy: " << employee->printType() << endl
				<< endl;
		cout << THREE_TABS << "[8] Discard changes" << endl;
		cout << THREE_TABS << "[9] Save" << endl;

		if (changesMessage != "") {
			cout << endl << THREE_TABS << changesMessage << endl;
			changesMessage.clear();
		}
		cout << endl << THREE_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {

		case '1':
			cout << endl;
			while (newName.size() == 0 || !is_All_ASCII_Letter(newName)) {
				cout << THREE_TABS << "Name: ";
				getline(cin, newName, '\n');
			}
			employee->setName(newName);
			edited = true;
			break;

		case '2':
			cout << endl;
			while (newAgeStr.size() == 0 || !is_All_Number(newAgeStr)
					|| newAgeStr.size() > 3) {
				cout << THREE_TABS << "Age: ";
				getline(cin, newAgeStr, '\n');
			}
			ss << newAgeStr;
			ss >> newAge;
			employee->setAge(newAge);
			edited = true;
			break;

		case '3':
			cout << endl;
			while (newPhoneStr.size() == 0 || !is_All_Number(newPhoneStr)
					|| newPhoneStr.size() < 6 || newPhoneStr.size() > 12) {
				cout << THREE_TABS << "Phone: ";
				getline(cin, newPhoneStr, '\n');
			}
			ss << newPhoneStr;
			ss >> newPhone;
			employee->setPhone(newPhone);
			edited = true;
			break;

		case '4':
			cout << endl;
			while (newEmail.size() == 0 || newEmail.size() < 7) {
				cout << THREE_TABS << "Mail: ";
				getline(cin, newEmail, '\n');
			}
			employee->setEmail(newEmail);
			edited = true;
			break;

		case '5':
			cout << endl;
			while (newNifStr.size() == 0 || !is_All_Number(newNifStr)
					|| newNifStr.size() != 9 || seekNIF(newNifStr)) {
				cout << THREE_TABS << "NIF: ";
				getline(cin, newNifStr, '\n');
			}
			ss << newNifStr;
			ss >> newNif;
			employee->setNif(newNif);
			edited = true;
			break;
		case '6':
			cout << endl;
			while (newWageStr.size() == 0 || !is_All_Number(newWageStr)) {
				cout << THREE_TABS << "Wage: ";
				getline(cin, newWageStr, '\n');
			}
			ss << newWageStr;
			ss >> newWage;
			employee->setWage(newWage);
			edited = true;
			break;
		case '7':
			cout << endl << THREE_TABS
					<< "[S] to set as supervisor [E] as employee"
					<< PROMPT_SYMBOL;
			ch = cin.get();
			if (tolower(ch) == 's') {
				Employee* e = static_cast<Employee*>(employee);
				if (e != NULL) {
					library.removeEmployeeFromSupervisors(e);
					employee->setSupervisor(1);
					edited = true;
				}
				library.SupervisorEmployeeRandom();
			} else if (tolower(ch) == 'e') {
				employee->setSupervisor(0); // setSupervisor automatically cleans the supervisor team
				edited = true;
				if (library.getEmployees().size() > 1) {
					library.SupervisorEmployeeRandom();
				}
			}
			cin.ignore();
			break;
		case '8':

			if (edited)
				*employee = backup;
			exit = true;
			break;
		case '9':

			if (edited)
				library.savePersons();
			exit = true;
			break;
		case ESCAPE_KEY:

			if (edited)
				*employee = backup;
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::editBorrow(Person* reader) {
	char key;
	bool exit = false;
	vector<Borrow*> borrows;
	string header = "Display borrows";
	string returnDialog = "Return book?";
	string infMsg;

	do {
		clearScreen();
		displayHeader(header);
		borrows = reader->getBorrowedBooks();

		for (size_t i = 0, z = 1; i < borrows.size(); i++) {
			cout << THREE_TABS << "[" << z++ << "] " << borrows[i]->printShort()
					<< endl;
		}
		if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}

		cout << THREE_TABS << "Select book to return [ESC exits]" << endl
				<< endl << THREE_TABS << PROMPT_SYMBOL;

		key = getKey();
		switch (key) {
		case '1':
			if (borrows.size() > 0) {
				if (confirmOperation(returnDialog)) {
					reader->removeBorrow(borrows[0]);
					library.removeBorrow(borrows[0]);
					library.saveBorrows();
					infMsg = "Book returned successfully";
				}
			}
			break;
		case '2':
			if (borrows.size() > 1) {
				if (confirmOperation(returnDialog)) {
					library.removeBorrow(borrows[1]);
					reader->removeBorrow(borrows[1]);
					library.saveBorrows();
					infMsg = "Book returned successfully";
				}
			}
			break;
		case '3':
			if (borrows.size() > 2) {
				if (confirmOperation(returnDialog)) {
					library.removeBorrow(borrows[2]);
					reader->removeBorrow(borrows[2]);
					library.saveBorrows();
					infMsg = "Book returned successfully";
				}
			}
			break;
		case RETURN_KEY:
			if (borrows.size() > 0) {
				if (confirmOperation(returnDialog)) {
					library.removeBorrow(borrows[0]);
					reader->removeBorrow(borrows[0]);
					library.saveBorrows();
					infMsg = "Book returned successfully";
				}
			}
			break;
		case ESCAPE_KEY:
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
	bool clear = false;
	int key;
	size_t selected = 0, vLimit = 10;
	vector<Person*> matches;

	do {
		clearScreen();
		displayHeader(header);
		if (clear) {
			selected = 0;
			matches.clear();
			clear = false;
		}
		if (query.size() > 0 && matches.size() == 0) {
			for (size_t i = 0; i < persons.size(); i++)
				if (partialMatchQuery(query, persons[i]->getName()))
					matches.push_back(persons[i]);
		}

		for (size_t i = 0; i < matches.size() && i < vLimit; i++) {
			colorMsg(THREE_TABS, matches[i]->getName(),
					(selected == i ? FGBLACK_BGGREEN : FGGREEN_BGBLACK), 0);
			cout << TAB;
			if (matches[i]->getName().size() < 16)
				cout << TAB;
			colorMsg("", matches[i]->printType(), FGWHITE_BGBLACK, 1);
		}
		cout << endl << TWO_TABS << TAB << "Enter person name [ESC exits]\n\n"
				<< TWO_TABS << TAB << PROMPT_SYMBOL << query;

		key = getKey();

		switch (key) {
		case 0:
			break;
		case RETURN_KEY:
			if (matches.size() > selected)
				return matches[selected];
			break;
		case BACKSPACE_KEY:
			if (query.length() > 0) {
				clear = true;
				query.erase(query.end() - 1);
			}
			break;
		case ESCAPE_KEY:
			exit = true;
			break;
		case DELETE_KEY:
			clear = true;
			query.clear();
			break;
		case ARROW_DOWN:
			selected++;
			selected %= (matches.size() > vLimit ? vLimit : matches.size());
			break;
		case ARROW_UP:
			if (selected < 1)
				selected = (matches.size() > vLimit ? vLimit : matches.size())
						- 1;
			else
				selected--;
			break;
		default:
			clear = true;
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
	bool clear = false;
	int key;
	size_t selected = 0, vLimit = 4;
	vector<Book*> matches;
	do {
		clearScreen();
		displayHeader(header);

		if (clear) {
			selected = 0;
			matches.clear();
			clear = false;
		}
		// Search books for given query
		if (query.size() > 0 && matches.size() == 0) {
			for (size_t i = 0; i < books.size(); i++) {
				string title = books[i]->getTitle();
				vector<string> authors = books[i]->getAuthors();

				bool matchAuthor = false;
				for (size_t y = 0; y < authors.size(); y++)
					matchAuthor |= partialMatchQuery(query, authors[y]);

				if (partialMatchQuery(query, title) || matchAuthor)
					matches.push_back(books[i]);
			}
		}
		// Display books that match
		for (size_t i = 0; i < matches.size() && i < vLimit; i++) {
			colorMsg(THREE_TABS, matches[i]->getTitle().substr(0, 34) + " ",
					(selected == i ? FGBLACK_BGGREEN : FGGREEN_BGBLACK), 0);
			colorMsg("",
					(books[i]->getBorrowed() == 1 ? "[Borrowed]" : "[Available]"),
					FGWHITE_BGBLACK, 1);
			colorMsg(THREE_TABS, matches[i]->printAuthors() + " ",
					(selected == i ? FGBLACK_BGGREEN : FGGREEN_BGBLACK), 2);
		}
		cout << endl << THREE_TABS << "Enter title or author [ESC exits]"
				<< endl << endl;
		cout << THREE_TABS << PROMPT_SYMBOL << query;

		key = getKey();

		switch (key) {
		case 0:
			break;
		case RETURN_KEY:
			if (matches.size() > selected)
				return matches[selected];
			break;
		case BACKSPACE_KEY:
			if (query.length() > 0) {
				clear = true;
				query.erase(query.end() - 1);
			}
			break;
		case ESCAPE_KEY:
			exit = true;
			break;
		case DELETE_KEY:
			clear = true;
			query.clear();
			break;
		case ARROW_DOWN:
			selected++;
			selected %= (matches.size() > vLimit ? vLimit : matches.size());
			break;
		case ARROW_UP:
			if (selected < 1)
				selected = (matches.size() > vLimit ? vLimit : matches.size())
						- 1;
			else
				selected--;
			break;
		default:
			clear = true;
			query += char(key);
			break;
		}
	} while (!exit);
	return NULL;
}

void Interface::clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	if ((HANDLE) hConsoleOutput == INVALID_HANDLE_VALUE)
		return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hConsoleOutput, &csbi))
		return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(hConsoleOutput, (TCHAR) ' ', cellCount,
			homeCoords, &count))
		return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(hConsoleOutput, csbi.wAttributes, cellCount,
			homeCoords, &count))
		return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hConsoleOutput, homeCoords);
#else
	system(CLEARSCREEN);
#endif
}

void Interface::displayHeader(string& header) {
	unsigned int width = 77;
	unsigned int size = header.size();
	unsigned int dynSizeLeft = ceil((width - size) / 2);
	unsigned int dynSizeRight = dynSizeLeft;

	if (dynSizeLeft + dynSizeRight + size < width)
		dynSizeRight++;
	colorMsg(" ", string(width, ' '), FGBLACK_BGGREEN, 1);
	colorMsg(" ", string(dynSizeLeft, ' ') + header + string(dynSizeRight, ' '),
	FGBLACK_BGGREEN, 1);
	colorMsg(" ", string(width, ' '), FGBLACK_BGGREEN, 3);
}

bool Interface::confirmOperation(string& query) {
	setColor(FGWHITE_BGBLACK);
	cout << query << " [y] to confirm";
	char answer = getKey();
	resetColor();

	if (answer == 'y' || answer == 'Y')
		return true;
	else
		return false;
}

template<class T>
string Interface::repeatStr(const T& s, const size_t n) {
	stringstream ss;
	for (size_t i = 0; i < n; i++)
		ss << s;
	return ss.str();
}

void Interface::personsDisplayPtr(LibraryGetFn getFunc, string listName,
		string labels, string readerStr[], LibraryMemFn funcs[],
		size_t length) {

	CALL_MEMBER_FN(library,funcs[0])();
	vector<Person*> vec = CALL_MEMBER_FN(library,getFunc)();
	unsigned int vecSize = vec.size(), pCount = 1, vLimit = 0, i = 0, progress;
	float pLimit;
	bool done = false;
	size_t sortFunc = 0;
	string vLimitMsg =
			" [ESC] to interrupt [s] to sort or any other key to continue...";
	char ch;

	if (vecSize == 0)
		pLimit = 1;
	else
		pLimit = ceil(static_cast<float>(vecSize) / MAX_LINES);
	while (1) {
		do {
			vLimit = 0;
			progress = ceil((13.0 / pLimit) * pCount);
			clearScreen();
			displayHeader(listName);
			cout << TWO_TABS << ("Sorted by " + readerStr[sortFunc])
					<< (readerStr[sortFunc].size() > 5 ? TAB : TWO_TABS)
					<< "Page " << pCount << " of " << pLimit << " ["
					<< repeatStr(progressBar, progress)
					<< string((13 - progress), ' ') << "]" << endl << endl;
			cout << " " << repeatStr(hSeparator, 77) << " " << endl;
			cout << " " << labels << endl;
			cout << " " << repeatStr(hSeparator, 77) << " " << endl;

			if (vecSize == 0) {
				string nothing = "Nothing to show here :(";
				cout << string(5, '\n');
				errorMsg(nothing);
				cout << string(6, '\n');
			}

			while (vLimit < MAX_LINES && i < vecSize && !done) {
				setColor(FGWHITE_BGBLACK);
				cout << " " << vec[i]->print();
				resetColor();
				cout << endl;
				i++;
				vLimit++;

				if (vLimit == MAX_LINES && i <= vecSize) {
					pCount++;
					cout << " " << repeatStr(hSeparator, 77) << endl
							<< vLimitMsg;
					ch = getKey();
					if (ch == ESCAPE_KEY)
						done = true;
					else if (ch == 's') {
						sortFunc++;
						sortFunc %= length;
						CALL_MEMBER_FN(library,funcs[sortFunc])();
						clearScreen();
						pCount = 1, i = 0, progress = 0;
						vec = CALL_MEMBER_FN(library,getFunc)();
					}
				}
			}
			if (vecSize != 0)
				cout << string((MAX_LINES - vLimit), '\n');
		} while (i < vecSize && !done);
		if (done)
			break;
		else if (i == vecSize) {
			cout << " " << repeatStr(hSeparator, 77) << endl << vLimitMsg;
			ch = getKey();
			if (ch == 's') {
				sortFunc++;
				sortFunc %= length;
				clearScreen();
				CALL_MEMBER_FN(library,funcs[sortFunc])();
				pCount = 1, i = 0, progress = 0;
				vec = CALL_MEMBER_FN(library,getFunc)();
			} else
				break;
		}
	}
}

void Interface::booksDisplayPtr(LibraryGetBkFn getFunc, string listName,
		string labels, string readerStr[], LibraryMemFn funcs[],
		size_t length) {

	CALL_MEMBER_FN(library,funcs[0])();
	vector<Book*> vec = CALL_MEMBER_FN(library,getFunc)();
	unsigned int vecSize = vec.size(), pCount = 1, vLimit = 0, i = 0, progress;
	float pLimit;
	bool done = false;
	size_t sortFunc = 0;
	string vLimitMsg =
			" [ESC] to interrupt [s] to sort or any other key to continue...";
	char ch;

	if (vecSize == 0)
		pLimit = 1;
	else
		pLimit = ceil(static_cast<float>(vecSize) / MAX_LINES);
	while (1) {
		do {
			vLimit = 0;
			progress = ceil((13.0 / pLimit) * pCount);
			clearScreen();
			displayHeader(listName);
			cout << TWO_TABS << ("Sorted by " + readerStr[sortFunc])
					<< (readerStr[sortFunc].size() > 5 ? TAB : TWO_TABS)
					<< "Page " << pCount << " of " << pLimit << " ["
					<< repeatStr(progressBar, progress)
					<< string((13 - progress), ' ') << "]" << endl;
			cout << " " << repeatStr(hSeparator, 77) << " " << endl;
			cout << " " << labels << endl;
			cout << " " << repeatStr(hSeparator, 77) << " " << endl;

			if (vecSize == 0) {
				string nothing = "Nothing to show here :(";
				cout << string(5, '\n');
				errorMsg(nothing);
				cout << string(6, '\n');
			}

			while (vLimit < MAX_LINES && i < vecSize && !done) {
				setColor(FGWHITE_BGBLACK);
				cout << " " << vec[i]->print();
				resetColor();
				cout << endl;
				i++;
				vLimit++;

				if (vLimit == MAX_LINES && i <= vecSize) {
					pCount++;
					cout << " " << repeatStr(hSeparator, 77) << endl
							<< vLimitMsg;
					ch = getKey();
					if (ch == ESCAPE_KEY)
						done = true;
					else if (ch == 's') {
						sortFunc++;
						sortFunc %= length;
						CALL_MEMBER_FN(library,funcs[sortFunc])();
						clearScreen();
						pCount = 1, i = 0, progress = 0;
						vec = CALL_MEMBER_FN(library,getFunc)();
					}
				}
			}
			if (vecSize != 0)
				cout << string((MAX_LINES - vLimit), '\n');
		} while (i < vecSize && !done);
		if (done)
			break;
		else if (i == vecSize) {
			cout << " " << repeatStr(hSeparator, 77) << endl << vLimitMsg;
			ch = getKey();
			if (ch == 's') {
				sortFunc++;
				sortFunc %= length;
				clearScreen();
				CALL_MEMBER_FN(library,funcs[sortFunc])();
				pCount = 1, i = 0, progress = 0;
				vec = CALL_MEMBER_FN(library,getFunc)();
			} else
				break;
		}
	}
}

template<typename T>
void Interface::genericDisplay(vector<T> vec, string listName, string labels) {
	unsigned int vecSize = vec.size(), pCount = 1, vLimit = 0, i = 0, progress;
	float pLimit;
	bool done = false;
	string vLimitMsg = " [ESC] to interrupt or any other key to continue...";
	char ch;

	if (vecSize == 0)
		pLimit = 1;
	else
		pLimit = ceil(static_cast<float>(vecSize) / MAX_LINES);

	do {
		vLimit = 0;
		progress = ceil((19.0 / pLimit) * pCount);
		clearScreen();
		displayHeader(listName);
		cout << THREE_TABS << "Page " << pCount << " of " << pLimit << " ["
				<< repeatStr(progressBar, progress)
				<< string((19 - progress), ' ') << "]" << endl;
		cout << " " << repeatStr(hSeparator, 77) << " " << endl;
		cout << " " << labels << endl;
		cout << " " << repeatStr(hSeparator, 77) << " " << endl;

		if (vecSize == 0) {
			string nothing = "Nothing to show here :(";
			cout << string(5, '\n');
			errorMsg(nothing);
			cout << string(6, '\n');
		}

		while (vLimit < MAX_LINES && i < vecSize && !done) {
			setColor(FGWHITE_BGBLACK);
			cout << " " << vec[i]->print();
			resetColor();
			cout << endl;
			i++;
			vLimit++;

			if (vLimit == MAX_LINES && i < vecSize) {
				pCount++;
				cout << " " << repeatStr(hSeparator, 77) << endl << vLimitMsg;
				ch = getKey();
				if (ch == ESCAPE_KEY)
					done = true;
			}
		}
		if (vecSize != 0)
			cout << string((MAX_LINES - vLimit), '\n');
	} while (i < vecSize && !done);
	if (i == vecSize) {
		cout << " " << repeatStr(hSeparator, 77) << endl;
		cout << " Press any key to continue...";
		getKey();
	}
}

char Interface::getKey() {
#ifdef _WIN32

	DWORD fdwSaveOldMode;

	GetConsoleMode(hConsoleInput, &fdwSaveOldMode);

// no need to read the return character nor mouse events
	DWORD mode = !ENABLE_ECHO_INPUT | !ENABLE_LINE_INPUT
			| ENABLE_PROCESSED_INPUT | !ENABLE_MOUSE_INPUT;

	SetConsoleMode(hConsoleInput, mode);

	INPUT_RECORD lpBuffer;
	DWORD lpNumberOfEventsRead;
	DWORD specialKey;

	do {
		ReadConsoleInput(hConsoleInput, &lpBuffer, 128, &lpNumberOfEventsRead);
	} while (!lpBuffer.Event.KeyEvent.bKeyDown);

	specialKey = lpBuffer.Event.KeyEvent.wVirtualScanCode;
	char key = 0;

	if (specialKey == 72)
		key = ARROW_UP;
	else if (specialKey == 80)
		key = ARROW_DOWN;
	else if (specialKey == 83)
		key = DELETE_KEY;
	else if (specialKey == 1)
		key = ESCAPE_KEY;
	else
		key = lpBuffer.Event.KeyEvent.uChar.AsciiChar;

// Restore input mode on exit.
	SetConsoleMode(hConsoleInput, fdwSaveOldMode);

	return key;

#elif _WIN64
	return getch();
#else
	static struct termios oldt, newt;

	/*tcgetattr gets the parameters of the current terminal
	 STDIN_FILENO will tell tcgetattr that it should write the settings
	 of stdin to oldt*/
	tcgetattr( STDIN_FILENO, &oldt);
	/*now the settings will be copied*/
	newt = oldt;

	/*ICANON normally takes care that one line at a time will be processed
	 that means it will return if it sees a "\n" or an EOF or an EOL*/
	newt.c_lflag &= ~(ICANON | ECHO);

	/*Those new settings will be set to STDIN
	 TCSANOW tells tcsetattr to change attributes immediately. */
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);

	/*This is your part:
	 I choose 'e' to end input. Notice that EOF is also turned off
	 in the non-canonical mode*/
	char keys[32] = {0};
	fflush(stdout);
	read(STDIN_FILENO,keys,4096);

	if(keys[0] == 27 && keys[1] == 91) {
		if(keys[2] == 51 && keys[3] == 126)
		keys[0] = DELETE_KEY;
		else if (keys[2] == 65)
		keys[0] = ARROW_UP;
		else if (keys[2] == 66)
		keys[0] = ARROW_DOWN;
		else
		keys[0] = 0;
	}
	else if (keys[0] == 27 && keys[2] != 0)
	keys[0] = 0;

	/*restore the old settings*/
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	return keys[0];
#endif
}

void Interface::setColor(int color) {
#if defined(_WIN32) || defined(_WIN64)
	switch (color) {
	case FGGRAY_BGBLACK:
		SetConsoleTextAttribute(hConsoleOutput,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case FGWHITE_BGBLACK:
		SetConsoleTextAttribute(hConsoleOutput,
				FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
						| FOREGROUND_INTENSITY);
		break;
	case FGRED_BGBLACK:
		SetConsoleTextAttribute(hConsoleOutput,
		FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case FGGREEN_BGBLACK:
		SetConsoleTextAttribute(hConsoleOutput,
		FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case FGBLUE_BGBLACK:
		SetConsoleTextAttribute(hConsoleOutput,
		FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case FGGRAY_BGRED:
		SetConsoleTextAttribute(hConsoleOutput,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED);
		break;
	case FGWHITE_BGRED:
		SetConsoleTextAttribute(hConsoleOutput,
				FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
						| FOREGROUND_INTENSITY | BACKGROUND_RED);
		break;
	case FGBLACK_BGWHITE:
		SetConsoleTextAttribute(hConsoleOutput,
				BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
						| BACKGROUND_INTENSITY);
		break;
	case FGBLACK_BGGRAY:
		SetConsoleTextAttribute(hConsoleOutput,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		break;
	case FGBLACK_BGGREEN:
		SetConsoleTextAttribute(hConsoleOutput,
		BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		break;
	default:
		break;
	}
#else

	switch (color) {
		case 0:
		cout << "\033[0;37m";
		break;
		case 1:
		cout << "\033[0;31m";
		break;
		case 2:
		cout << "\033[0;32m";
		break;
		case 5:
		cout << "\033[1;41;1;37m";
		break;
		case 3:
		cout << "\033[0;34m";
		break;
		case 6:
		cout << "\033[1;30;1;47m";
		break;
		case 7:
		cout << "\033[1;30;1;47m";
		break;
		case 8:
		cout <<"\033[42;30m";
		break;
		default:
		break;
	}

#endif
}

void Interface::resetColor() {
#if defined(_WIN32) || defined(_WIN64)
	SetConsoleTextAttribute(hConsoleOutput,
	FOREGROUND_GREEN | FOREGROUND_INTENSITY | 0 | 0 | 0);
#else
	cout << "\033[0;32m";
#endif
}
vector<string> Interface::editAuthors() {
	vector<string> authors;
	string newAuthor, authorsDialog = "\t\t\tAdd another author?";
	for (int i = 1; authors.size() == 0 || authors.size() < 8; i++) {
		while (newAuthor.size() == 0 || !is_All_ASCII_Letter(newAuthor)) {
			cout << THREE_TABS << "Author " << i << ": ";
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

inline void Interface::centerString(const size_t &size) {
	int spacing = (int) ((80 - size) / 2);
	cout << string(spacing, ' ');
}

void Interface::colorMsg(const string &tabs, const string &s, const int &color,
		const int &newLines) {
	cout << tabs;
	setColor(color);
	cout << s;
	resetColor();
	cout << string(newLines, '\n');
}

void Interface::infoMsg(const string& m) {
	centerString(m.size() + 2);
	setColor(FGBLACK_BGGRAY);
	cout << " " + m + " ";
	resetColor();
}

void Interface::errorMsg(const string& m) {
	centerString(m.size() + 2);
	setColor(FGWHITE_BGRED);
	cout << " " + m + " ";
	resetColor();
}

bool Interface::seekNIF(const string &s) {
	vector<Person*> employees = library.getEmployees();
	unsigned int nif;
	stringstream ss;
	ss << s;
	ss >> nif;

	for (size_t i = 0; i < employees.size(); i++)
		if (employees[i]->getNif() == nif)
			return true;

	return false;
}
