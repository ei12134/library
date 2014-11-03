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
		cout << endl << DOUBLE_TAB << DOUBLE_TAB << "[1] Login\n\n";
		cout << DOUBLE_TAB << DOUBLE_TAB << "[2] Display\n\n";
		cout << DOUBLE_TAB << DOUBLE_TAB << "[3] Quit\n\n" << DOUBLE_TAB << TAB
				<< PROMPT_SYMBOL;

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

		cout << DOUBLE_TAB << TAB << "Age :" << TAB << reader->getAge() << endl;
		cout << DOUBLE_TAB << TAB << "Card :" << TAB << reader->getCard()
				<< endl;
		cout << DOUBLE_TAB << TAB << "Phone :" << TAB << reader->getPhone()
				<< endl;
		cout << DOUBLE_TAB << TAB << "Email :" << TAB << reader->getEmail()
				<< endl;
		cout << endl << DOUBLE_TAB << TAB << "[1] Borrowed books\n";
		cout << DOUBLE_TAB << TAB << "[2] Return a book\n";
		cout << DOUBLE_TAB << TAB << "[3] History\n";
		cout << DOUBLE_TAB << TAB << "[4] Logout\n\n" << DOUBLE_TAB << TAB
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
		cout << DOUBLE_TAB << TAB << "Age :" << TAB << employee->getAge()
				<< endl;
		cout << DOUBLE_TAB << TAB << "Card :" << TAB << employee->getNif()
				<< endl;
		cout << DOUBLE_TAB << TAB << "Phone :" << TAB << employee->getPhone()
				<< endl;
		cout << DOUBLE_TAB << TAB << "Email :" << TAB << employee->getEmail()
				<< endl;
		cout << DOUBLE_TAB << TAB << "Wage :" << TAB << employee->getWage()
				<< " euros" << endl;
		cout << endl << DOUBLE_TAB << TAB << "[1] Borrow a book\n";
		cout << DOUBLE_TAB << TAB << "[2] Manage readers\n";
		cout << DOUBLE_TAB << TAB << "[3] Manage books\n";
		cout << DOUBLE_TAB << TAB << "[4] Logout\n\n" << DOUBLE_TAB << TAB
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
		cout << DOUBLE_TAB << TAB << "Age :" << TAB << supervisor->getAge()
				<< endl;
		cout << DOUBLE_TAB << TAB << "Card :" << TAB << supervisor->getNif()
				<< endl;
		cout << DOUBLE_TAB << TAB << "Phone :" << TAB << supervisor->getPhone()
				<< endl;
		cout << DOUBLE_TAB << TAB << "Email :" << TAB << supervisor->getEmail()
				<< endl;
		cout << DOUBLE_TAB << TAB << "Wage :" << TAB << supervisor->getWage()
				<< " euros" << endl;
		cout << endl << DOUBLE_TAB << TAB << "[1] Display employees team\n";
		cout << DOUBLE_TAB << TAB << "[2] Manage employees\n";
		cout << DOUBLE_TAB << TAB << "[3] Manage supervisors\n";
		cout << DOUBLE_TAB << TAB << "[4] Logout\n\n" << DOUBLE_TAB << TAB
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

