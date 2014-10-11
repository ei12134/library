#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

#include "Library.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <limits>
#include <math.h>
#include <stdio.h>
#include <sstream>
using namespace std;

class Interface {
private:
	Library library;

public:
	Interface();
	void menu();
	void displayMenu();
	void clearScreen();
	template<typename T>
	void displayContainer(vector<T*> container) const;
	void displayHeader(string header);
	bool confirmOperation(string& query);
	int getInput();
	string readInputString(string dialog);
	void pressAnyKey();
	bool is_NON_ASCII_Letter(const int & c);
	bool is_All_ASCII_Letter(const string& s);
	virtual ~Interface();
};

#endif /* SRC_INTERFACE_H_ */
