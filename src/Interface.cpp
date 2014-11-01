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
		cout << endl << DOUBLE_TAB << TAB << "[1] Manage employees team\n";
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
		cout << TAB << "[3] Create Supervisor\n\n";
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
	bool confirmAuthor = false;
	bool confirmQuota = false;
	bool confirmPageNumber = false;
	bool confirmIsbn = false;
	bool confirmTitle = false;
	string newauthor;
	unsigned int newpageNumber;
	string newquota;
	string newisbn;
	string newtitle;

	string confirmString;

	while (!exitRequest) {
		while (!confirmAuthor) {
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
					confirmAuthor = false;
				else {
					if (newauthor[0] == '0') {
						exitRequest = true;
						confirmQuota = true;
						confirmPageNumber = true;
						confirmIsbn = true;
						confirmTitle = true;
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
							confirmAuthor = false;
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
									confirmAuthor = true;
								else
									confirmAuthor = false;
							}
						}
					}
				}
			}
		}

		while (!confirmPageNumber) {
			string pageInput;
			cout
					<< "\n Enter the number of Pages or type [0] to return to main menu\n\n > ";
			getline(cin, pageInput);

			if (cin.fail())
				cin.clear();
			else {
				if (pageInput == "" || pageInput == "\n")
					confirmPageNumber = false;
				else {
					if (pageInput[0] == '0') {
						exitRequest = true;
						confirmAuthor = true;
						confirmQuota = true;
						confirmPageNumber = true;
						confirmIsbn = true;
						confirmTitle = true;
						break;
					} else {
						if (CheckAllDigitString(pageInput)) {
							istringstream iss(pageInput);
							iss >> newpageNumber;

							if (pageInput[0] != '0')
								confirmPageNumber = true;
							else
								cout << "\n Wrong Input\n";
						} else
							cout << "\n Wrong Input\n";
					}
				}
			}
		}

		while (!confirmQuota) {

			cout
					<< "\n Enter the Quota or type [0] to return to main menu\n\n > ";
			getline(cin, newquota);

			if (cin.fail())
				cin.clear();
			else {
				if (newquota[0] == '0') {
					exitRequest = true;
					confirmAuthor = true;
					confirmQuota = true;
					confirmPageNumber = true;
					confirmIsbn = true;
					confirmTitle = true;
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
								confirmQuota = true;
							else
								confirmQuota = false;
						}
					}
				}
			}
		}

		while (!confirmIsbn) {

			cout << " Enter new ISB or type [0] to return to main menu\n\n > ";
			getline(cin, newisbn);

			if (cin.fail())
				cin.clear();
			else {
				if (newisbn == "" || newisbn == "\n")
					confirmIsbn = false;
				else {
					if (newisbn[0] == '0') {
						exitRequest = true;
						confirmQuota = true;
						confirmPageNumber = true;
						confirmIsbn = true;
						confirmTitle = true;
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
									confirmIsbn = true;
								else
									confirmIsbn = false;
							}
						}
					}
				}
			}
		}
		while (!confirmTitle) {

			cout
					<< " Enter new Title or type [0] to return to main menu\n\n > ";
			getline(cin, newtitle);

			if (cin.fail())
				cin.clear();
			else {
				if (newtitle == "" || newtitle == "\n")
					confirmTitle = false;
				else {
					if (newtitle[0] == '0') {
						exitRequest = true;
						confirmQuota = true;
						confirmPageNumber = true;
						confirmIsbn = true;
						confirmTitle = true;
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
									confirmTitle = true;
								else
									confirmTitle = false;
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

void Interface::createEmployees() {
	string confirmDialog =
			" Do you want to create a new employee with this information?";
	bool exitRequest = false;
	bool confirmName = false;
	bool confirmAge = false;
	bool confirmPhone = false;
	bool confirmEmail = false;
	bool confirmNif = false;
	bool confirmWage = false;
	string newname;
	unsigned int newage;
	unsigned int newphone;
	string newemail;
	unsigned int newnif;
	unsigned int newwage;

	string confirmString;

	while (!exitRequest) {
		while (!confirmName) {
			clearScreen();

			cout << "\n " << string(30, '#') << "\n";
			cout << " #" << string(28, ' ') << "#\n";
			cout << " #" << string(5, ' ') << "Create new Employee"
					<< string(5, ' ') << "#\n";
			cout << " #" << string(28, ' ') << "#\n";
			cout << " " << string(30, '#') << "\n\n\n";
			cout
					<< " Enter new Employee name or type [0] to return to main menu\n\n > ";
			getline(cin, newname);

			if (cin.fail())
				cin.clear();
			else {
				if (newname == "" || newname == "\n")
					confirmName = false;
				else {
					if (newname[0] == '0') {
						exitRequest = true;
						confirmAge = true;
						confirmPhone = true;
						confirmEmail = true;
						confirmNif = true;
						confirmWage = true;
						break;
					}

					else {
						if (newname.size() > 20) {
							newname = newname.substr(0, 20);
						}
						if (int(newname[0]) < 65
								|| ((int(newname[0]) > 90)
										&& (int(newname[0]) < 97))
								|| int(newname[0]) > 122) {
							cout
									<< "\n Invalid input. The first character must be a letter\n";
							confirmName = false;
						}

						else {
							cout << "\n Your Name used in display is: "
									<< newname
									<< "\n\n Is it correct? [yes to confirm]\n\n > ";
							getline(cin, confirmString);

							if (cin.fail()) {
								cin.clear();
							} else {
								if (confirmString == "yes"
										|| confirmString == "YES")
									confirmName = true;
								else
									confirmName = false;
							}
						}
					}
				}
			}
		}

		while (!confirmAge) {
			string ageInput;
			cout << "\n Enter age or type [0] to return to main menu\n\n > ";
			getline(cin, ageInput);

			if (cin.fail())
				cin.clear();
			else {
				if (ageInput == "" || ageInput == "\n")
					confirmAge = false;
				else {
					if (ageInput[0] == '0') {
						exitRequest = true;
						confirmName = true;
						confirmPhone = true;
						confirmEmail = true;
						confirmNif = true;
						confirmWage = true;
						break;
					} else {
						if (CheckAllDigitString(ageInput)
								&& ageInput.size() < 4) {
							istringstream iss(ageInput);
							iss >> newage;

							if (ageInput[0] != '0')
								confirmAge = true;
							else
								cout << "\n Wrong Input\n";
						} else
							cout << "\n Wrong Input\n";
					}
				}
			}
		}

		while (!confirmPhone) {
			string phoneInput;
			cout
					<< "\n Enter the phonenumber or type [0] to return to main menu\n\n > ";
			getline(cin, phoneInput);

			if (cin.fail())
				cin.clear();
			else {
				if (phoneInput == "" || phoneInput == "\n")
					confirmPhone = false;
				else {
					if (phoneInput[0] == '0') {
						exitRequest = true;
						confirmName = true;
						confirmAge = true;
						confirmEmail = true;
						confirmNif = true;
						confirmWage = true;
						break;
					} else {
						if (CheckAllDigitString(phoneInput)) {
							istringstream iss(phoneInput);
							iss >> newphone;

							if (phoneInput[0] != '0')
								confirmPhone = true;
							else
								cout << "\n Wrong Input\n";
						} else
							cout << "\n Wrong Input\n";
					}
				}
			}
		}

		while (!confirmEmail) {

			cout << " Enter email or type [0] to return to main menu\n\n > ";
			getline(cin, newemail);

			if (cin.fail())
				cin.clear();
			else {
				if (newemail == "" || newemail == "\n")
					confirmEmail = false;
				else {
					if (newemail[0] == '0') {
						exitRequest = true;
						confirmName = true;
						confirmAge = true;
						confirmPhone = true;
						confirmNif = true;
						confirmWage = true;
						break;
					}

					else {
						if (newemail.size() > 10) {
							newemail = newemail.substr(0, 10);
						} else {
							cout << "\n Your email used in display is: "
									<< newemail
									<< "\n\n Is it correct? [yes to confirm]\n\n > ";
							getline(cin, confirmString);

							if (cin.fail())
								cin.clear();
							else {
								if (confirmString == "yes"
										|| confirmString == "YES")
									confirmEmail = true;
								else
									confirmEmail = false;
							}
						}
					}
				}
			}
		}
		while (!confirmNif) {
			string nifInput;
			cout << " Enter your NIF or type [0] to return to main menu\n\n > ";
			getline(cin, nifInput);

			if (cin.fail())
				cin.clear();
			else {
				if (nifInput == "" || nifInput == "\n")
					confirmNif = false;
				else {
					if (nifInput[0] == '0') {
						exitRequest = true;
						confirmName = true;
						confirmAge = true;
						confirmPhone = true;
						confirmEmail = true;
						confirmWage = true;
						break;
					} else {
						if (CheckAllDigitString(nifInput)
								&& nifInput.size() == 9) {
							istringstream iss(nifInput);
							iss >> newnif;

							if (nifInput[0] != '0')
								confirmAge = true;
							else
								cout << "\n Wrong Input\n";
						} else
							cout << "\n Wrong Input\n";
					}
				}
			}
		}
		while (!confirmWage) {
			string wageInput;
			cout << "\n Enter wage or type [0] to return to main menu\n\n > ";
			getline(cin, wageInput);

			if (cin.fail())
				cin.clear();
			else {
				if (wageInput == "" || wageInput == "\n")
					confirmWage = false;
				else {
					if (wageInput[0] == '0') {
						exitRequest = true;
						confirmName = true;
						confirmAge = true;
						confirmPhone = true;
						confirmEmail = true;
						confirmNif = true;
						break;
					} else {
						if (CheckAllDigitString(wageInput)) {
							istringstream iss(wageInput);
							iss >> newwage;

							if (wageInput[0] != '0')
								confirmWage = true;
							else
								cout << "\n Wrong Input\n";
						} else
							cout << "\n Wrong Input\n";
					}
				}
			}
		}

		if (!exitRequest) {
			cout << "\n\n " << string(38, '#') << "\n";
			cout << " #" << string(36, ' ') << "#\n";
			cout << " #" << string(5, ' ') << "New Employee data"
					<< string(18, ' ') << "#\n";
			cout << " #" << string(36, ' ') << "#\n";
			cout << " #" << string(5, ' ') << "Name: " << newname
					<< string(25 - newname.size(), ' ') << "#\n";
			cout << " #" << string(5, ' ') << "age: " << ConvertToString(newage)
					<< string(26 - ConvertToString(newage).size(), ' ')
					<< "#\n";
			cout << " #" << string(5, ' ') << "phone: "
					<< ConvertToString(newphone)
					<< string(26 - ConvertToString(newphone).size(), ' ')
					<< "#\n";
			cout << " #" << string(5, ' ') << "email: " << newemail
					<< string(25 - newemail.size(), ' ') << "#\n";
			cout << " #" << string(5, ' ') << "NIF: " << ConvertToString(newnif)
					<< string(26 - ConvertToString(newnif).size(), ' ')
					<< "#\n";
			cout << " #" << string(5, ' ') << "WAGE: "
					<< ConvertToString(newwage)
					<< string(26 - ConvertToString(newwage).size(), ' ')
					<< "#\n";
			cout << " #" << string(36, ' ') << "#\n";
			cout << " " << string(38, '#') << "\n\n\n";

			if (confirmOperation(confirmDialog)) {
				exitRequest = false;
				cout << "\n\n Writing to employee.csv file\n\n";
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
			vector<Person*> empl = library.getEmployees(); //ver melhor isto
			Employee *s0 = new Employee(newname, newage, newphone, newemail,
					newnif, newwage);
			library.addPerson(s0);

			exitRequest = true;
			cout << " Press any key to continue...";
			if (getchar() != '\n')
				cin.ignore(1024, '\n');
		}
	}

}

void Interface::createSupervisors() {

}

void Interface::createReaders() {

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
