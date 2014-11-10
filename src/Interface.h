#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "Library.h"
#include "Algorithms.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

#ifdef _WIN32
#define BACKSPACE_KEY 8
#define RETURN_KEY 13
#define CLEARSCREEN "cls"
#include <windows.h>
#include <conio.h>
#define PROMPT_SYMBOL "> "
#else // Other OS's
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO
#define PROMPT_SYMBOL "$ "
#define CLEARSCREEN "clear"
#define BACKSPACE_KEY 127
#define RETURN_KEY 10
#endif

#define GRAY -1
#define WHITE 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define HALF_TAB string(4,' ')
#define TAB "\t"
#define TWO_TABS TAB TAB
#define THREE_TABS TWO_TABS TAB
#define FOUR_TABS TWO_TABS TWO_TABS
#define MAX_LINES 11
#define ESCAPE_KEY 27
#define DELETE_KEY 83

static const char topBorder = 220;
static const char bottomBorder = 223;
static const char verticalBorder = 219;
static const char hSeparator = 196;
static const char progressBar = 254;

class Interface {
private:
	Library library;
#if defined(_WIN32) || defined (_WIN64)
	HANDLE hConsole;
#endif

public:
	Interface();
	~Interface();

	void menu();
	void sortMenu();
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
	void createReader();
	void createEmployee();
	void createBorrow(Person* employee);

	void editBook(Book* book);
	void editReader(Person* reader);
	void editEmployee(Person* employee);
	void editBorrow(Person* reader);
	vector<string> editAuthors();

	Person* searchPerson(vector<Person*> persons);
	Book* searchBook(vector<Book*> books);

	void displayHeader(string& header);
	bool confirmOperation(string& query);

	template<typename T>
	void genericDisplay(vector<T> vec, string listName, string labels);

	inline string centerString(const string &s);

	void infoMsg(const string& m);
	void errorMsg(const string& m);

	char getKey();
	void setColor(int color);
	void resetColor();
	bool is_Number(const int & c);
	bool seekNIF(const string &s);
};

#endif /* INTERFACE_H_ */
