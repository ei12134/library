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
			createBook(); //a alterar futuramente
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

void Interface::create() {
	char input;
	string exitDialog = "Exit the program?";
	string header = "Create";
	bool exit = false;

	do {
		clearScreen();
		displayHeader(header);
		cout << endl << TAB << "[1] Create Person\n\n";
		cout << TAB << "[2] Create Book\n\n";
		cout << TAB << "[3] Quit\n\n\n" << TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			createPerson();
			break;
		case '2':
			createBook();
			break;
		case '3':
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

void Interface::createPerson() {
	char input;
	string exitDialog = "Exit the program?";
	string header = "Create Person";
	bool exit = false;

	do {
		clearScreen();
		displayHeader(header);
		cout << endl << TAB << "[1] Create Reader\n\n";
		cout << TAB << "[2] Create Employee\n\n";
		cout << TAB << "[3] Create Supervisor\n\n";
		cout << TAB << "[4] Quit\n\n\n" << TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			createReader();
			break;
		case '2':
			createEmployee();
			break;
		case '3':
			createSupervisor();
			break;
		case '4':
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

bool CheckAllDigitString(string stringToCheck) {
	bool allDigitString = true;

	if (stringToCheck.size() == 0)
		allDigitString = false;

	for (unsigned int i = 0; i < stringToCheck.size(); i++) {
		if (int(stringToCheck[i]) < 0 || int(stringToCheck[i] > 127)) {
			allDigitString = false;
			break;
		}

		if (!isdigit(stringToCheck[i])) {
			allDigitString = false;
			break;
		}
	}

	return allDigitString;
}

string ConvertToString(unsigned int numberToConvert) {
	string newString;

	ostringstream tmpString;
	tmpString << numberToConvert;
	newString = tmpString.str();

	return newString;
}

void PressAnyKey() {
	cout << " Pressione qualquer tecla para continuar... ";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}

void Interface::createBook() {

	string header = "Create Book";
	string newAuthor, newPageNumber, newQuota, newIsbn, newTitle;
	stringstream ss;
	unsigned int newPageNumbe;
	bool valid = false;
	char ch;
	clearScreen();
	displayHeader(header);

	while (newAuthor == "" || !is_All_ASCII_Letter(newAuthor)) {
		cout << " Author: ";
		getline(cin, newAuthor, '\n');
	}
	while (newQuota == "") {
		cout << " Quota: ";
		getline(cin, newQuota, '\n');
	}
	while (newPageNumber == "" || !CheckAllDigitString(newPageNumber)) {
		cout << " PageNumber: ";
		getline(cin, newPageNumber, '\n');
	}
	while (newIsbn == "") {
		cout << " Isbn: ";
		getline(cin, newIsbn, '\n');
	}

	while (newTitle == "") {
		cout << " Title: ";
		getline(cin, newTitle, '\n');

	}
	cout << "Press S to save" << endl;
	ch = cin.get();
	if (ch == 's' || ch == 'S') {
		valid = true;
	}
	if (valid) {
		ss << newPageNumber;
		ss >> newPageNumbe;
		vector<Book*> books = library.getBooks();
		Book *b = new Book(newAuthor, false, newQuota, newPageNumbe, newIsbn,
				newTitle);
		library.addBook(b);
		cout << " " << newAuthor << " adicionado com sucesso.\n";
	}
	PressAnyKey();
}

void Interface::createEmployee() {
	string header = "Create Employee";
	string newName, newAge, newPhone, newEmail, newNif, newWage;
	stringstream ss;
	unsigned int newAg, newPhon, newNi, newWag;
	bool valid = false;
	char ch;
	clearScreen();
	displayHeader(header);

	while (newName == "" || !is_All_ASCII_Letter(newName)) {
		cout << " Name: ";
		getline(cin, newName, '\n');
	}
	while (newAge == "" || !CheckAllDigitString(newAge) || newAge.size() > 2) {
		cout << " Age: ";
		getline(cin, newAge, '\n');
	}
	while (newPhone == "" || !CheckAllDigitString(newPhone)
			|| newPhone.size() < 6 || newPhone.size() > 12) {
		cout << " Phone: ";
		getline(cin, newPhone, '\n');
	}
	while (newEmail == "" || newEmail.size() < 10) {
		cout << " Mail: ";
		getline(cin, newEmail, '\n');
	}
	while (newNif == "" || !CheckAllDigitString(newNif) || newNif.size() != 9) {
		cout << " NIF: ";
		getline(cin, newNif, '\n');
	}
	while (newWage == "" || !CheckAllDigitString(newWage)) {
		cout << " Wage: ";
		getline(cin, newWage, '\n');
	}
	cout << "Press S to save" << endl;
	ch = cin.get();
	if (ch == 's' || ch == 'S') {
		valid = true;
	}
	if (valid) {
		ss << newAge;
		ss >> newAg;
		ss << newPhone;
		ss >> newPhon;
		ss << newNif;
		ss >> newNi;
		ss << newWage;
		ss >> newWag;

		vector<Person*> empl = library.getEmployees();
		Employee *s0 = new Employee(newName, newAg, newPhon, newEmail, newNi,
				newWag, false);
		library.addPerson(s0);
		cout << " " << newName << " adicionado com sucesso.\n";
	}
	PressAnyKey();
}

void Interface::createSupervisor() {

}

void Interface::createReader() {

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
					"Author		Borrowed	Quota	PageNumber	ISBN	Title");
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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
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
