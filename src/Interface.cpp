#include "Interface.h"

Interface::Interface() {
	this->library = Library();
	menu();
}

Interface::~Interface() {
}

void Interface::menu() {
	char input;
	string exitDialog = "Exit the program?";
	string header = "Library";
	bool exit = false;

	do {
		clearScreen();
		displayHeader(header);
		cout << endl << TAB << "[1] Login\n\n";
		cout << TAB << "[2] Display\n\n";
		cout << TAB << "[3] Search\n\n";
		cout << TAB << "[4] Create\n\n";
		cout << TAB << "[5] Quit\n\n\n" << SYMBOL_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			searchPerson();
			break;
		case '2':
			displayMenu();
			break;

		case '4':
			create();
			break;
		case '5':
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

void Interface::readerMenu(Person* reader) {
	char input;
	bool exit = false;
	string header = reader->getName();

	do {
		clearScreen();
		displayHeader(header);

		cout << "\t\t\tAge :\t" << reader->getAge() << endl;
		cout << "\t\t\tCard :\t" << reader->getCard() << endl;
		cout << "\t\t\tPhone :\t" << reader->getPhone() << endl;
		cout << "\t\t\tEmail :\t" << reader->getEmail() << endl;

		cout << endl << TAB << "[1] Borrows\n\n";
		cout << TAB << "[2] History\n\n";
		cout << TAB << "[3] Return to main menu\n\n\n" << SYMBOL_TAB
				<< PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			break;
		case '2':
			break;
		case '3':
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
		cout << TAB << "[3] Quit\n\n\n" << SYMBOL_TAB << PROMPT_SYMBOL;

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
		cout << TAB << "[3] Create Superviser\n\n";
		cout << TAB << "[4] Quit\n\n\n" << SYMBOL_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			createReaders();
			break;
		case '2':
			createEmployees();
			break;

		case '3':
			createSupervisors();
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

void Interface::createBook() {
	string confirmDialog =
			" Do you want to create a new book with this information?";
	bool exitRequest = false;
	bool confirmauthor = false;
	bool confirmquota = false;
	bool confirmpageNumber = false;
	bool confirmisbn = false;
	bool confirmtitle = false;
	string newauthor;
	unsigned int newpageNumber;
	string newquota;
	string newisbn;
	string newtitle;

	string confirmString;

	while (!exitRequest) {
		while (!confirmauthor) {
			clearScreen();

			cout << "\n " << string(30, '#') << "\n";
			cout << " #" << string(28, ' ') << "#\n";
			cout << " #" << string(5, ' ') << "Create new Book"
					<< string(5, ' ') << "#\n";
			cout << " #" << string(28, ' ') << "#\n";
			cout << " " << string(30, '#') << "\n\n\n";
			cout
					<< " Enter new Author or type [0] to return to main menu\n\n > ";
			getline(cin, newauthor);

			if (cin.fail())
				cin.clear();
			else {
				if (newauthor == "" || newauthor == "\n")
					confirmauthor = false;
				else {
					if (newauthor[0] == '0') {
						exitRequest = true;
						confirmquota = true;
						confirmpageNumber = true;
						confirmisbn = true;
						confirmtitle = true;
						break;
					}

					else {
						if (newauthor.size() > 20) {
							newauthor = newauthor.substr(0, 20);
						}
						if (int(newauthor[0]) < 65
								|| ((int(newauthor[0]) > 90)
										&& (int(newauthor[0]) < 97))
								|| int(newauthor[0]) > 122) {
							cout
									<< "\n Invalid input. The first character must be a letter\n";
							confirmauthor = false;
						}

						else {
							cout << "\n Your Author used in display is: "
									<< newauthor
									<< "\n\n Is it correct? [yes to confirm]\n\n > ";
							getline(cin, confirmString);

							if (cin.fail()) {
								cin.clear();
							} else {
								if (confirmString == "yes"
										|| confirmString == "YES")
									confirmauthor = true;
								else
									confirmauthor = false;
							}
						}
					}
				}
			}
		}

		while (!confirmpageNumber) {
			string pageInput;
			cout
					<< "\n Enter the number of Pages or type [0] to return to main menu\n\n > ";
			getline(cin, pageInput);

			if (cin.fail())
				cin.clear();
			else {
				if (pageInput == "" || pageInput == "\n")
					confirmpageNumber = false;
				else {
					if (pageInput[0] == '0') {
						exitRequest = true;
						confirmauthor = true;
						confirmquota = true;
						confirmpageNumber = true;
						confirmisbn = true;
						confirmtitle = true;
						break;
					} else {
						if (CheckAllDigitString(pageInput)) {
							istringstream iss(pageInput);
							iss >> newpageNumber;

							if (pageInput[0] != '0')
								confirmpageNumber = true;
							else
								cout << "\n Wrong Input\n";
						} else
							cout << "\n Wrong Input\n";
					}
				}
			}
		}

		while (!confirmquota) {

			cout
					<< "\n Enter the Quota or type [0] to return to main menu\n\n > ";
			getline(cin, newquota);

			if (cin.fail())
				cin.clear();
			else {
				if (newquota[0] == '0') {
					exitRequest = true;
					confirmauthor = true;
					confirmquota = true;
					confirmpageNumber = true;
					confirmisbn = true;
					confirmtitle = true;
					break;
				} else {
					if (newquota.size() > 10) {
						newquota = newquota.substr(0, 10);
					} else {
						cout << "\n Your Quota used in display is: " << newquota
								<< "\n\n Is it correct? [yes to confirm]\n\n > ";
						getline(cin, confirmString);

						if (cin.fail())
							cin.clear();
						else {
							if (confirmString == "yes"
									|| confirmString == "YES")
								confirmquota = true;
							else
								confirmquota = false;
						}
					}
				}
			}
		}

		while (!confirmisbn) {

			cout << " Enter new ISB or type [0] to return to main menu\n\n > ";
			getline(cin, newisbn);

			if (cin.fail())
				cin.clear();
			else {
				if (newisbn == "" || newisbn == "\n")
					confirmisbn = false;
				else {
					if (newisbn[0] == '0') {
						exitRequest = true;
						confirmquota = true;
						confirmpageNumber = true;
						confirmisbn = true;
						confirmtitle = true;
						break;
					}

					else {
						if (newisbn.size() > 10) {
							newisbn = newisbn.substr(0, 10);
						} else {
							cout << "\n Your ISBN used in display is: "
									<< newisbn
									<< "\n\n Is it correct? [yes to confirm]\n\n > ";
							getline(cin, confirmString);

							if (cin.fail())
								cin.clear();
							else {
								if (confirmString == "yes"
										|| confirmString == "YES")
									confirmisbn = true;
								else
									confirmisbn = false;
							}
						}
					}
				}
			}
		}
		while (!confirmtitle) {

			cout
					<< " Enter new Title or type [0] to return to main menu\n\n > ";
			getline(cin, newtitle);

			if (cin.fail())
				cin.clear();
			else {
				if (newtitle == "" || newtitle == "\n")
					confirmtitle = false;
				else {
					if (newtitle[0] == '0') {
						exitRequest = true;
						confirmquota = true;
						confirmpageNumber = true;
						confirmisbn = true;
						confirmtitle = true;
						break;
					}

					else {
						if (newtitle.size() > 20) {
							newtitle = newisbn.substr(0, 20);
						} else {
							cout << "\n Your Title used in display is: "
									<< newtitle
									<< "\n\n Is it correct? [yes to confirm]\n\n > ";
							getline(cin, confirmString);

							if (cin.fail())
								cin.clear();
							else {
								if (confirmString == "yes"
										|| confirmString == "YES")
									confirmtitle = true;
								else
									confirmtitle = false;
							}
						}
					}
				}
			}
		}

		if (!exitRequest) {
			cout << "\n\n " << string(38, '#') << "\n";
			cout << " #" << string(36, ' ') << "#\n";
			cout << " #" << string(5, ' ') << "New Book data" << string(18, ' ')
					<< "#\n";
			cout << " #" << string(36, ' ') << "#\n";
			cout << " #" << string(5, ' ') << "Author: " << newauthor
					<< string(25 - newauthor.size(), ' ') << "#\n";
			cout << " #" << string(5, ' ') << "Paginas: "
					<< ConvertToString(newpageNumber)
					<< string(26 - ConvertToString(newpageNumber).size(), ' ')
					<< "#\n";
			cout << " #" << string(5, ' ') << "Quota: " << newquota
					<< string(25 - newquota.size(), ' ') << "#\n";
			cout << " #" << string(5, ' ') << "ISB: " << newisbn
					<< string(25 - newisbn.size(), ' ') << "#\n";
			cout << " #" << string(5, ' ') << "Title: " << newtitle
					<< string(25 - newtitle.size(), ' ') << "#\n";
			cout << " #" << string(36, ' ') << "#\n";
			cout << " " << string(38, '#') << "\n\n\n";

			if (confirmOperation(confirmDialog)) {
				exitRequest = false;
				cout << "\n\n Writing to books.csv file\n\n";
			} else {
				exitRequest = true;
				cout
						<< "\n\n Operation canceled\n Press any key to continue...";
				getchar();
				/*if ( getchar() != '\n' )
				 cin.clear( 1024,'\n' );*/
			}
		}

		if (!exitRequest) {
			vector<Book*> books = library.getBooks();
			Book *v0 = new Book(newauthor, false, newquota, newpageNumber,
					newisbn, newtitle);
			library.addBook(v0);

			exitRequest = true;
			cout << " Press any key to continue...";
			if (getchar() != '\n')
				cin.ignore(1024, '\n');
		}
	}
}
//" Name       Age       Phone       Email       Nif       Wage");

void Interface::createEmployees() {

}

void Interface::createSupervisors() {

}

void Interface::createReaders() {

}

void Interface::searchPerson() {
	string query;
	string header = "Login";
	bool exit = false;
	int key;
	vector<Person*> persons = library.getPersons();
	vector<Person*> matches;
	do {
		clearScreen();
		displayHeader(header);
		cout << endl << endl;
		matches.clear();
		if (query.size() > 0) {
			for (size_t i = 0, z = 1; i < persons.size() && z < 6; i++) {
				string name = persons[i]->getName();
				if (matchQuery(query, name)) {
					cout << " [" << z++ << "] " << persons[i]->getName() << "\t"
							<< persons[i]->printType() << endl << endl;
					matches.push_back(persons[i]);
				}
			}
		}

		cout << "\n Enter person name [ESC to exit]\n\n" << SYMBOL_SHORT_TAB
				<< PROMPT_SYMBOL << query;

		key = getKey();

		switch (key) {
		case 8:
			if (query.length() > 0)
				query.erase(query.end() - 1);
			break;
		case 1:
			if (matches.size() > 0) {
				exit = true;
				readerMenu(matches[0]);
			}
			break;
		case 13:		// ENTER
			if (matches.size() > 0) {
				exit = true;
				readerMenu(matches[0]);
			}
			break;
		case 27:		// ESC
			exit = true;
			break;
		case 83:		// DELETE - works only in Windows
			query.clear();
			break;
		default:
			query += char(key);
			break;
		}
	} while (!exit);
}

void Interface::displayMenu() {
	char input;
	bool exit = false;
	string header = "Display";

	do {
		clearScreen();
		displayHeader(header);
		cout << endl << TAB << "[1] All\n\n";
		cout << TAB << "[2] Readers\n\n";
		cout << TAB << "[3] Employees\n\n";
		cout << TAB << "[4] Supervisors\n\n";
		cout << TAB << "[5] Book\n\n";
		cout << TAB << "[6] Exit to menu\n\n\n" << SYMBOL_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			clearScreen();
			genericDisplay(library.getPersons(), "All",
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
		default:
			break;
		}
	} while (!exit);
}

void Interface::clearScreen() {
	system(CLEAR);
}

void Interface::displayHeader(string& header) {
	unsigned int size = header.size(), dynsize = ceil((34 - size) / 2),
			dynsize2 = dynsize;

	if ((dynsize * 2 + size + 2) < 36)
		dynsize2++;

	cout << endl << string(22, ' ') << string(36, '#') << string(22, ' ');
	cout << string(22, ' ') << "#" << string(34, ' ') << "#" << string(22, ' ');
	cout << string(22, ' ') << "#" << string(dynsize, ' ') << header
			<< string(dynsize2, ' ') << "#" << string(22, ' ');
	cout << string(22, ' ') << "#" << string(34, ' ') << "#" << string(22, ' ');
	cout << string(22, ' ') << string(36, '#') << string(22, ' ') << endl;
}

bool Interface::confirmOperation(string& query) {
	cout << query << " [y] to confirm ";
	char answer = getKey();

	if (answer == 'y' || answer == 'Y')
		return true;
	else
		return false;
}

void Interface::pressAnyKey() {
	cout << " Press any key to continue...";
	getKey();
}

template<typename T>
void Interface::genericDisplay(vector<T> vec, string listName, string labels) {
	unsigned int vecSize = vec.size(), pCount = 1, vLimit = 0, i = 0, progress;
	float pLimit = ceil(static_cast<float>(vecSize) / MAX_LINES);
	bool done = false;
	string vLimitMsg = " [q] to interrupt or any other key to continue...";
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
				if (ch == 'q')
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

bool Interface::matchQuery(const string & q, const string & n) {
	if (q.size() == 0)
		return false;
	for (size_t i = 0; i < q.size() && i < n.size(); i++) {
		if (tolower(q[i]) != tolower(n[i]))
			return false;
	}
	return true;
}

bool Interface::is_Number(const int & c) {
	return (c < 57) || (c > 48);
}

bool Interface::is_NON_ASCII_Letter(const int & c) {
	return ((c < 65) || (c > 122) || (c > 90 && c < 97));
}

//bool Interface::is_All_ASCII_Letter(const string& s) {
//	return find_if(s.begin(), s.end(), is_NON_ASCII_Letter) == s.end();
//}