void Interface::manageBooks() {
	char input;
	bool exit = false;
	string header = "Manage books";

	do {
		clearScreen();
		displayHeader(header);
		cout << endl << DOUBLE_TAB << TAB << "[1] Create book\n";
		cout << DOUBLE_TAB << TAB << "[2] Edit book\n";
		cout << DOUBLE_TAB << TAB << "[3] Remove book\n";
		cout << DOUBLE_TAB << TAB << "[4] Exit\n\n" << DOUBLE_TAB << TAB
				<< PROMPT_SYMBOL;
		input = getKey();
		switch (input) {
		case '1':
			clearScreen();
			createBook();
			break;
		case '2':
			clearScreen();
			editBook(searchBook(library.getBooks()));
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

void Interface::manageEmployees(Person* supervisor) {
	char input;
	bool exit = false;
	string header = "Manage employees";

	do {
		clearScreen();
		displayHeader(header);
		cout << endl << DOUBLE_TAB << TAB << "[1] Create employee\n";
		cout << DOUBLE_TAB << TAB << "[2] Edit employee\n";
		cout << DOUBLE_TAB << TAB << "[3] Exit\n\n" << DOUBLE_TAB << TAB
				<< PROMPT_SYMBOL;
		input = getKey();
		switch (input) {
		case '1':
			clearScreen();
			createEmployee();
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

void Interface::createBook() {
	string header = "Create Book", authorsDialog = "\t\t\tAdd another author?";
	string newAuthor, newPageNumberStr, newQuota, newIsbn, newTitle;
	stringstream ss;
	unsigned int newPageNumber;

	clearScreen();
	displayHeader(header);

	vector<string> authors = editAuthors();
	while (newQuota == "") {
		cout << DOUBLE_TAB << DOUBLE_TAB << "Quota: ";
		getline(cin, newQuota, '\n');
	}
	while (newPageNumberStr == "" || !is_All_Number(newPageNumberStr)) {
		cout << DOUBLE_TAB << DOUBLE_TAB << "PageNumber: ";
		getline(cin, newPageNumberStr, '\n');
	}
	while (newIsbn == "" || (newIsbn.size() != 13 && newIsbn.size() != 10)) {
		cout << DOUBLE_TAB << DOUBLE_TAB << "Isbn: ";
		getline(cin, newIsbn, '\n');
	}
	while (newTitle == "") {
		cout << DOUBLE_TAB << DOUBLE_TAB << "Title: ";
		getline(cin, newTitle, '\n');

	}
	cout << endl << DOUBLE_TAB << DOUBLE_TAB << "Press S to save"
			<< PROMPT_SYMBOL;
	char ch = cin.get();
	if (ch == 's' || ch == 'S') {
		ss << newPageNumberStr;
		ss >> newPageNumber;
		vector<Book*> books = library.getBooks();
		Book *b = new Book(authors, false, newQuota, newPageNumber, newIsbn,
				newTitle);
		library.addBook(b);
		cout << DOUBLE_TAB << TAB << newTitle << " successfully added.\n";
	} else
		cout << "Book creation cancelled\n";
	pressAnyKey();
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

	while (newName == "" || !is_All_ASCII_Letter(newName)) {
		cout << DOUBLE_TAB << DOUBLE_TAB << "Name: ";
		getline(cin, newName, '\n');
	}
	while (newAgeStr == "" || !!is_All_Number(newAgeStr) || newAgeStr.size() > 2) {
		cout << DOUBLE_TAB << DOUBLE_TAB << "Age: ";
		getline(cin, newAgeStr, '\n');
	}
	while (newPhoneStr == "" || !!is_All_Number(newPhoneStr)
			|| newPhoneStr.size() < 6 || newPhoneStr.size() > 12) {
		cout << DOUBLE_TAB << DOUBLE_TAB << "Phone: ";
		getline(cin, newPhoneStr, '\n');
	}
	while (newEmail == "" || newEmail.size() < 10) {
		cout << DOUBLE_TAB << DOUBLE_TAB << "Mail: ";
		getline(cin, newEmail, '\n');
	}
	while (newNifStr == "" || !!is_All_Number(newNifStr)
			|| newNifStr.size() != 9) {
		cout << DOUBLE_TAB << DOUBLE_TAB << "NIF: ";
		getline(cin, newNifStr, '\n');
	}
	while (newWageStr == "" || !!is_All_Number(newWageStr)) {
		cout << DOUBLE_TAB << DOUBLE_TAB << "Wage: ";
		getline(cin, newWageStr, '\n');
	}

	if (confirmOperation(supervisorDialog))
		supervisor = true;

	cout << endl << DOUBLE_TAB << DOUBLE_TAB << "Press S to save"
			<< PROMPT_SYMBOL;
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
		cout << DOUBLE_TAB << TAB << newName << " successfully added.\n";
	} else
		cout << "Employee creation cancelled\n";
	pressAnyKey();
}

void Interface::createReader() {

}

void Interface::editBook(Book* book) {
	char input;
	bool exit = false;
	string header = "Edit book";
	string newQuota, changesMessage;

	do {
		clearScreen();
		displayHeader(header);
		cout << endl << DOUBLE_TAB << TAB << "[1] Author\n";
		cout << DOUBLE_TAB << TAB << "[2] Quota\n";
		cout << DOUBLE_TAB << TAB << "[3] Page number\n";
		cout << DOUBLE_TAB << TAB << "[4] Isbn\n";
		cout << DOUBLE_TAB << TAB << "[5] Title\n";
		cout << DOUBLE_TAB << TAB << "[6] Exit\n";

		if (changesMessage != ""){
			cout << DOUBLE_TAB << TAB << changesMessage << endl;
			changesMessage = "";
		}
		cout << endl << DOUBLE_TAB << TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			cout << endl;
			book->setAuthors(editAuthors());
			changesMessage = "\n\t\t\tChanges saved successfully";
			break;
		case '2':
			while (newQuota == "") {
				cout << DOUBLE_TAB << DOUBLE_TAB << "Quota: ";
				getline(cin, newQuota, '\n');
			}
			book->setQuota(newQuota);
			changesMessage = "\n\t\t\tChanges saved successfully";
			break;
		case '3':
			//				while (newPageNumberStr == "" || !is_All_Number(newPageNumberStr)) {
			//					cout << DOUBLE_TAB << DOUBLE_TAB << "PageNumber: ";
			//					getline(cin, newPageNumberStr, '\n');
			//				}
			//				while (newIsbn == "" || (newIsbn.size() != 13 && newIsbn.size() != 10)) {
			//					cout << DOUBLE_TAB << DOUBLE_TAB << "Isbn: ";
			//					getline(cin, newIsbn, '\n');
			//				}
			//				while (newTitle == "") {
			//					cout << DOUBLE_TAB << DOUBLE_TAB << "Title: ";
			//					getline(cin, newTitle, '\n');
			//
			//				}
			break;
		case '4':
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
					cout << DOUBLE_TAB << TAB << "[" << z++ << "] "
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
				if (matchQuery(query, title)) {
					cout << DOUBLE_TAB << TAB << "[" << z++ << "] "
							<< ((books[i]->getTitle()).size() > 14 ?
									books[i]->getTitle().substr(0, 14) :
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
		cout << endl << DOUBLE_TAB << DOUBLE_TAB << "[1] Persons\n\n";
		cout << DOUBLE_TAB << DOUBLE_TAB << "[2] Readers\n\n";
		cout << DOUBLE_TAB << DOUBLE_TAB << "[3] Employees\n\n";
		cout << DOUBLE_TAB << DOUBLE_TAB << "[4] Supervisors\n\n";
		cout << DOUBLE_TAB << DOUBLE_TAB << "[5] Books\n\n";
		cout << DOUBLE_TAB << DOUBLE_TAB << "[6] Exit to menu\n\n\n"
				<< DOUBLE_TAB << TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			clearScreen();
			genericDisplay(library.getPersons(), "Persons",
					"Name       Age       Phone       Email       [Card]       Nif       Wage");
			break;
		case '2':
			clearScreen();
			genericDisplay(library.getReaders(), "Readers",
					" Name       Age       Phone       Email       Card");
			break;
		case '3':
			clearScreen();
			genericDisplay(library.getEmployees(), "Employees",
					" Name       Age       Phone       Email       Nif       Wage");
			break;
		case '4':
			clearScreen();
			genericDisplay(library.getSupervisors(), "Supervisors",
					" Name       Age       Phone       Email       Nif       Wage");
			break;
		case '5':
			clearScreen();
			genericDisplay(library.getBooks(), "Books",
					"Authors       Borrowed       Quota       PageNumber       ISBN       Title");
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

	cout << DOUBLE_TAB << TAB << string(33, '#') << endl;
	cout << DOUBLE_TAB << TAB << "#" << DOUBLE_TAB << DOUBLE_TAB << "#" << endl;
	cout << DOUBLE_TAB << TAB << "#" << string(dynSizeLeft, ' ') << header
			<< string(dynSizeRight, ' ') << "#" << endl;
	cout << DOUBLE_TAB << TAB << "#" << DOUBLE_TAB << DOUBLE_TAB << "#" << endl;
	cout << DOUBLE_TAB << TAB << string(33, '#') << endl << endl;
}

bool Interface::confirmOperation(string& query) {
	cout << query << " [y] to confirm";
	char answer = getKey();

	if (answer == 'y' || answer == 'Y')
		return true;
	else
		return false;
}

void Interface::pressAnyKey() {
	cout << " Pressione qualquer tecla para continuar... ";
	getKey();
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
		progress = ceil((18.0 / pLimit) * pCount);
		clearScreen();
		displayHeader(listName);
		cout << string(24, ' ') << "Page " << pCount << " of " << pLimit << " ["
				<< string(progress, '#') << string((18 - progress), ' ') << "]"
				<< string(24, ' ') << endl;
		cout << " " << string(78, '-') << " ";
		cout << string((80 - labels.length()) / 2, ' ') << labels
				<< string((80 - labels.length()) / 2, ' ');
		cout << " " << string(78, '-') << " ";

		while (vLimit < MAX_LINES && i < vecSize && !done) {
			cout << "\n " << vec[i]->print() << "\n"; // maybe overload << operator??
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
		pressAnyKey();
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
		while (newAuthor == "" || !is_All_ASCII_Letter(newAuthor)) {
			cout << DOUBLE_TAB << DOUBLE_TAB << "Author " << i << ": ";
			getline(cin, newAuthor, '\n');
		}
		authors.push_back(newAuthor);
		newAuthor = "";
		if (!confirmOperation(authorsDialog)) {
			cout << endl;
			break;
		}
		cout << endl;
	}
	return authors;
}

