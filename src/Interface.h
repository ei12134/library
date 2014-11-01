#ifndef INTERFACE_H_
#define INTERFACE_H_

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
#include <cstdlib>
using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#include <conio.h>
#define PROMPT_SYMBOL "> "
#else // Other OS's
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO
#define PROMPT_SYMBOL "$ "
#define CLEAR "clear"
#endif

#define MAX_LINES 5
#define TAB string(26, ' ')
#define DOUBLE_TAB "\t\t"
#define SYMBOL_TAB string(22, ' ')
#define SYMBOL_SHORT_TAB string(1, ' ')
#define BACSKPACE_KEY 8
#define RETURN_KEY 13
#define ESCAPE_KEY 27
#define DELETE_KEY 83

class Interface {
private:
	Library library;

public:
	Interface();
	void menu();
	void displayMenu();
	void clearScreen();
	void dispatchPerson(Person* person);
	void readerMenu(Person* reader);
	void employeeMenu(Person* employee);
	void supervisorMenu(Person* supervisor);
	void create();
	void createPerson();
	void createEmployees();
	void createReaders();
	void createSupervisors();
	void createBook();
	Person* searchPerson(vector<Person*> persons);
	void displayHeader(string& header);
	bool confirmOperation(string& query);
	string readInputString(string dialog);
	void pressAnyKey();
	template<typename T>
	void genericDisplay(vector<T> vec, string listName, string labels);
	virtual ~Interface();
	char getKey();
	bool is_NON_ASCII_Letter(const int & c);
	bool is_All_ASCII_Letter(const string& s);
	bool is_Number(const int & c);
	bool matchQuery(const string & q, const string & n);
};

#endif /* INTERFACE_H_ */
