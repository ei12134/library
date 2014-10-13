#include "Interface.h"

Interface::Interface() {
	this->library = Library();
	menu();
}

Interface::~Interface() {
	// TODO Auto-generated destructor stub
}

void Interface::menu() {
	int input;
	string exitDialog = "\n Are you sure you want to exit the program?";
	bool exit = false;

	do {
		clearScreen();
		displayHeader("Library");
		cout << " [1] Enter as a Reader\n";
		cout << " [2] Enter as an Employee\n";
		cout << " [3] Enter as a Supervisor\n";
		cout << " [4] Display\n";
		cout << " [5] Quit\n\n $ ";

		input = getInput();
		switch (input) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			displayMenu();
			break;
		case 5:
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
	int input;
	bool exit = false;

	do {
		clearScreen();
		displayHeader("Display");
		cout << " [1] Readers\n";
		cout << " [2] Employees\n";
		cout << " [3] Supervisors\n";
		cout << " [4] Book\n";
		cout << " [5] Exit to menu\n\n $ ";

		input = getInput();
		switch (input) {
		case 1:
			clearScreen();
			pressAnyKey();
			break;
		case 2:
			clearScreen();
			pressAnyKey();
			break;
		case 3:
			clearScreen();
			pressAnyKey();
			break;
		case 4:
			displayMenu();
			break;
		case 5:
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
	string answer;
	cout << query << "\n [y] to confirm\n\n $ ";
	cin >> answer;

	if (answer == "y" || answer == "Y") {
		clearScreen();
		return true;
	} else {
		clearScreen();
		return false;
	}
}

int Interface::getInput() {
	int input;
	do {
		cin.clear();
		cin >> input;
	} while (cin.fail());

	return input;
}

//string Interface::readInputString(string dialog) {
//	string input;
//	do {
////		cout << " Use only characters from the alphabet [a-z]*[A-Z]*.\n";
//		cout << dialog;
//		getline(cin, input, '\n');
//	} while (cin.fail() || !(is_All_ASCII_Letter(input)) || (input.size() == 1));
//
//	return input;
//}

void Interface::pressAnyKey() {
	cout << " Press any key to continue . . .";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}

bool Interface::is_NON_ASCII_Letter(const int & c) {
	return ((c < 65) || (c > 122) || (c > 90 && c < 97));
}

//bool Interface::is_All_ASCII_Letter(const string& s) {
//	return find_if(s.begin(), s.end(), is_NON_ASCII_Letter) == s.end();
//}

template<typename T>
void Interface::displayContainer(vector<T*> container) const {
	typename vector<T*>::const_iterator it;
	for (it = container.begin(); it != container.end(); it++) {
		string print = (*it)->print();
		cout << print << endl;
	}
}
