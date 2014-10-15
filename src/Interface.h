#ifndef INTERFACE_H_
#define INTERFACE_H_

#ifdef _WIN32
#define CLEAR "cls"
#define PROMPT_SYMBOL " >"
#else // Other OS's
#define PROMPT_SYMBOL " $"
#define CLEAR "clear"
#endif

#include "Library.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <limits>
#include <math.h>
#include <stdio.h>
#include <sstream>
using namespace std;

#define MAX_LINES 5

class Interface {
private:
	Library library;

public:
	Interface();
	void menu();
	void displayMenu();
	void clearScreen();
	void displayHeader(string header);
	bool confirmOperation(string& query);
	int getInput();
	string readInputString(string dialog);
	void pressAnyKey();
	template<typename T>
	void genericDisplay(vector<T> vec, string listName, string labels);
	virtual ~Interface();
};

#endif /* INTERFACE_H_ */
