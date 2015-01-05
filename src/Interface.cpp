#include "Interface.h"

Interface::Interface() {
	setConsole();
	menu();
}

Interface::~Interface() {
	restoreConsole();
}

void Interface::menu() {
	char input;
	bool exit = false;
	const size_t menuCmdsSize = 4;
	string menuCmds[menuCmdsSize] = { "Login", "Display", "Search\n", "Quit" };
	string spacing = string((80 - menuCmds[1].size() - 4) / 2, ' ');
	string exitDialog = "Quit?";
	string header = "Library";

	do {
		clearScreen();
		displayHeader(header);

		for (size_t i = 0; i < menuCmdsSize; i++)
			cmdMsg(spacing, (i + 1), menuCmds[i], FGGREEN_BGBLACK, 1);

		cout << endl << spacing << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			if (library.getSupervisors().size() != 0)
				dispatchPerson(searchPerson(library.getPersons(), "Login"));
			else
				createEmployee();
			break;
		case '2':
			displayMenu();
			break;
		case '3':
			searchMenu();
			break;
		case '4':
			if (confirmOperation(exitDialog))
				exit = true;
			break;
		case ESCAPE_KEY:
			if (confirmOperation(exitDialog))
				exit = true;
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

void Interface::displayMenu() {
	char input;
	bool exit = false;
	const size_t displayMenuSize = 9;
	string displayMenu[displayMenuSize] = { "Persons", "Readers", "Employees",
			"Supervisors", "Books", "Books BST", "Inactive readers",
			"Requests queue\n", "Exit" };
	string header = "Display";
	vector<string> persStr;
	persStr.push_back("name");
	persStr.push_back("age");
	persStr.push_back("phone");
	persStr.push_back("email");
	vector<string> readerStr = persStr;
	readerStr.push_back("card");
	vector<string> emplStr = persStr;
	vector<string> supStr = persStr;
	vector<string> booksStr;
	booksStr.push_back("title");
	booksStr.push_back("author");
	booksStr.push_back("year");
	booksStr.push_back("status");

	do {
		clearScreen();
		displayHeader(header);
		int sortFunc = 0;

		for (size_t i = 0; i < displayMenuSize; i++)
			cmdMsg(FOUR_TABS, (i + 1), displayMenu[i], FGGREEN_BGBLACK, 1);

		cout << endl << FOUR_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			while (displayContainer(library.getSortedPrint(PERSON, sortFunc),
					"Persons", "\tName\t\tAge\tPhone\t\tEmail\t\t\t[Id]",
					persStr[sortFunc]) == -1) {
				sortFunc++;
				sortFunc %= persStr.size();
			}
			break;
		case '2':
			while (displayContainer(library.getSortedPrint(READER, sortFunc),
					"Readers", "\tName\t\tAge\tPhone\t\tEmail\t\t\tCard",
					readerStr[sortFunc]) == -1) {
				sortFunc++;
				sortFunc %= readerStr.size();
			}
			break;
		case '3':
			while (displayContainer(library.getSortedPrint(EMPLOYEE, sortFunc),
					"Employees", "\tName\t\tAge\tPhone\t\tEmail\t\t\tNif",
					emplStr[sortFunc]) == -1) {
				sortFunc++;
				sortFunc %= emplStr.size();
			}
			break;
		case '4':
			while (displayContainer(
					library.getSortedPrint(SUPERVISOR, sortFunc), "Supervisors",
					"\tName\t\tAge\tPhone\t\tEmail\t\t\tNif", supStr[sortFunc])
					== -1) {
				sortFunc++;
				sortFunc %= supStr.size();
			}
			break;
		case '5':
			while (displayContainer(library.getSortedPrint(BOOK, sortFunc),
					"Books", "\tTitle\t\t\tAuthors\t\t\tYear\tStatus",
					booksStr[sortFunc]) == -1) {
				sortFunc++;
				sortFunc %= booksStr.size();
			}
			break;
		case '6':
			displayContainer(library.getBooksTreePrint(), "Books BST",
					"\tTitle\t\t\tAuthors\t\t\tYear\tStatus", "");
			break;
		case '7':
			displayContainer(library.getHashTablePrint(), "Inactive Readers",
					"\tName\t\tAge\tPhone\t\tEmail\t\t\tCard", "");
			break;
		case '8':
			displayContainer(library.getPriorityQueuePrint(), "Requests queue",
					"\tName\t\tAge\tTitle\t\t\t\tDate", "");
			break;
		case '9':
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

void Interface::searchMenu() {
	int input;
	bool exit = false;
	const size_t searchMenuSize = 4;
	string searchMenu[searchMenuSize] = { "By edition year", "By title",
			"By author\n", "Exit" };
	string header = "Search books BST";
	string query;
	vector<string> booksStr;
	booksStr.push_back("title");
	booksStr.push_back("author");
	booksStr.push_back("year");
	booksStr.push_back("status");
	size_t selected = 0;

	do {
		clearScreen();
		displayHeader(header);

		stringstream ss;
		unsigned int year;

		for (size_t i = 0; i < searchMenuSize; i++)
			colorMsg(FOUR_TABS, searchMenu[i],
					(selected == i ? FGBLACK_BGGREEN : FGGREEN_BGBLACK), 1);

		cout << endl << endl << TWO_TABS
				<< "Select search method and enter query ";
		colorMsg("", "[ESC to exit]", FGWHITE_BGBLACK, 2);
		cout << TWO_TABS << PROMPT_SYMBOL;
		colorMsg("", query, FGWHITE_BGBLACK, 0);

		input = getKey();

		switch (input) {
		case 0:
			break;
		case RETURN_KEY:
			if (selected == searchMenuSize - 1)
				exit = true;
			else if (query.size() > 0) {
				if (is_All_Number(query) && selected == 0) {
					ss << query;
					ss >> year;
					ss.clear();
					displayContainer(library.getBooksTreePrintByYear(year),
							"Books BST",
							"\tTitle\t\t\tAuthors\t\t\tYear\tStatus", "");
				} else if (selected == 1) {
					displayContainer(library.getBooksTreePrintByTitle(query),
							"Books BST",
							"\tTitle\t\t\tAuthors\t\t\tYear\tStatus", "");
				} else if (is_All_ASCII_Letter(query) && selected == 2) {
					displayContainer(library.getBooksTreePrintByAuthor(query),
							"Books BST",
							"\tTitle\t\t\tAuthors\t\t\tYear\tStatus", "");
				}
			}
			break;
		case BACKSPACE_KEY:
			if (query.length() > 0)
				query.erase(query.end() - 1);
			break;
		case ESCAPE_KEY:
			exit = true;
			break;
		case DELETE_KEY:
			query.clear();
			break;
		case ARROW_DOWN:
			selected++;
			selected %= searchMenuSize;
			break;
		case ARROW_UP:
			if (selected < 1)
				selected = searchMenuSize - 1;
			else
				selected--;
			break;
		default:
			query += char(input);
			break;
		}
	} while (!exit);
}

void Interface::readerMenu(Person* reader) {
	char input;
	bool exit = false;
	const size_t cmdsSize = 4;
	string cmds[cmdsSize] = { "Display borrows", "Display requests",
			"Borrow history\n", "Logout\n" };
	string header;
	string infMsg;
	vector<Borrow*> previousBorrows;
	do {
		header = "Reader" + string(headerSpacing, ' ') + reader->getName();
		clearScreen();
		displayHeader(header);
		colorMsg(THREE_TABS + HALF_TAB, "Age: ", FGWHITE_BGBLACK, 0);
		cout << reader->getAge() << " years" << endl;
		colorMsg(THREE_TABS + HALF_TAB, "Card: ", FGWHITE_BGBLACK, 0);
		cout << +reader->getCard() << endl;
		colorMsg(THREE_TABS + HALF_TAB, "Phone: ", FGWHITE_BGBLACK, 0);
		cout << reader->getPhone() << endl;
		colorMsg(THREE_TABS + HALF_TAB, "Email: ", FGWHITE_BGBLACK, 0);
		cout << reader->getEmail() << endl << endl;
		for (size_t i = 0; i < cmdsSize; i++)
			cmdMsg(THREE_TABS + HALF_TAB, (i + 1), cmds[i], FGGREEN_BGBLACK, 1);
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
			displayContainer(library.getPriorityQueuePrintByReader(reader),
					"Requests queue", "\tName\t\tAge\tTitle\t\t\t\tDate", "");
			break;
		case '3':
			previousBorrows = library.getReaderBorrows(reader);
			displayContainer(library.getContainerPtrPrint(previousBorrows),
					"Borrow history", "\tTitle\t\t\t\tBorrowed\tReturned\tID",
					"");
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

void Interface::employeeMenu(Person* employee) {
	char input;
	bool exit = false;
	const size_t cmdsSize = 5;
	string cmds[cmdsSize] = { "Borrow a book", "Manage books", "Manage readers",
			"Manage requests\n", "Logout\n" };
	string header;

	do {
		header = "Employee" + string(headerSpacing, ' ') + employee->getName();
		clearScreen();
		displayHeader(header);

		colorMsg(THREE_TABS + HALF_TAB, "Age: ", FGWHITE_BGBLACK, 0);
		cout << employee->getAge() << " years" << endl;

		colorMsg(THREE_TABS + HALF_TAB, "Nif: ", FGWHITE_BGBLACK, 0);
		cout << employee->getNif() << endl;

		colorMsg(THREE_TABS + HALF_TAB, "Phone: ", FGWHITE_BGBLACK, 0);
		cout << employee->getPhone() << endl;

		colorMsg(THREE_TABS + HALF_TAB, "Email: ", FGWHITE_BGBLACK, 0);
		cout << employee->getEmail() << endl;

		colorMsg(THREE_TABS + HALF_TAB, "Wage: ", FGWHITE_BGBLACK, 0);
		cout << employee->getWage() << " EUR" << endl << endl;

		for (size_t i = 0; i < cmdsSize; i++)
			cmdMsg(THREE_TABS + HALF_TAB, (i + 1), cmds[i], FGGREEN_BGBLACK, 1);

		cout << THREE_TABS << HALF_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			createBorrow(employee, false);
			break;
		case '2':
			manageBooks();
			break;
		case '3':
			manageReaders();
			break;
		case '4':
			manageRequests(employee);
			break;
		case '5':
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
	const size_t cmdsSize = 6;
	string cmds[cmdsSize] = { "Borrow a book", "Manage books", "Manage readers",
			"Manage employees", "Manage requests\n", "Logout\n" };
	string header;

	do {
		if (supervisor->getType() != 3) {
			employeeMenu(supervisor);
			break;
		}

		header = "Supervisor" + string(headerSpacing, ' ')
				+ supervisor->getName();
		clearScreen();
		displayHeader(header);

		colorMsg(THREE_TABS + HALF_TAB, "Age: ", FGWHITE_BGBLACK, 0);
		cout << supervisor->getAge() << " years" << endl;

		colorMsg(THREE_TABS + HALF_TAB, "Nif: ", FGWHITE_BGBLACK, 0);
		cout << supervisor->getNif() << endl;

		colorMsg(THREE_TABS + HALF_TAB, "Phone: ", FGWHITE_BGBLACK, 0);
		cout << supervisor->getPhone() << endl;

		colorMsg(THREE_TABS + HALF_TAB, "Email: ", FGWHITE_BGBLACK, 0);
		cout << supervisor->getEmail() << endl;

		colorMsg(THREE_TABS + HALF_TAB, "Wage: ", FGWHITE_BGBLACK, 0);
		cout << supervisor->getWage() << " EUR" << endl << endl;

		for (size_t i = 0; i < cmdsSize; i++)
			cmdMsg(THREE_TABS + HALF_TAB, (i + 1), cmds[i], FGGREEN_BGBLACK, 1);

		cout << THREE_TABS << HALF_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			createBorrow(supervisor, false);
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
			manageRequests(supervisor);
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

void Interface::manageBooks() {
	char input;
	bool exit = false;
	string header = "Manage books", errMsg, infMsg;
	string confirmRemove = "Remove book?";
	const size_t cmdsSize = 6;
	string cmds[cmdsSize] = { "Create", "Display", "BST", "Edit", "Remove\n",
			"Exit\n" };
	Book* book;
	vector<string> booksStr;
	booksStr.push_back("title");
	booksStr.push_back("author");
	booksStr.push_back("year");
	booksStr.push_back("status");

	do {
		clearScreen();
		displayHeader(header);

		int sortFunc = 0;

		for (size_t i = 0; i < cmdsSize; i++)
			cmdMsg(FOUR_TABS, (i + 1), cmds[i], FGGREEN_BGBLACK, 1);

		if (errMsg.size() > 0) {
			errorMsg(errMsg);
			cout << endl << endl;
			errMsg.clear();
		} else if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}
		cout << FOUR_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			if (createBook())
				errMsg = "Error creating a book";
			break;
		case '2':
			while (displayContainer(library.getSortedPrint(BOOK, sortFunc),
					"Books", "\tTitle\t\t\tAuthors\t\t\tYear\tStatus",
					booksStr[sortFunc]) == -1) {
				sortFunc++;
				sortFunc %= booksStr.size();
			}
			break;
		case '3':
			displayContainer(library.getBooksTreePrint(), "Books BST",
					"\tTitle\t\t\tAuthors\t\t\tYear\tStatus", "");
			break;
		case '4':
			book = searchBook(library.getBooks());
			if (book != NULL) {
				editBook(book);
			} else
				errMsg = "Error editing a book";
			break;
		case '5':
			book = searchBook(library.getBooks());
			if (book != NULL && !book->getBorrowed()
					&& confirmOperation(confirmRemove)) {
				if (library.removeBook(book)) {
					library.removeTreeBook(book);
					infMsg = "Book removed successfully";
					library.saveBooks();
				} else
					errMsg = "Error removing a book";
			} else
				errMsg = "Error removing a book";
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

void Interface::manageReaders() {
	char input;
	bool exit = false;
	string header = "Manage readers";
	string errMsg, infMsg;
	string spacing = string((int) ((80 - 17) / 2), ' ');
	const size_t cmdsSize = 7;
	string cmds[cmdsSize] = { "Create", "Display", "Edit", "Remove",
			"Display inactives", "Update inactives\n", "Exit\n" };
	Person* reader;
	vector<string> readerStr;
	readerStr.push_back("name");
	readerStr.push_back("age");
	readerStr.push_back("phone");
	readerStr.push_back("email");
	readerStr.push_back("card");

	do {
		clearScreen();
		displayHeader(header);

		int sortFunc = 0;
		for (size_t i = 0; i < cmdsSize; i++)
			cmdMsg(spacing, (i + 1), cmds[i], FGGREEN_BGBLACK, 1);

		if (errMsg.size() > 0) {
			errorMsg(errMsg);
			cout << endl << endl;
			errMsg.clear();
		} else if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}
		cout << spacing << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			if (createReader())
				errMsg = "Error creating a reader";
			break;
		case '2':
			while (displayContainer(library.getSortedPrint(READER, sortFunc),
					"Readers", "\tName\t\tAge\tPhone\t\tEmail\t\t\tCard",
					readerStr[sortFunc]) == -1) {
				sortFunc++;
				sortFunc %= readerStr.size();
			}
			break;
		case '3':
			reader = searchPerson(library.getReaders(), "Search reader");
			if (reader != NULL)
				editReader(reader);
			else
				errMsg = "Error editing a reader";
			break;
		case '4':
			if (library.removeReader(
					searchPerson(library.getReaders(), "Search reader"))) {
				library.savePersons();
				infMsg = "Reader removed successfully";
			} else
				errMsg = "Error removing a reader";
			break;
		case '5':
			displayContainer(library.getHashTablePrint(), "Inactive Readers",
					"\tName\t\tAge\tPhone\t\tEmail\t\t\tCard", "");
			break;
		case '6':
			library.updateInactiveReaders();
			infMsg = "Inactive readers hash table updated";
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

void Interface::manageEmployees(Person* supervisor) {
	char input;
	bool exit = false;
	string header = "Manage employees";
	string errMsg, infMsg;
	const size_t cmdsSize = 7;
	string cmds[cmdsSize] = { "Create", "Display", "Team", "Edit", "Remove",
			"Auto-assign\n", "Exit\n" };
	Employee* employee;
	vector<string> display;
	vector<Employee *> team;
	vector<string> emplStr;
	emplStr.push_back("name");
	emplStr.push_back("age");
	emplStr.push_back("phone");
	emplStr.push_back("email");
	emplStr.push_back("card");

	do {
		clearScreen();
		displayHeader(header);

		int sortFunc = 0;
		for (size_t i = 0; i < cmdsSize; i++)
			cmdMsg(FOUR_TABS, (i + 1), cmds[i], FGGREEN_BGBLACK, 1);

		if (errMsg.size() > 0) {
			errorMsg(errMsg);
			cout << endl << endl;
			errMsg.clear();
		} else if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}
		cout << FOUR_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			if (createEmployee())
				errMsg = "Error creating an employee";
			break;
		case '2':
			while (displayContainer(
					library.getSortedPrint(EMPLOYEE_OR_SUPERVISOR, sortFunc),
					"Employees", "\tName\t\tAge\tPhone\t\tEmail\t\t\tNif",
					emplStr[sortFunc]) == -1) {
				sortFunc++;
				sortFunc %= emplStr.size();
			}
			break;
		case '3':
			team = supervisor->getEmployeeTeam();
			display = library.getContainerPtrPrint(team);
			displayContainer(display, "Employees team",
					"\tName\t\tAge\tPhone\t\tEmail\t\t\tNif", "");
			break;
		case '4':
			employee = static_cast<Employee*>(searchPerson(
					library.getEmployees(true), "Search employee"));
			if (employee != NULL)
				editEmployee(employee);
			else
				errMsg = "Error editing an employee";
			break;
		case '5':
			if (library.removeEmployee(
					(searchPerson(library.getEmployees(true), "Search employee")),
					supervisor)) {
				library.savePersons();
				infMsg = "Employee removed successfully";
			} else
				errMsg = "Error removing an employee";
			break;
		case '6':
			library.assignEmployees();
			library.savePersons();
			infMsg = "Employees were evenly assigned";
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

void Interface::manageRequests(Person* employee) {
	char input;
	bool exit = false;
	string header = "Manage requests";
	string errMsg, infMsg;
	const size_t cmdsSize = 5;
	string cmds[cmdsSize] =
			{ "Create", "Display", "Edit", "Remove\n", "Exit\n" };

	do {
		clearScreen();
		displayHeader(header);
		Request r;

		for (size_t i = 0; i < cmdsSize; i++)
			cmdMsg(FOUR_TABS, (i + 1), cmds[i], FGGREEN_BGBLACK, 1);

		if (errMsg.size() > 0) {
			errorMsg(errMsg);
			cout << endl << endl;
			errMsg.clear();
		} else if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}
		cout << FOUR_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			createBorrow(employee, true);
			break;
		case '2':
			displayContainer(library.getPriorityQueuePrint(), "Requests queue",
					"\tName\t\tAge\tTitle\t\t\t\tDate", "");
			break;
		case '3':
			r = searchRequest(library.getRequests());
			if (r.getBook() != NULL && r.getReader() != NULL) {
				if (library.removeRequest(r)) {
					Request newR = editRequest(r);
					if (library.addRequest(newR)) {
						library.removeReaderFromHashTable(newR.getReader());
						library.saveRequests();
						r.getReader()->setInactive(false);
					}
				}
			} else {
				errMsg = "No request was selected";
			}
			break;
		case '4':
			r = searchRequest(library.getRequests());
			if (r.getBook() != NULL && r.getReader() != NULL) {
				if (library.removeRequest(r)) {
					infMsg = "Request removed successfully";
					library.saveRequests();
				}
			} else
				errMsg = "No request was selected";
			break;
		case '5':
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

bool Interface::createBook() {

	char input;
	bool aborted = true;
	bool exit = false;
	string infMsg, errMsg;
	const size_t cmdsSize = 8;
	string cmds[cmdsSize] = { "[1] Author: ", "[2] Quota: ", "[3] Pages: ",
			"[4] ISBN: ", "[5] Title: ", "[6] Edition: ", "Create", "Exit" };
	Book *b = NULL;
	string header = "Create Book";
	string newAuthor, newPageNumberStr, newQuota, newISBN, newTitle,
			newEditionYearStr;
	vector<string> authors;
	unsigned int newPageNumber, newEditionYear;

	do {
		stringstream ss;

		clearScreen();
		displayHeader(header);

		colorMsg(THREE_TABS, cmds[0], FGWHITE_BGBLACK, 0);
		cout << (authors.size() > 0 ? authors[0] : "") << endl;
		colorMsg(THREE_TABS, cmds[1], FGWHITE_BGBLACK, 0);
		cout << newQuota << endl;
		colorMsg(THREE_TABS, cmds[2], FGWHITE_BGBLACK, 0);
		cout << newPageNumberStr << endl;
		colorMsg(THREE_TABS, cmds[3], FGWHITE_BGBLACK, 0);
		cout << newISBN << endl;
		colorMsg(THREE_TABS, cmds[4], FGWHITE_BGBLACK, 0);
		cout << newTitle << endl;
		colorMsg(THREE_TABS, cmds[5], FGWHITE_BGBLACK, 0);
		cout << newEditionYearStr << endl << endl;

		for (size_t i = 6; i < cmdsSize; i++) {
			cmdMsg(THREE_TABS, i + 1, cmds[i], FGGREEN_BGBLACK, 2);
		}

		if (errMsg.size() > 0) {
			errorMsg(errMsg);
			cout << endl << endl;
			errMsg.clear();
		} else if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}
		cout << THREE_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			cout << endl << endl;
			authors = editAuthors();
			break;
		case '2':
			cout << endl << endl << THREE_TABS << "Quota: ";
			getline(cin, newQuota, '\n');
			break;
		case '3':
			cout << endl << endl << THREE_TABS << "Pages: ";
			getline(cin, newPageNumberStr, '\n');
			ss << newPageNumberStr;
			ss >> newPageNumber;
			break;
		case '4':
			cout << endl << endl << THREE_TABS << "ISBN: ";
			getline(cin, newISBN, '\n');
			break;
		case '5':
			cout << endl << endl << THREE_TABS << "Title: ";
			getline(cin, newTitle, '\n');
			break;
		case '6':
			cout << endl << endl << THREE_TABS << "Year: ";
			getline(cin, newEditionYearStr, '\n');
			ss << newEditionYearStr;
			ss >> newEditionYear;
			break;
		case '7':
			if (authors.size() == 0) {
				errMsg = "Enter at least one author";
			} else if (newQuota.size() == 0)
				errMsg = "Enter a correct quota";
			else if (newPageNumberStr.size() == 0
					|| !is_All_Number(newPageNumberStr))
				errMsg = "Enter a correct page number";
			else if (newISBN.size() == 0
					|| (newISBN.size() != 13 && newISBN.size() != 10))
				errMsg = "Enter a correct 10 or 13 digit ISBN";
			else if (newTitle.size() == 0)
				errMsg = "Enter a correct title";
			else if (newEditionYearStr.size() == 0
					|| !is_All_Number(newEditionYearStr))
				errMsg = "Enter a correct edition year";
			else {
				b = new Book(authors, false, newQuota, newPageNumber, newISBN,
						newTitle, newEditionYear, false);
				library.addBook(b);
				library.addTreeBook(b);
				library.saveBooks();

				infMsg = newTitle + " successfully created";
				aborted = false;
			}
			break;
		case '8':
			exit = true;
			break;
		case ESCAPE_KEY:
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
	return aborted;
}

bool Interface::createReader() {
	char input;
	bool aborted = true;
	bool exit = false;
	string infMsg, errMsg;
	string header = "Create reader";
	const size_t cmdsSize = 6;
	string cmds[cmdsSize] = { "[1] Name: ", "[2] Age: ", "[3] Phone: ",
			"[4] Email: ", "Create", "Exit" };
	Reader *r = NULL;
	string newName, newAgeStr, newPhoneStr, newEmail;
	unsigned int newAge, newPhone;

	do {
		stringstream ss;
		clearScreen();
		displayHeader(header);
		colorMsg(THREE_TABS, cmds[0], FGWHITE_BGBLACK, 0);
		cout << newName << endl;
		colorMsg(THREE_TABS, cmds[1], FGWHITE_BGBLACK, 0);
		cout << newAgeStr << endl;
		colorMsg(THREE_TABS, cmds[2], FGWHITE_BGBLACK, 0);
		cout << newPhoneStr << endl;
		colorMsg(THREE_TABS, cmds[3], FGWHITE_BGBLACK, 0);
		cout << newEmail.substr(0, 20) << endl << endl;
		for (size_t i = 4; i < cmdsSize; i++) {
			cmdMsg(THREE_TABS, i + 1, cmds[i], FGGREEN_BGBLACK, 2);
		}

		if (errMsg.size() > 0) {
			errorMsg(errMsg);
			cout << endl << endl;
			errMsg.clear();
		} else if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}
		cout << THREE_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			cout << endl << endl << THREE_TABS << "Name: ";
			getline(cin, newName, '\n');
			break;
		case '2':
			cout << endl << endl << THREE_TABS << "Age: ";
			getline(cin, newAgeStr, '\n');
			ss << newAgeStr;
			ss >> newAge;
			break;
		case '3':
			cout << endl << endl << THREE_TABS << "Phone: ";
			getline(cin, newPhoneStr, '\n');
			ss << newPhoneStr;
			ss >> newPhone;
			break;
		case '4':
			cout << endl << endl << THREE_TABS << "Email: ";
			getline(cin, newEmail, '\n');
			break;
		case '5':
			if (newName.size() == 0 || !is_All_ASCII_Letter(newName))
				errMsg = "Enter a correct name";
			else if (newAgeStr.size() == 0 || !is_All_Number(newAgeStr)
					|| newAgeStr.size() > 3)
				errMsg = "Enter a correct age";
			else if (newPhoneStr.size() == 0 || !is_All_Number(newPhoneStr)
					|| newPhoneStr.size() != 9)
				errMsg = "Enter 9 digit phone number";
			else if (newEmail.size() == 0 || newEmail.size() < 6)
				errMsg = "Enter a correct email address";
			else {
				r = new Reader(newName, newAge, newPhone, newEmail);
				library.addPerson(r);
				library.savePersons();
				infMsg = newName + " successfully created";
				aborted = false;
			}
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
	return aborted;
}

bool Interface::createEmployee() {
	char input;
	bool aborted = true;
	bool exit = false;
	string header = "Create employee";
	string infMsg, errMsg;
	const size_t cmdsSize = 9;
	string cmds[cmdsSize] = { "[1] Name: ", "[2] Age: ", "[3] Phone: ",
			"[4] Email: ", "[5] Nif: ", "[6] Wage: ", "[7] Hierarchy: ",
			"Create", "Exit" };
	Employee *e = NULL;
	string newName, newAgeStr, newPhoneStr, newEmail, newNifStr, newWageStr;
	unsigned int newAge, newPhone, newNif, newWage;
	bool newSupervisor = false;

	do {
		stringstream ss;
		clearScreen();
		displayHeader(header);

		colorMsg(THREE_TABS, cmds[0], FGWHITE_BGBLACK, 0);
		cout << newName << endl;
		colorMsg(THREE_TABS, cmds[1], FGWHITE_BGBLACK, 0);
		cout << newAgeStr << endl;
		colorMsg(THREE_TABS, cmds[2], FGWHITE_BGBLACK, 0);
		cout << newPhoneStr << endl;
		colorMsg(THREE_TABS, cmds[3], FGWHITE_BGBLACK, 0);
		cout << newEmail.substr(0, 20) << endl;
		colorMsg(THREE_TABS, cmds[4], FGWHITE_BGBLACK, 0);
		cout << newNifStr << endl;
		colorMsg(THREE_TABS, cmds[5], FGWHITE_BGBLACK, 0);
		cout << newWageStr << endl;
		colorMsg(THREE_TABS, cmds[6], FGWHITE_BGBLACK, 0);
		cout << "[" << (newSupervisor ? "Supervisor" : "Employee") << "]"
				<< endl << endl;
		for (size_t i = 7; i < cmdsSize; i++) {
			cmdMsg(THREE_TABS, i + 1, cmds[i], FGGREEN_BGBLACK, 2);
		}

		if (errMsg.size() > 0) {
			errorMsg(errMsg);
			cout << endl << endl;
			errMsg.clear();
		} else if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}
		cout << THREE_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {

		case '1':
			cout << endl << endl << THREE_TABS << "Name: ";
			getline(cin, newName, '\n');
			break;
		case '2':
			cout << endl << endl << THREE_TABS << "Age: ";
			getline(cin, newAgeStr, '\n');
			ss << newAgeStr;
			ss >> newAge;
			break;
		case '3':
			cout << endl << endl << THREE_TABS << "Phone: ";
			getline(cin, newPhoneStr, '\n');
			ss << newPhoneStr;
			ss >> newPhone;
			break;
		case '4':
			cout << endl << endl << THREE_TABS << "Email: ";
			getline(cin, newEmail, '\n');
			break;
		case '5':
			cout << endl << endl << THREE_TABS << "NIF: ";
			getline(cin, newNifStr, '\n');
			ss << newNifStr;
			ss >> newNif;
			break;
		case '6':
			cout << endl << endl << THREE_TABS << "Wage: ";
			getline(cin, newWageStr, '\n');
			ss << newWageStr;
			ss >> newWage;
			break;
		case '7':
			newSupervisor = !newSupervisor;
			break;
		case '8':
			if (newName.size() == 0 || !is_All_ASCII_Letter(newName))
				errMsg = "Enter a correct name";
			else if (newAgeStr.size() == 0 || !is_All_Number(newAgeStr)
					|| newAgeStr.size() > 3)
				errMsg = "Enter a correct age";
			else if (newPhoneStr.size() == 0 || !is_All_Number(newPhoneStr)
					|| newPhoneStr.size() != 9)
				errMsg = "Enter 9 digit phone number";
			else if (newEmail.size() == 0 || newEmail.size() < 6)
				errMsg = "Enter a correct email address";
			else if (newNifStr.size() == 0 || !is_All_Number(newNifStr)
					|| newNifStr.size() != 9 || seekNIF(newNifStr))
				errMsg = "Enter 9 digit nif";
			else if (newWageStr.size() == 0 || !is_All_Number(newWageStr))
				errMsg = "Enter a numeric wage";
			else {
				e = new Employee(newName, newAge, newPhone, newEmail, newNif,
						newWage, newSupervisor);
				library.addPerson(e);
				library.savePersons();
				infMsg = newName + " successfully created";
				aborted = false;
			}
			break;
		case '9':
			exit = true;
			break;
		case ESCAPE_KEY:
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
	return aborted;
}

void Interface::createBorrow(Person* employee, bool request) {
	char input;
	bool exit = false;
	string header;
	if (request)
		header = "Create request";
	else
		header = "Create borrow";
	string errMsg, infMsg;
	const size_t cmdsSize = 4;
	string cmds[cmdsSize] = { "Select reader", "Select book", (
			request ? "Create request\n" : "Create borrow\n"), "Exit\n" };
	Person* reader = NULL;
	Book* book = NULL;

	do {
		clearScreen();
		displayHeader(header);

		if (reader != NULL) {
			colorMsg(THREE_TABS, "[Reader name] ", FGWHITE_BGBLACK, 0);
			cout << reader->getName() << endl;
		}
		if (book != NULL) {
			colorMsg(THREE_TABS, "[Book title] ", FGWHITE_BGBLACK, 0);
			cout << book->getTitle() << endl;
		}
		if (reader != NULL || book != NULL)
			cout << endl;

		for (size_t i = 0; i < cmdsSize; i++) {
			if (i == 2 && (reader == NULL || book == NULL))
				cmdMsg(THREE_TABS + HALF_TAB, (i + 1), cmds[i], FGGRAY_BGBLACK,
						1);
			else
				cmdMsg(THREE_TABS + HALF_TAB, (i + 1), cmds[i], FGGREEN_BGBLACK,
						1);
		}

		if (errMsg.size() > 0) {
			errorMsg(errMsg);
			cout << endl << endl;
			errMsg.clear();
		}
		if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl << endl;
			infMsg.clear();
		}

		cout << endl << TAB << "Select one reader and one book to create a "
				<< (request ? "request" : "borrow") << " ";
		colorMsg("", "[ESC exits]", FGWHITE_BGBLACK, 2);
		cout << TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			reader = searchPerson(library.getReaders(), "Search reader");
			if (reader == NULL) {
				reader = NULL;
				errMsg = "Select another reader";
			}
			break;
		case '2':
			if (request)
				book = searchBook(library.getBorrowedBooks());
			else
				book = searchBook(library.getBooks());
			if (book == NULL) {
				book = NULL;
				errMsg = "Select another book";
			}
			break;
		case '3':
			if (reader != NULL && book != NULL) {
				Borrow* borrow = new Borrow(book, employee, reader);
				if (!book->getBorrowed() && reader->addBorrow(borrow)) {
					// make reader active again??
					library.addBorrow(borrow);
					infMsg = "Borrow created successfully";
				} else if (book->getBorrowed()) {
					errMsg = "The book requested wasn't available";
					Date d;
					Request r(book, reader, d);
					if (library.addRequest(r)) {
						r.getReader()->setInactive(false);
						library.removeReaderFromHashTable(r.getReader());
						library.saveRequests();
						infMsg = "The book was automatically reserved";
					} else {
						infMsg = "That request already exists";
					}
					delete borrow;
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
	string changesMessage;

	const size_t cmdsSize = 9;
	string cmds[cmdsSize] = { "[1] Author: ", "[2] Quota: ", "[3] Pages: ",
			"[4] ISBN: ", "[5] Title: ", "[6] Edition: ", "Discard changes",
			"Save changes", "Exit" };
	library.removeTreeBook(book);
	Book backup = *book;
	do {
		string newQuota, newTitle, newISBN, newPageNumberStr, newEditionYearStr;
		unsigned int newPageNumber, newEditionYear;
		stringstream ss;
		string header = "Edit book" + string(5, ' ') + book->getTitle();
		clearScreen();
		displayHeader(header);

		colorMsg(THREE_TABS, cmds[0], FGWHITE_BGBLACK, 0);
		cout << book->getAuthors()[0] << endl;
		colorMsg(THREE_TABS, cmds[1], FGWHITE_BGBLACK, 0);
		cout << book->getQuota() << endl;
		colorMsg(THREE_TABS, cmds[2], FGWHITE_BGBLACK, 0);
		cout << book->getPageNumber() << endl;
		colorMsg(THREE_TABS, cmds[3], FGWHITE_BGBLACK, 0);
		cout << book->getISBN() << endl;
		colorMsg(THREE_TABS, cmds[4], FGWHITE_BGBLACK, 0);
		cout << book->getTitle().substr(0, 20) << endl;
		colorMsg(THREE_TABS, cmds[5], FGWHITE_BGBLACK, 0);
		cout << book->getEditionYear() << endl << endl;

		for (size_t i = 6; i < cmdsSize - 1; i++) {
			if (!edited)
				cmdMsg(THREE_TABS, i + 1, cmds[i], FGGRAY_BGBLACK, 1);
			else
				cmdMsg(THREE_TABS, i + 1, cmds[i], FGGREEN_BGBLACK, 1);
		}
		cout << endl;
		cmdMsg(THREE_TABS, cmdsSize, cmds[cmdsSize - 1], FGGREEN_BGBLACK, 1);

		if (changesMessage.size() > 0) {
			cout << endl;
			infoMsg(changesMessage);
			changesMessage.clear();
			cout << endl;
		}
		cout << endl << THREE_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {

		case '1':
			cout << endl << endl;
			book->setAuthors(editAuthors());
			edited = true;
			break;
		case '2':
			cout << endl << endl;
			while (newQuota.size() == 0) {
				cout << THREE_TABS << "Quota: ";
				getline(cin, newQuota, '\n');
			}
			book->setQuota(newQuota);
			edited = true;
			break;

		case '3':
			cout << endl << endl;
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
			cout << endl << endl;
			while (newISBN.size() == 0
					|| (newISBN.size() != 13 && newISBN.size() != 10)) {
				cout << THREE_TABS << "ISBN: ";
				getline(cin, newISBN, '\n');
			}
			book->setISBN(newISBN);
			edited = true;
			break;

		case '5':
			cout << endl << endl;
			while (newTitle.size() == 0) {
				cout << THREE_TABS << "Title: ";
				getline(cin, newTitle, '\n');
			}
			book->setTitle(newTitle);
			edited = true;
			break;
		case '6':
			cout << endl << endl;
			while (newEditionYearStr.size() == 0
					|| !is_All_Number(newEditionYearStr)) {
				cout << THREE_TABS << "Edition year: ";
				getline(cin, newEditionYearStr, '\n');
			}
			ss << newEditionYearStr;
			ss >> newEditionYear;
			book->setEditionYear(newEditionYear);
			edited = true;
			break;
		case '7':
			if (edited) {
				*book = backup;
				edited = false;
				changesMessage = "Changes discarded";
			}
			break;
		case '8':
			if (edited) {
				library.saveBooks();
				edited = false;
				changesMessage = "Changes saved successfully";
			}
			break;
		case '9':
			if (edited)
				*book = backup;
			library.addTreeBook(book);
			edited = false;
			exit = true;
			break;
		case ESCAPE_KEY:
			if (edited)
				*book = backup;
			library.addTreeBook(book);
			edited = false;
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
	bool editingDate = false;
	Date editedDate;
	string errMsg, infMsg;
	const size_t cmdsSize = 9;
	string cmds[cmdsSize] = { "[1] Name: ", "[2] Age: ", "[3] Phone: ",
			"[4] Email: ", "[5] Status: ", "[6] Last activity: ",
			"Discard changes", "Save changes", "Exit" };
	Reader* castedReader = dynamic_cast<Reader*>(reader);
	Reader backup = *castedReader;

	do {
		string newName, newAgeStr, newPhoneStr, newEmail;
		unsigned int newAge, newPhone;
		int editDateResult;
		stringstream ss;
		string header = "Edit Reader" + string(5, ' ') + reader->getName();
		clearScreen();
		displayHeader(header);

		colorMsg(THREE_TABS, cmds[0], FGWHITE_BGBLACK, 0);
		cout << castedReader->getName().substr(0, 20) << endl;
		colorMsg(THREE_TABS, cmds[1], FGWHITE_BGBLACK, 0);
		cout << castedReader->getAge() << endl;
		colorMsg(THREE_TABS, cmds[2], FGWHITE_BGBLACK, 0);
		cout << castedReader->getPhone() << endl;
		colorMsg(THREE_TABS, cmds[3], FGWHITE_BGBLACK, 0);
		cout << castedReader->getEmail().substr(0, 20) << endl;
		colorMsg(THREE_TABS, cmds[4], FGWHITE_BGBLACK, 0);
		cout << (castedReader->getInactive() ? "inactive" : "active") << endl;
		colorMsg(THREE_TABS, cmds[5], FGWHITE_BGBLACK, 0);
		cout
				<< (editingDate ?
						editedDate.print() :
						castedReader->getLastActivity().print()) << endl
				<< endl;

		for (size_t i = 6; i < cmdsSize - 1; i++) {
			if (!edited)
				cmdMsg(THREE_TABS, i + 1, cmds[i], FGGRAY_BGBLACK, 1);
			else
				cmdMsg(THREE_TABS, i + 1, cmds[i], FGGREEN_BGBLACK, 1);
		}
		cout << endl;
		cmdMsg(THREE_TABS, cmdsSize, cmds[cmdsSize - 1], FGGREEN_BGBLACK, 1);

		if (errMsg.size() > 0) {
			cout << endl;
			errorMsg(errMsg);
			cout << endl;
			errMsg.clear();
		}
		if (infMsg.size() > 0) {
			cout << endl;
			infoMsg(infMsg);
			infMsg.clear();
			cout << endl;
		}
		cout << endl << THREE_TABS << PROMPT_SYMBOL;

		if (!editingDate)
			input = getKey();
		switch (input) {

		case '1':
			cout << endl << endl;
			while (newName.size() == 0 || !is_All_ASCII_Letter(newName)) {
				cout << THREE_TABS << "Name: ";
				getline(cin, newName, '\n');
			}
			castedReader->setName(newName);
			edited = true;
			break;

		case '2':
			cout << endl << endl;
			while (newAgeStr.size() == 0 || !is_All_Number(newAgeStr)
					|| newAgeStr.size() > 3) {
				cout << THREE_TABS << "Age: ";
				getline(cin, newAgeStr, '\n');
			}
			ss << newAgeStr;
			ss >> newAge;
			castedReader->setAge(newAge);
			edited = true;
			break;

		case '3':
			cout << endl << endl;
			while (newPhoneStr.size() == 0 || !is_All_Number(newPhoneStr)
					|| newPhoneStr.size() < 6 || newPhoneStr.size() > 12) {
				cout << THREE_TABS << "Phone: ";
				getline(cin, newPhoneStr, '\n');
			}
			ss << newPhoneStr;
			ss >> newPhone;
			castedReader->setPhone(newPhone);
			edited = true;
			break;

		case '4':
			cout << endl << endl;
			while (newEmail.size() == 0 || newEmail.size() < 7) {
				cout << THREE_TABS << "Mail: ";
				getline(cin, newEmail, '\n');
			}
			castedReader->setEmail(newEmail);
			edited = true;
			break;
		case '5':
			castedReader->setInactive(!castedReader->getInactive());
			edited = true;
			break;
		case '6':
			infMsg = " Press [+] or [-] to change the date [ESC to cancel]";
			if (!editingDate) {
				// start editing with editR date
				editedDate = castedReader->getLastActivity();
				editingDate = true;
			} else {
				editDateResult = editDate(editedDate);

				switch (editDateResult) {
				case 0:
					// display new date
					// keep changing date
					if (editedDate != castedReader->getLastActivity())
						edited = true;
					// check inactivity
					castedReader->checkInactiveByDate();
					// change & save new date
					castedReader->setLastActivity(editedDate);
					break;
				case RETURN_KEY:
					// mark edited
					if (editedDate != castedReader->getLastActivity())
						edited = true;
					// check inactivity
					castedReader->checkInactiveByDate();
					// change & save new date
					castedReader->setLastActivity(editedDate);
					// stop changing date
					editingDate = false;
					// display messages
					infMsg.clear();
					break;
				case ESCAPE_KEY:
					// restore date
					// stop changing date
					editingDate = false;
					// display messages
					infMsg.clear();
					errMsg = "Date editing was cancelled";
					break;
				default:
					break;
				}
			}
			break;
		case '7':
			if (edited) {
				*castedReader = backup;
				edited = false;
				infMsg = "Changes discarded";
			}
			break;
		case '8':
			if (edited) {
				reader = castedReader;
				library.savePersons();
				library.removeReaderFromHashTable(&backup);
				if (castedReader->getInactive())
					library.addReaderToHashTable(castedReader);
				edited = false;
				infMsg = "Changes saved successfully";
			}
			break;
		case '9':
			if (edited)
				*reader = backup;
			edited = false;
			exit = true;
			break;
		case ESCAPE_KEY:
			if (edited)
				*reader = backup;
			edited = false;
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
}

void Interface::editEmployee(Employee* employee) {
	char input;
	bool exit = false;
	bool edited = false;
	string changesMessage;
	const size_t cmdsSize = 10;
	string cmds[cmdsSize] = { "[1] Name: ", "[2] Age: ", "[3] Phone: ",
			"[4] Email: ", "[5] Nif: ", "[6] Wage: ", "[7] Hierarchy: ",
			"Discard changes", "Save changes", "Exit" };
	Employee backup = *employee;

	do {
		string newName, newAgeStr, newPhoneStr, newEmail, newNifStr, newWageStr;
		unsigned int newAge, newPhone, newNif, newWage;
		stringstream ss;
		string header = "Edit Employee" + string(5, ' ') + employee->getName();
		clearScreen();
		displayHeader(header);

		colorMsg(THREE_TABS, cmds[0], FGWHITE_BGBLACK, 0);
		cout << employee->getName().substr(0, 20) << endl;
		colorMsg(THREE_TABS, cmds[1], FGWHITE_BGBLACK, 0);
		cout << employee->getAge() << endl;
		colorMsg(THREE_TABS, cmds[2], FGWHITE_BGBLACK, 0);
		cout << employee->getPhone() << endl;
		colorMsg(THREE_TABS, cmds[3], FGWHITE_BGBLACK, 0);
		cout << employee->getEmail().substr(0, 20) << endl;
		colorMsg(THREE_TABS, cmds[4], FGWHITE_BGBLACK, 0);
		cout << employee->getNif() << endl;
		colorMsg(THREE_TABS, cmds[5], FGWHITE_BGBLACK, 0);
		cout << employee->getWage() << endl;
		colorMsg(THREE_TABS, cmds[6], FGWHITE_BGBLACK, 0);
		cout << employee->printType() << endl << endl;

		for (size_t i = 7; i < cmdsSize - 1; i++) {
			if (!edited)
				cmdMsg(THREE_TABS, i + 1, cmds[i], FGGRAY_BGBLACK, 1);
			else
				cmdMsg(THREE_TABS, i + 1, cmds[i], FGGREEN_BGBLACK, 1);
		}
		cout << endl;
		cmdMsg(THREE_TABS, 0, cmds[cmdsSize - 1], FGGREEN_BGBLACK, 1);

		if (changesMessage.size() > 0) {
			cout << endl;
			infoMsg(changesMessage);
			changesMessage.clear();
			cout << endl;
		}
		cout << endl << THREE_TABS << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {

		case '1':
			cout << endl << endl;
			while (newName.size() == 0 || !is_All_ASCII_Letter(newName)) {
				cout << THREE_TABS << "Name: ";
				getline(cin, newName, '\n');
			}
			employee->setName(newName);
			edited = true;
			break;
		case '2':
			cout << endl << endl;
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
			cout << endl << endl;
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
			cout << endl << endl;
			while (newEmail.size() == 0 || newEmail.size() < 7) {
				cout << THREE_TABS << "Email: ";
				getline(cin, newEmail, '\n');
			}
			employee->setEmail(newEmail);
			edited = true;
			break;
		case '5':
			cout << endl << endl;
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
			cout << endl << endl;
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
			employee->setSupervisor(!employee->getSupervisor());
			library.assignEmployees();
			edited = true;
			break;
		case '8':
			if (edited) {
				*employee = backup;
				edited = false;
				changesMessage = "Changes discarded";
			}
			break;
		case '9':
			if (edited) {
				library.savePersons();
				edited = false;
				changesMessage = "Changes saved successfully";
			}
			break;
		case '0':
			if (edited)
				*employee = backup;
			edited = false;
			exit = true;
			break;
		case ESCAPE_KEY:
			if (edited)
				*employee = backup;
			edited = false;
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
	string infMsg, infMsg2, infMsg3, queuedReaderName;

	do {
		clearScreen();
		displayHeader(header);
		borrows = reader->getBorrowedBooks();

		for (size_t i = 0; i < borrows.size(); i++)
			cmdMsg(THREE_TABS, (i + 1), borrows[i]->printShort(),
			FGGREEN_BGBLACK, 1);

		if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl;
			infMsg.clear();
		}
		if (infMsg2.size() > 0) {
			infoMsg(infMsg2);
			cout << endl;
			infMsg2.clear();
		}
		if (infMsg3.size() > 0) {
			infoMsg(infMsg3);
			cout << endl;
			infMsg3.clear();
		}

		cout << endl << THREE_TABS << "Select book to return ";
		colorMsg("", "[ESC exits]", FGWHITE_BGBLACK, 2);
		cout << THREE_TABS << PROMPT_SYMBOL;

		key = getKey();
		switch (key) {
		case '1':
			if (borrows.size() > 0) {
				if (confirmOperation(returnDialog)) {
					reader->removeBorrow(borrows[0]);
					library.removeBorrow(borrows[0]);
					queuedReaderName = library.borrowQueuedRequest(borrows[0]);
					if (queuedReaderName.size() > 0)
						infMsg2 = "Book borrowed to queued reader ["
								+ queuedReaderName + "]";
					library.saveBorrows();
					infMsg = "Book returned successfully";

					if (library.removeRequestByReader(reader)) {
						library.saveRequests();
						infMsg3 = "Book requested was borrowed to the reader";
					}
				}
			}
			break;
		case '2':
			if (borrows.size() > 1) {
				if (confirmOperation(returnDialog)) {
					library.removeBorrow(borrows[1]);
					reader->removeBorrow(borrows[1]);
					queuedReaderName = library.borrowQueuedRequest(borrows[1]);
					if (queuedReaderName.size() > 0)
						infMsg2 = "Book borrowed to queued reader ["
								+ queuedReaderName + "]";
					library.saveBorrows();
					infMsg = "Book returned successfully";

					if (library.removeRequestByReader(reader)) {
						library.saveRequests();
						infMsg3 = "Book requested was borrowed to the reader";
					}
				}
			}
			break;
		case '3':
			if (borrows.size() > 2) {
				if (confirmOperation(returnDialog)) {
					library.removeBorrow(borrows[2]);
					reader->removeBorrow(borrows[2]);
					queuedReaderName = library.borrowQueuedRequest(borrows[2]);
					if (queuedReaderName.size() > 0)
						infMsg2 = "Book borrowed to queued reader ["
								+ queuedReaderName + "]";
					library.saveBorrows();
					infMsg = "Book returned successfully";

					if (library.removeRequestByReader(reader)) {
						library.saveRequests();
						infMsg3 = "Book requested was borrowed to the reader";
					}
				}
			}
			break;
		case RETURN_KEY:
			if (borrows.size() > 0) {
				if (confirmOperation(returnDialog)) {
					library.removeBorrow(borrows[0]);
					reader->removeBorrow(borrows[0]);
					queuedReaderName = library.borrowQueuedRequest(borrows[0]);
					if (queuedReaderName.size() > 0)
						infMsg2 = "Book borrowed to queued reader ["
								+ queuedReaderName + "]";
					library.saveBorrows();
					infMsg = "Book returned successfully";

					if (library.removeRequestByReader(reader)) {
						library.saveRequests();
						infMsg3 = "Book requested was borrowed to the reader";
					}
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

Request Interface::editRequest(const Request &r) {
	char input;
	bool exit = false;
	bool edited = false;
	bool editingDate = false;
	string errMsg, infMsg;
	const size_t cmdsSize = 6;
	string cmds[cmdsSize] = { "[1] Reader: ", "[2] Book: ", "[3] Date: ",
			"Discard changes", "Save changes", "Exit" };
	Date editedDate = r.getDate();
	Request editR = r;
	Request newR = r;

	do {
		int editDateResult;
		stringstream ss;
		string header = "Edit Request";
		clearScreen();
		displayHeader(header);

		colorMsg(THREE_TABS, cmds[0], FGWHITE_BGBLACK, 0);
		cout << editR.getReader()->getName().substr(0, 24) << endl;
		colorMsg(THREE_TABS, cmds[1], FGWHITE_BGBLACK, 0);
		cout << editR.getBook()->getTitle().substr(0, 24) << endl;
		colorMsg(THREE_TABS, cmds[2], FGWHITE_BGBLACK, 0);
		cout << (editingDate ? editedDate.print() : editR.getDate().print())
				<< endl << endl;

		for (size_t i = 3; i < cmdsSize - 1; i++) {
			if (!edited)
				cmdMsg(THREE_TABS, i + 1, cmds[i], FGGRAY_BGBLACK, 1);
			else
				cmdMsg(THREE_TABS, i + 1, cmds[i], FGGREEN_BGBLACK, 1);
		}
		cout << endl;
		cmdMsg(THREE_TABS, cmdsSize, cmds[cmdsSize - 1], FGGREEN_BGBLACK, 2);

		if (errMsg.size() > 0) {
			errorMsg(errMsg);
			cout << endl;
			errMsg.clear();
		}
		if (infMsg.size() > 0) {
			infoMsg(infMsg);
			cout << endl;
			infMsg.clear();
		}

		cout << endl << THREE_TABS << PROMPT_SYMBOL;
		if (!editingDate)
			input = getKey();
		switch (input) {
		case '1':
			if (editR.changeReader(
					searchPerson(library.getReaders(), "Search reader")))
				edited = true;
			else
				errMsg = "Error editing the reader field";
			break;
		case '2':
			if (editR.changeBook(searchBook((library.getBorrowedBooks())))) {
				edited = true;
			} else {
				errMsg = "Error editing the book field";
			}
			break;
		case '3':
			infMsg = " Press [+] or [-] to change the date [ESC to cancel]";
			if (!editingDate) {
				// start editing with editR date
				editedDate = editR.getDate();
				editingDate = true;
			} else {
				editDateResult = editDate(editedDate);

				switch (editDateResult) {
				case 0:
					// display new date
					// keep changing date
					break;
				case RETURN_KEY:
					// mark edited
					if (editedDate != editR.getDate())
						edited = true;
					// change & save new date
					editR.setDate(editedDate);
					// stop changing date
					editingDate = false;
					// display messages
					infMsg.clear();
					break;
				case ESCAPE_KEY:
					// restore date
					// stop changing date
					editingDate = false;
					// display messages
					infMsg.clear();
					errMsg = "Date editing was cancelled";
					break;
				default:
					break;
				}
			}
			break;
		case '4':
			if (edited) {
				edited = false;
				editR = newR; // changes to default again
				infMsg = "Changes discarded";
			}
			break;
		case '5':
			if (edited) {
				newR = editR;
				edited = false;
				infMsg = "Changes saved successfully";
			}
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
	return newR;
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

int Interface::editDate(Date &d) {
	char input = getKey();
	switch (input) {
	case '+':
		d++;
		return 0;
		break;
	case '-':
		d--;
		return 0;
		break;
	case RETURN_KEY:
		return RETURN_KEY;
		break;
	case ESCAPE_KEY:
		return ESCAPE_KEY;
		break;
	default:
		break;
	}
	return 0;
}

Person* Interface::searchPerson(vector<Person*> persons, string header) {
	string query;
	bool exit = false;
	bool clear = false;
	int key;
	size_t selected = 0, vLimit = 14;
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
			for (int j = 16 - matches[i]->getName().size(); j > 0; j -= 8)
				cout << TAB;

			colorMsg("", matches[i]->printType(), FGWHITE_BGBLACK, 1);
		}
		cout << endl << THREE_TABS << "Enter person name ";
		colorMsg("", "[ESC to exit]", FGWHITE_BGBLACK, 2);
		cout << THREE_TABS << PROMPT_SYMBOL << query;

		key = getKey();

		switch (key) {
		case 0:
			break;
		case TAB_KEY:
			if (matches.size() > selected + 1) {
				if (query != matches[selected]->getName())
					query = matches[selected]->getName();
				else
					query = matches[++selected]->getName();
			} else {
				selected = 0;
				if (matches.size() > selected)
					query = matches[selected]->getName();
			}
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
			query.clear();
			clear = true;
			break;
		case ARROW_DOWN:
			if (matches.size() == 0)
				selected = 0;
			else {
				selected++;
				selected %= (matches.size() > vLimit ? vLimit : matches.size());
			}
			break;
		case ARROW_UP:
			if (matches.size() == 0)
				selected = 0;
			else if (selected < 1)
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
	string header = "Search book";
	bool exit = false;
	bool clear = false;
	int key;
	size_t selected = 0, vLimit = 5;
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

			colorMsg(TWO_TABS, "Title:     ", FGWHITE_BGBLACK, 0);
			colorMsg("", matches[i]->getTitle().substr(0, 28),
					(selected == i ? FGBLACK_BGGREEN : FGGREEN_BGBLACK), 0);

			for (ssize_t z = 28 - matches[i]->getTitle().size(); z >= 0; z -= 8)
				cout << TAB;

			colorMsg("",
					(matches[i]->getBorrowed() ? "[Borrowed]" : "[Available]"),
					FGWHITE_BGBLACK, 1);

			colorMsg(TWO_TABS, "Author(s): ", FGWHITE_BGBLACK, 0);
			colorMsg("", matches[i]->printAuthors() + " ",
					(selected == i ? FGBLACK_BGGREEN : FGGREEN_BGBLACK), 2);
		}
		cout << THREE_TABS << "Enter title or author ";
		colorMsg("", "[ESC to exit]", FGWHITE_BGBLACK, 2);
		cout << THREE_TABS << PROMPT_SYMBOL << query;

		key = getKey();

		switch (key) {
		case 0:
			break;
		case TAB_KEY:
			if (matches.size() > selected + 1) {
				if (query != matches[selected]->getTitle())
					query = matches[selected]->getTitle();
				else
					query = matches[++selected]->getTitle();
			} else {
				selected = 0;
				if (matches.size() > selected)
					query = matches[selected]->getTitle();
			}
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
			if (matches.size() == 0)
				selected = 0;
			else {
				selected++;
				selected %= (matches.size() > vLimit ? vLimit : matches.size());
			}
			break;
		case ARROW_UP:
			if (matches.size() == 0)
				selected = 0;
			else if (selected < 1)
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

Request Interface::searchRequest(priority_queue<Request> requestQueue) {
	string query;
	string header = "Search requests";
	bool exit = false;
	bool clear = false;
	int key;
	string spacing = string((int) ((80 - 48) / 2), ' ');
	size_t selected = 0, vLimit = 5;
	vector<Request> matches;
	do {
		clearScreen();
		displayHeader(header);
		priority_queue<Request> copy = requestQueue;
		if (clear) {
			selected = 0;
			matches.clear();
			clear = false;
		}
// Search books for given query
		if (query.size() > 0 && matches.size() == 0) {
			while (!copy.empty()) {
				string readerName = copy.top().getReader()->getName();
				string bookTitle = copy.top().getBook()->getTitle();
				if (partialMatchQuery(query, readerName)
						|| partialMatchQuery(query, bookTitle))
					matches.push_back(copy.top());
				copy.pop();
			}
		}
// Display books that match
		for (size_t i = 0; i < matches.size() && i < vLimit; i++) {

			colorMsg(TWO_TABS, "Reader:     ", FGWHITE_BGBLACK, 0);
			colorMsg("", matches[i].getReader()->getName().substr(0, 28),
					(selected == i ? FGBLACK_BGGREEN : FGGREEN_BGBLACK), 0);

			for (ssize_t z = 28 - matches[i].getReader()->getName().size();
					z >= 0; z -= 8)
				cout << TAB;

			colorMsg("", (matches[i].getDate().print()), FGWHITE_BGBLACK, 1);

			colorMsg(TWO_TABS, "Book:     ", FGWHITE_BGBLACK, 0);
			colorMsg("", matches[i].getBook()->getTitle() + " ",
					(selected == i ? FGBLACK_BGGREEN : FGGREEN_BGBLACK), 2);
		}
		cout << spacing << "Enter reader name or book title ";
		colorMsg("", "[ESC to exit]", FGWHITE_BGBLACK, 2);
		cout << spacing << PROMPT_SYMBOL << query;

		key = getKey();

		switch (key) {
		case 0:
			break;
		case TAB_KEY:
			if (matches.size() > selected + 1) {
				if (query != matches[selected].getReader()->getName())
					query = matches[selected].getReader()->getName();
				else
					query = matches[++selected].getReader()->getName();
			} else {
				selected = 0;
				if (matches.size() > selected)
					query = matches[selected].getReader()->getName();
			}
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
			if (matches.size() == 0)
				selected = 0;
			else {
				selected++;
				selected %= (matches.size() > vLimit ? vLimit : matches.size());
			}
			break;
		case ARROW_UP:
			if (matches.size() == 0)
				selected = 0;
			else if (selected < 1)
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
	Request r;
	return r;
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
	unsigned int width = 80;
	unsigned int size = header.size();
	unsigned int dynSizeLeft = ceil((width - size) / 2);
	unsigned int dynSizeRight = dynSizeLeft;
	char lineSeparator;

#if defined (_WIN32) || defined (_WIN64)
	lineSeparator = '\r';
#else
	lineSeparator = '\n';
#endif

	setColor(FGBLACK_BGGREEN);
	if (dynSizeLeft + dynSizeRight + size < width)
		dynSizeRight++;
	cout << string(width, ' ') << lineSeparator;
	cout << string(dynSizeLeft, ' ') << header << string(dynSizeRight, ' ')
			<< lineSeparator;
	cout << string(width, ' ') << lineSeparator << endl << endl;
	resetColor();
}

bool Interface::confirmOperation(string& query) {
	setColor(FGWHITE_BGBLACK);
	cout << query << " [y/n]";
	char answer = getKey();
	resetColor();

	if (tolower(answer) == 'y')
		return true;
	else
		return false;
}

template<class T>
string Interface::repeatStr(const T& s, const size_t n) {
#if defined(_WIN32) || defined (_WIN64)
	return string(n, s);
#else
	string r = s;
	for (size_t i = 0; i < n; i++)
	r += s;
	return r;
#endif
}

int Interface::displayContainer(vector<string> vec, string listName,
		string labels, string sortStr) {
	unsigned int vecSize = vec.size(), pCount = 1, vLimit = 0, i = 0, progress;
	float pLimit;
	bool done = false;
	char key;
	string vLimitMsg;
	string sortedMsg;
	if (sortStr.size() > 0) {
		sortedMsg = "Sorted by " + sortStr
				+ (sortStr.size() > 5 ? +TAB : +TWO_TABS);
		vLimitMsg =
				" [ESC] to interrupt [s] to sort or any other key to continue...";
	} else
		vLimitMsg = " [ESC] to interrupt or any other key to continue...";
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
			ostringstream progrStr;
			progrStr << sortedMsg << "Page " << pCount << " of " << pLimit

			<< " [" << repeatStr(progressBar, progress)
					<< string((13 - progress), ' ') << "]";
			if (sortStr.size() == 0) {
				cout << THREE_TABS << progrStr.str();
			} else {
				cout << TWO_TABS << progrStr.str();
			}
			cout << endl << endl;
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
				cout << " " << vec[i];
				resetColor();
				cout << endl;
				i++;
				vLimit++;
				if (vLimit == MAX_LINES && i < vecSize) {
					pCount++;
					cout << " " << repeatStr(hSeparator, 77) << endl
							<< vLimitMsg;
					key = getKey();
					if (key == ESCAPE_KEY)
						done = true;
					else if (tolower(key) == 's' && sortStr.size() > 0) {
						return -1;
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
			key = getKey();
			if (tolower(key) == 's' && sortStr.size() > 0) {
				return -1;
			} else
				break;
		}
	}
	return 0;
}

void Interface::setConsole() {
#if defined(_WIN32) || defined (_WIN64)
// get handles
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);

// backup current console configuration
	GetConsoleMode(hConsoleOutput, &fdwOldMode);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(hConsoleOutput, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

// set window title & size
	_COORD coord;
	coord.X = WIDTH;
	coord.Y = HEIGHT;
	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = HEIGHT - 1;
	Rect.Right = WIDTH - 1;
	SetConsoleWindowInfo(hConsoleOutput, TRUE, &Rect);
	SetConsoleScreenBufferSize(hConsoleOutput, coord);
	SetConsoleTitleA("Library");
	setColor(FGGREEN_BGBLACK);
#else
	setColor(FGGREEN_BGBLACK);
	cout << string(30, '\n');
#endif
	clearScreen();
}

void Interface::restoreConsole() {
#if defined(_WIN32) || defined(_WIN64)
// restore old console configuration
	SetConsoleMode(hConsoleInput, fdwOldMode);
	SetConsoleTextAttribute(hConsoleOutput, wOldColorAttrs);
#else
	cout << "\033[0;0;0m" + string(30, '\n');
#endif
	clearScreen();
}

char Interface::getKey() {
#if (defined _WIN32 || defined _WIN64)
	DWORD fdwSaveOldMode;
	GetConsoleMode(hConsoleInput, &fdwSaveOldMode);

// no need to read the return character nor mouse events
	DWORD mode = !ENABLE_ECHO_INPUT | !ENABLE_LINE_INPUT
			| !ENABLE_PROCESSED_INPUT | !ENABLE_MOUSE_INPUT;

	SetConsoleMode(hConsoleInput, mode);

	INPUT_RECORD lpBuffer;
	DWORD lpNumberOfEventsRead;
	DWORD specialKey;

	do {
		ReadConsoleInput(hConsoleInput, &lpBuffer, 1, &lpNumberOfEventsRead);
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

//FlushConsoleInputBuffer(hConsoleInput); // getline & special keys
// Restore input mode on exit.
	SetConsoleMode(hConsoleInput, fdwSaveOldMode);
	return key;
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
	read(STDIN_FILENO, keys, 4096);

	if (keys[0] == 27 && keys[1] == 91) {
		if (keys[2] == 51 && keys[3] == 126)
		keys[0] = DELETE_KEY;
		else if (keys[2] == 65)
		keys[0] = ARROW_UP;
		else if (keys[2] == 66)
		keys[0] = ARROW_DOWN;
		else
		keys[0] = 0;
	} else if (keys[0] == 27 && keys[2] != 0)
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
		case FGGRAY_BGBLACK:
		cout << "\033[40;37m";
		break;
		case FGWHITE_BGBLACK:
		cout << "\033[40;37m";
		break;
		case FGRED_BGBLACK:
		cout << "\033[40;31m";
		break;
		case FGGREEN_BGBLACK:
		cout << "\033[40;32m";
		break;
		case FGBLUE_BGBLACK:
		cout << "\033[40;34m";
		break;
		case FGGRAY_BGRED:
		cout << "\033[41;37m";
		break;
		case FGWHITE_BGRED:
		cout << "\033[41;37m";
		break;
		case FGBLACK_BGWHITE:
		cout << "\033[47;30m";
		break;
		case FGBLACK_BGGRAY:
		cout << "\033[47;30m";
		break;
		case FGBLACK_BGGREEN:
		cout << "\033[42;30m";
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
	cout << "\033[0;40;32m";
#endif
}

inline void Interface::centerString(const size_t &size) {
	int spacing = (int) ((80 - size) / 2);
	cout << string(spacing, ' ');
}

void Interface::cmdMsg(const string &tabs, const size_t index, const string &s,
		const int &color, const int &newLines) {
	cout << tabs;
	stringstream ss;
	setColor(FGWHITE_BGBLACK);
	ss << "[";
	ss << index;
	ss << "] ";
	cout << ss.str();

	setColor(color);
	cout << s;
	cout << string(newLines, '\n');
	resetColor();
}

void Interface::colorMsg(const string &tabs, const string &s, const int &color,
		const int &newLines) {
	cout << tabs;
	setColor(color);
	cout << s;
	cout << string(newLines, '\n');
	resetColor();
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
	vector<Person*> employees = library.getEmployees(true);
	unsigned int nif;
	stringstream ss;
	ss << s;
	ss >> nif;

	for (size_t i = 0; i < employees.size(); i++)
		if (employees[i]->getNif() == nif)
			return true;

	return false;
}

