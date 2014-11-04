#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "Library.h"
#include "Algorithms.h"
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

#define TAB "\t"
#define DOUBLE_TAB TAB TAB
#define TRI_TAB DOUBLE_TAB TAB
#define TETRA_TAB DOUBLE_TAB DOUBLE_TAB
#define MAX_LINES 9
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
	void manageBooks();
	void manageReaders();
	void manageEmployees(Person* supervisor);
	void createBook();
	void createEmployee();
	void createReader();
	void editBook(Book* book);
	void editEmployee(Person* employee);
	vector<string> editAuthors();
	Person* searchPerson(vector<Person*> persons);
	Book* searchBook(vector<Book*> books);
	void displayHeader(string& header);
	bool confirmOperation(string& query);
	string readInputString(string dialog);
	template<typename T>
	void genericDisplay(vector<T> vec, string listName, string labels);
	virtual ~Interface();
	char getKey();
	bool is_Number(const int & c);
	template<typename T>
	string optParam(const T &p);
};

#endif /* INTERFACE_H_ */
