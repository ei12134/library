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
		cout << endl << FOUR_TABS << "[1] Login\n\n";
		cout << FOUR_TABS << "[2] Display\n\n";
		cout << FOUR_TABS << "[3] Quit\n\n" << THREE_TABS << PROMPT_SYMBOL;

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

void Interface::readerMenu(Person *reader) {
	char input;
	bool exit = false;
	string header = "Reader   " + reader->getName();
	string message;

	do {
		clearScreen();
		displayHeader(header);

		cout << THREE_TABS << "Age:" << TAB << reader->getAge() << endl;
		cout << THREE_TABS << "Card:" << TAB << reader->getCard() << endl;
		cout << THREE_TABS << "Phone:" << TAB << reader->getPhone() << endl;
		cout << THREE_TABS << "Email:" << TAB << reader->getEmail() << endl;
		cout << endl << THREE_TABS << "[1] Display borrows\n";
		cout << THREE_TABS << "[2] Borrow history\n";
		cout << THREE_TABS << "[3] Logout\n\n" << TWO_TABS << TAB
				<< PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			clearScreen();
			editBorrow(reader);
			break;
		case '2':
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

void Interface::employeeMenu(Person* employee) {
	char input;
	bool exit = false;
	string header = "Employee   " + employee->getName();

	do {
		clearScreen();
		displayHeader(header);
		cout << THREE_TABS << HALF_TAB << "Age: " << employee->getAge() << endl;
		cout << THREE_TABS << HALF_TAB << "Nif: " << employee->getNif() << endl;
		cout << THREE_TABS << HALF_TAB << "Phone: " << employee->getPhone()
				<< endl;
		cout << THREE_TABS << HALF_TAB << "Email: " << employee->getEmail()
				<< endl;
		cout << THREE_TABS << HALF_TAB << "Wage: " << employee->getWage()
				<< " euros" << endl;
		cout << endl << THREE_TABS << HALF_TAB << "[1] Borrow a book\n";
		cout << THREE_TABS << HALF_TAB << "[2] Manage readers\n";
		cout << THREE_TABS << HALF_TAB << "[3] Manage books\n";
		cout << THREE_TABS << HALF_TAB << "[4] Logout\n\n" << TWO_TABS << TAB
				<< PROMPT_SYMBOL;

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
		cout << THREE_TABS << HALF_TAB << "Age: " << supervisor->getAge()
				<< " years" << endl;
		cout << THREE_TABS << HALF_TAB << "Nif: " << supervisor->getNif()
				<< endl;
		cout << THREE_TABS << HALF_TAB << "Phone: " << supervisor->getPhone()
				<< endl;
		cout << THREE_TABS << HALF_TAB << "Email: " << supervisor->getEmail()
				<< endl;
		cout << THREE_TABS << HALF_TAB << "Wage: " << supervisor->getWage()
				<< " euros" << endl;
		cout << endl << THREE_TABS + HALF_TAB << "[1] Borrow a book\n";
		cout << THREE_TABS << HALF_TAB << "[2] Manage books\n";
		cout << THREE_TABS << HALF_TAB << "[3] Manage readers\n";
		cout << THREE_TABS << HALF_TAB << "[4] Manage employees\n";
		cout << THREE_TABS << HALF_TAB << "[5] Employees team\n";
		cout << THREE_TABS << HALF_TAB << "[6] Logout\n\n" << TWO_TABS << TAB
				<< PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			createBorrow(supervisor);
			break;
		case '2':
			manageBooks();
		case '3':
			manageReaders();
			break;
		case '4':
			manageEmployees(supervisor);
			break;
		case '5':
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

void Interface::manageBooks() {
	char input;
	bool exit = false;
	string header = "Manage books", message;
	string confirmRemove = "Remove book?";
	Book* book;

	do {
		clearScreen();
		displayHeader(header);
		cout << endl << FOUR_TABS << "[1] Create book\n";
		cout << FOUR_TABS << "[2] Edit book\n";
		cout << FOUR_TABS << "[3] Remove book\n";
		cout << FOUR_TABS << "[4] Exit\n\n";
		if (message.size() > 0) {
			cout << THREE_TABS << warningParameter(message) << endl << endl;
			message.clear();
		}
		cout << THREE_TABS << PROMPT_SYMBOL;

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
			book = searchBook(library.getBooks());
			if (book != NULL && confirmOperation(confirmRemove)) {
				if (library.removeBook(book))
					message = "Book removed successfully";
				else
					message = "Error removing a book";
			} else
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

void Interface::manageReaders() {
	char input;
	bool exit = false;
	string header = "Manage readers";
	string message;
	Person* reader;

	do {
		clearScreen();
		displayHeader(header);
		cout << endl << FOUR_TABS << "[1] Create reader\n";
		cout << FOUR_TABS << "[2] Edit reader\n";
		cout << FOUR_TABS << "[3] Remove reader\n";
		cout << FOUR_TABS << "[4] Exit\n\n";
		if (message.size() > 0) {
			cout << THREE_TABS << warningParameter(message) << endl << endl;
			message.clear();
		}
		cout << THREE_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			clearScreen();
			createReader();
			break;
		case '2':
			reader = searchPerson(library.getReaders());
			if (reader != NULL)
				editReader(reader);
			else
				message = "Error editing a reader";
			break;
		case '3':
			clearScreen();
			if (library.removeReader(searchPerson(library.getReaders())))
				message = "Reader removed successfully";
			else
				message = "Error removing a reader";
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
	Person* employee;

	do {
		clearScreen();
		displayHeader(header);
		cout << endl << FOUR_TABS << "[1] Create employee\n";
		cout << FOUR_TABS << "[2] Edit employee\n";
		cout << FOUR_TABS << "[3] Remove employee\n";
		cout << FOUR_TABS << "[4] Exit\n\n";
		if (message.size() > 0) {
			cout << THREE_TABS << warningParameter(message) << endl << endl;
			message.clear();
		}
		cout << THREE_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			clearScreen();
			createEmployee();
			break;
		case '2':
			employee = searchPerson(library.getEmployees());
			if (employee != NULL)
				editEmployee(employee);
			else
				message = "Error editing an employee";
			break;
		case '3':
			clearScreen();
			if (library.removeEmployee((searchPerson(library.getEmployees())),
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
		cout << endl << THREE_TABS << newTitle << " successfully created.";
	} else
		cout << "Book creation cancelled\n";
	getKey();
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
		cout << endl << THREE_TABS << newName << " successfully created.";
	} else
		cout << "Reader creation cancelled\n";
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

	if (confirmOperation(supervisorDialog))
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
		cout << endl << THREE_TABS << newName << " successfully created.";
	} else
		cout << "Employee creation cancelled\n";
	getKey();
}

void Interface::createBorrow(Person* employee) {
	char input;
	bool exit = false;
	string header = "Create borrow";
	string createMessage;
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

		if (createMessage.size() > 0) {
			cout << THREE_TABS << warningParameter(createMessage) << endl
					<< endl;
			createMessage.clear();
		}

		cout << THREE_TABS << "Select book to return [ESC exits]" << endl
				<< endl << THREE_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			reader = searchPerson(library.getReaders());
			if (reader == NULL || reader->getBorrowedBooks().size() > 2) {
				reader = NULL;
				createMessage = "Select another reader";
			}
			break;
		case '2':
			book = searchBook(library.getAvailableBooks());
			if (book == NULL || book->getBorrowed()) {
				book = NULL;
				createMessage = "Select another book";
			}
			break;
		case '3':
			if (reader != NULL && book != NULL) {
				Borrow* borrow = new Borrow(book, employee, reader);
				if (reader->addBorrow(borrow)) {
					library.addBorrow(borrow);
					book->setBorrowed(true);
				}else{
					delete borrow;
				}

				createMessage = "Borrow created successfully";
				reader = NULL;
				book = NULL;
			} else
				createMessage = "Select a reader and a book";
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

void Interface::editBook(Book* book) {
	char input;
	bool exit = false;
	string header = "Edit book";
	do {
		string newQuota, newTitle, newISBN, newPageNumberStr, changesMessage;
		unsigned int newPageNumber;
		stringstream ss;
		istringstream s;

		clearScreen();
		displayHeader(header);
		cout << endl << THREE_TABS << "[1] Author" << TAB
				<< optionalParameter(book->getAuthors()[0]) << endl;
		cout << THREE_TABS << "[2] Quota" << TAB
				<< optionalParameter(book->getQuota()) << endl;
		cout << THREE_TABS << "[3] Page number" << TAB <<
		optionalParameter(book->getPageNumber()) << endl;
		cout << THREE_TABS << "[4] ISBN" << TAB
				<< optionalParameter(book->getISBN()) << endl;
		cout << THREE_TABS << "[5] Title" << TAB
				<< (book->getTitle().size() > 16 ?
						optionalParameter(book->getTitle().substr(0, 16)) :
						optionalParameter(book->getTitle())) << endl; //
		cout << THREE_TABS << "[6] Exit" << endl;

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
			changesMessage = "Changes saved successfully";
			break;

		case '2':
			cout << endl;
			while (newQuota.size() == 0) {
				cout << THREE_TABS << "Quota: ";
				getline(cin, newQuota, '\n');
			}
			book->setQuota(newQuota);
			changesMessage = "Changes saved successfully";
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
			changesMessage = "Changes saved successfully";
			break;

		case '4':
			cout << endl;
			while (newISBN.size() == 0
					|| (newISBN.size() != 13 && newISBN.size() != 10)) {
				cout << THREE_TABS << "ISBN: ";
				getline(cin, newISBN, '\n');
			}
			book->setISBN(newISBN);
			changesMessage = "Changes saved successfully";
			break;

		case '5':
			cout << endl;
			while (newTitle.size() == 0) {
				cout << THREE_TABS << "Title: ";
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

void Interface::editReader(Person* reader) {
	char input;
	bool exit = false;
	string header = "Edit Reader";
	do {
		string newName, newAgeStr, newPhoneStr, newEmail, changesMessage;
		unsigned int newAge, newPhone;
		stringstream ss;

		clearScreen();
		displayHeader(header);
		cout << endl << THREE_TABS << "[1] Name" << TAB
				<< reader->getName().substr(0, 15) << endl;
		cout << THREE_TABS << "[2] Age:" << TAB << reader->getAge() << " years"
				<< endl;
		cout << THREE_TABS << "[3] Phone:" << TAB << reader->getPhone() << endl;
		cout << THREE_TABS << "[4] Email:" << TAB << reader->getEmail() << endl;
		cout << THREE_TABS << "[5] Exit" << endl;

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
			changesMessage = "Changes saved successfully";
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
			changesMessage = "Changes saved successfully";
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
			changesMessage = "Changes saved successfully";
			break;

		case '4':
			cout << endl;
			while (newEmail.size() == 0 || newEmail.size() < 7) {
				cout << THREE_TABS << "Mail: ";
				getline(cin, newEmail, '\n');
			}
			reader->setEmail(newEmail);
			changesMessage = "Changes saved successfully";
			break;
		case '5':
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
		char ch;
		stringstream ss;
		istringstream s;

		clearScreen();
		displayHeader(header);
		cout << endl << THREE_TABS << "[1] Name:" << TAB << employee->getName()
				<< endl;
		cout << THREE_TABS << "[2] Age:" << TAB << employee->getAge()
				<< " years" << endl;
		cout << THREE_TABS << "[3] Phone:" << TAB << employee->getPhone()
				<< endl;
		cout << THREE_TABS << "[4] Email:" << TAB << employee->getEmail()
				<< endl;
		cout << THREE_TABS << "[5] NIF:" << TAB << employee->getNif() << endl;
		cout << THREE_TABS << "[6] Wage:" << TAB << employee->getWage() << endl;
		cout << THREE_TABS << "[7] Hierarchy:" << TAB << employee->printType()
				<< endl;
		cout << THREE_TABS << "[8] Exit" << endl;

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
			changesMessage = "Changes saved successfully";
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
			changesMessage = "Changes saved successfully";
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
			changesMessage = "Changes saved successfully";
			break;

		case '4':
			cout << endl;
			while (newEmail.size() == 0 || newEmail.size() < 7) {
				cout << THREE_TABS << "Mail: ";
				getline(cin, newEmail, '\n');
			}
			employee->setEmail(newEmail);
			changesMessage = "Changes saved successfully";
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
			changesMessage = "Changes saved successfully";
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
			changesMessage = "Changes saved successfully";
			break;
		case '7':
			cout << endl << THREE_TABS
					<< "[S] to set as supervisor [E] as employee"
					<< PROMPT_SYMBOL;
			ch = cin.get();
			if (tolower(ch) == 's') {
				employee->setSupervisor(1);
				changesMessage = "Changes saved successfully";
			} else if (tolower(ch) == 'e') {
				employee->setSupervisor(0);
				changesMessage = "Changes saved successfully";
			}
			cin.ignore();
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

void Interface::editBorrow(Person* reader) {
	char key;
	bool exit = false;
	vector<Borrow*> borrows;
	string header = "Display borrows";
	string returnDialog = "Return book?";
	string returnMessage;

	do {
		clearScreen();
		displayHeader(header);
		borrows = reader->getBorrowedBooks();

		for (size_t i = 0, z = 1; i < borrows.size(); i++) {
			cout << THREE_TABS << "[" << z++ << "] " << borrows[i]->printShort()
					<< endl;
		}
		if (returnMessage.size() > 0) {
			cout << THREE_TABS << warningParameter(returnMessage) << endl
					<< endl;
			returnMessage.clear();
		}

		cout << THREE_TABS << "Select book to return [ESC exits]" << endl
				<< endl << THREE_TABS << PROMPT_SYMBOL;

		key = getKey();
		switch (key) {
		case '1':
			if (borrows.size() > 0) {
				if (confirmOperation(returnDialog)) {
					library.removeBorrow(borrows[0]);
					reader->removeBorrow(borrows[0]);
					returnMessage = "Book returned successfully";
				}
			}
			break;
		case '2':
			if (borrows.size() > 1) {
				if (confirmOperation(returnDialog)) {
					library.removeBorrow(borrows[1]);
					reader->removeBorrow(borrows[1]);
					returnMessage = "Book returned successfully";
				}
			}
			break;
		case '3':
			if (borrows.size() > 2) {
				if (confirmOperation(returnDialog)) {
					library.removeBorrow(borrows[2]);
					reader->removeBorrow(borrows[2]);
					returnMessage = "Book returned successfully";
				}
			}
			break;
		case RETURN_KEY:
			if (borrows.size() > 0) {
				if (confirmOperation(returnDialog)) {
					library.removeBorrow(borrows[0]);
					reader->removeBorrow(borrows[0]);
					returnMessage = "Book returned successfully";
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
				if (partialMatchQuery(query, name)) {
					cout << THREE_TABS << "[" << z++ << "] "
							<< persons[i]->getName() << TAB;

					if (persons[i]->getName().size() < 12)
						cout << TAB;

					cout << persons[i]->printType() << endl << endl;
					matches.push_back(persons[i]);
				}
			}
		}

		cout << endl << TWO_TABS << TAB << "Enter person name [ESC exits]\n\n"
				<< TWO_TABS << TAB << PROMPT_SYMBOL << query;

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
		matches.reserve(4);
		if (query.size() > 0) {
			for (size_t i = 0, z = 1; i < books.size() && z < 5; i++) {
				string title = books[i]->getTitle();
				vector<string> authors = books[i]->getAuthors();
				bool matchAuthor = false;
				for (size_t y = 0; y < authors.size(); y++)
					matchAuthor |= partialMatchQuery(query, authors[y]);

				if (partialMatchQuery(query, title) || matchAuthor) {
					cout << TWO_TABS << "[" << z++ << "] "
							<< books[i]->printShort() << endl << endl;
					matches.push_back(books[i]);
				}
			}
		}
		cout << endl << THREE_TABS << "Enter title or author [ESC exits]"
				<< endl << endl;
		cout << THREE_TABS << PROMPT_SYMBOL << query;

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
		cout << endl << FOUR_TABS << "[1] Persons\n\n";
		cout << FOUR_TABS << "[2] Readers\n\n";
		cout << FOUR_TABS << "[3] Employees\n\n";
		cout << FOUR_TABS << "[4] Supervisors\n\n";
		cout << FOUR_TABS << "[5] Books\n\n";
		cout << FOUR_TABS << "[6] Exit to menu\n\n\n";
		cout << THREE_TABS << PROMPT_SYMBOL;

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
					"\tTitle\t\t\tAuthors\t\tISBN\t\tStatus");
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

	cout << THREE_TABS << string(33, '#') << endl;
	cout << THREE_TABS << "#" << FOUR_TABS << "#" << endl;
	cout << THREE_TABS << "#" << string(dynSizeLeft, ' ') << header
			<< string(dynSizeRight, ' ') << "#" << endl;
	cout << THREE_TABS << "#" << FOUR_TABS << "#" << endl;
	cout << THREE_TABS << string(33, '#') << endl << endl;
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
		cout << THREE_TABS << "Page " << pCount << " of " << pLimit << " ["
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
				cout << " " << string(77, '-') << endl << vLimitMsg;
				ch = getKey();
				if (ch == ESCAPE_KEY)
					done = true;
			}
		}
	}
	if (i == vecSize) {
		cout << " " << string(77, '-') << endl;
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

template<typename T>
string Interface::optionalParameter(const T &p) {
	stringstream ss;
	ss << "[" << p << "]";
	return ss.str();
}

template<typename T>
string Interface::warningParameter(const T &p) {
	stringstream ss;
	ss << "*** " << p << " ***";
	return ss.str();
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
