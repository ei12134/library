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
	bool exit = false;

	do {
		clearScreen();
		displayHeader("Library");
		cout << endl << TAB << "[1] Enter as a Reader\n\n";
		cout << TAB << "[2] Enter as an Employee\n\n";
		cout << TAB << "[3] Enter as a Supervisor\n\n";
		cout << TAB << "[4] Display\n\n";
		cout << TAB << "[5] Quit\n\n\n" << SYMBOL_TAB << PROMPT_SYMBOL;

		input = getKey();
		switch (input) {
		case '1':
			break;
		case '2':
			break;
		case '3':
			break;
		case '4':
			displayMenu();
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

void Interface::displayMenu() {
	char input;
	bool exit = false;

	do {
		clearScreen();
		displayHeader("Display");
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

void Interface::displayHeader(string header) {
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
	newt.c_lflag &= ~(ICANON | ECHO);

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
