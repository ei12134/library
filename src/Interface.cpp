#include "Interface.h"

Interface::Interface() {
	this->library = Library();
	menu();
}

Interface::~Interface() {
}

void Interface::menu() {
	char input;
	string exitDialog = " Exit the program?";
	bool exit = false;

	do {
		clearScreen();
		displayHeader("Library");
		cout << "\n [1] Enter as a Reader\n\n";
		cout << " [2] Enter as an Employee\n\n";
		cout << " [3] Enter as a Supervisor\n\n";
		cout << " [4] Display\n\n";
		cout << " [5] Quit\n\n\n" << PROMPT_SYMBOL;

		input = getch();
		switch (input) {
		case 49:
			break;
		case 50:
			break;
		case 51:
			break;
		case 52:
			displayMenu();
			break;
		case 53:
			if (confirmOperation(exitDialog))
				exit = true;
			break;
		default:
			input = -1;
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
		cout << "\n [1] All\n\n";
		cout << " [2] Readers\n\n";
		cout << " [3] Employees\n\n";
		cout << " [4] Supervisors\n\n";
		cout << " [5] Book\n\n";
		cout << " [6] Exit to menu\n\n\n" << PROMPT_SYMBOL;

		input = getch();
		switch (input) {
		case 49:
			clearScreen();
			genericDisplay(library.getPersons(), "All",
					"Name ; Age ; Phone ; Email ; [Card] ; Nif ; Wage");
			break;
		case 50:
			clearScreen();
			genericDisplay(library.getReaders(), "Readers",
					"Name ; Age ; Phone ; Email ; Card");
			break;
		case 51:
			clearScreen();
			genericDisplay(library.getEmployees(), "Employees",
					"Name ; Age ; Phone ; Email ; Nif ; Wage");
			break;
		case 52:
			clearScreen();
			genericDisplay(library.getSupervisors(), "Supervisors",
					"Name ; Age ; Phone ; Email ; Nif ; Wage");
			break;
		case 53:
			clearScreen();
			break;
		case 54:
			exit = true;
			break;
		default:
			input = -1;
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

	cout << "\n " << string(36, '#') << "\n";
	cout << " #" << string(34, ' ') << "#\n";
	cout << " #" << string(dynsize, ' ') << header << string(dynsize2, ' ')
			<< "#\n";
	cout << " #" << string(34, ' ') << "#\n";
	cout << " " << string(36, '#') << "\n\n";
}

bool Interface::confirmOperation(string& query) {
	cout << query << " [y] to confirm ";
	char answer = getch();

	if (answer == 'y' || answer == 'Y')
		return true;
	else
		return false;
}

void Interface::pressAnyKey() {
	cout << " Press any key to continue...";
	getch();
}

template<typename T>
void Interface::genericDisplay(vector<T> vec, string listName, string labels) {
	unsigned int vecSize = vec.size(), pCount = 1, vLimit = 0, i = 0, progress;
	float pLimit = ceil(static_cast<float>(vecSize) / MAX_LINES);
	bool done = false;
	string vLimitDialog = " [q] to interrupt or any other key to continue...";
	char ch;

	while (i < vecSize && !done) {
		vLimit = 0;
		progress = ceil((18.0 / pLimit) * pCount);
		clearScreen();
		displayHeader(listName);
		cout << " Page " << pCount << " out of " << pLimit << " ["
				<< string(progress, '#') << string((18 - progress), ' ')
				<< "]\n\n";
		cout << " " << string(78, '-') << " ";
		cout << " " << labels << string(79 - labels.length(), ' ');
		cout << " " << string(78, '-') << " ";

		while (vLimit < MAX_LINES && i < vecSize && !done) {
			cout << "\n " << vec[i]->print() << "\n"; // maybe overload << operator??
			i++;
			vLimit++;

			if (vLimit == MAX_LINES && i < vecSize) {
				pCount++;
				cout << " " << string(78, '-') << " " << vLimitDialog;
				ch = getch();
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
