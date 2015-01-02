#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "Library.h"
#include "Algorithms.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

#if defined(_WIN32) || defined (_WIN64)
#define BACKSPACE_KEY 8
#define RETURN_KEY 13
#define CLEARSCREEN "cls"
#include <windows.h>
#include <wincon.h>
#define PROMPT_SYMBOL "> "

static const char hSeparator = 196;
static const char progressBar = 254;

#else // Other OS's#include <termios.h>    //termios, TCSANOW, ECHO, ICANON#include <unistd.h>     //STDIN_FILENO#define PROMPT_SYMBOL "$ "#define CLEARSCREEN "clear"#define BACKSPACE_KEY 127
#define RETURN_KEY 10
static const string hSeparator = "\u2501";
static const string progressBar = "\u25A0";

#endif

#define FGGRAY_BGBLACK -1
#define FGWHITE_BGBLACK 0
#define FGRED_BGBLACK 1
#define FGGREEN_BGBLACK 2
#define FGBLUE_BGBLACK 3
#define FGGRAY_BGRED 4
#define FGWHITE_BGRED 5
#define FGBLACK_BGWHITE 6
#define FGBLACK_BGGRAY 7
#define FGBLACK_BGGREEN 8
#define HALF_TAB string(4,' ')
#define TAB "\t"
#define TWO_TABS TAB TAB
#define THREE_TABS TWO_TABS TAB
#define THREE_HALF_TABS TWO_TABS TAB + HALF_TAB
#define FOUR_TABS TWO_TABS TWO_TABS
#define FIVE_TABS FOUR_TABS TAB
#define MAX_LINES 12
#define ESCAPE_KEY 27
#define ARROW_DOWN 28
#define ARROW_UP 29
#define SPACE_BAR 32
#define DELETE_KEY 83
#define TAB_KEY 9
#define WIDTH 80
#define HEIGHT 25

const size_t headerSpacing = 3;

class Interface {
private:
	Library library;
#if defined(_WIN32) || defined (_WIN64)
	HANDLE hConsoleOutput;
	HANDLE hConsoleInput;
	DWORD fdwOldMode;
	DWORD wOldColorAttrs;
#endif

public:
	Interface();
	~Interface();

	void menu();
	void displayMenu();
	void searchMenu();

	void clearScreen();
	void dispatchPerson(Person* person);
	void readerMenu(Person* reader);
	void employeeMenu(Person* employee);
	void supervisorMenu(Person* supervisor);

	void manageBooks();
	void manageReaders();
	void manageEmployees(Person* supervisor);
	void manageRequests(Person* employee);

	bool createBook();
	bool createReader();
	bool createEmployee();
	void createBorrow(Person* employee, bool request);

	void editBook(Book* book);
	void editReader(Person* reader);
	void editEmployee(Employee* employee);
	void editBorrow(Person* reader);
	Request editRequest(const Request &r);
	vector<string> editAuthors();

	int editDate(Date &d);

	Person* searchPerson(vector<Person*> persons, string header);
	Book* searchBook(vector<Book*> books);
	Request searchRequest(priority_queue<Request> requestQueue);

	void displayHeader(string& header);
	bool confirmOperation(string& query);

	int displayContainer(vector<string> vec, string listName, string labels,
			string sortStr);

	inline void centerString(const size_t &size);

	void cmdMsg(const string &tabs, const size_t index, const string &s,
			const int &color, const int &newLines);

	void colorMsg(const string &tabs, const string &s, const int &color,
			const int &newLines);
	void infoMsg(const string& m);
	void errorMsg(const string& m);

	template<class T>
	string repeatStr(const T& s, const size_t n);

	void setConsole();
	void restoreConsole();
	char getKey();
	void setColor(int color);
	void resetColor();
	bool is_Number(const int & c);
	bool seekNIF(const string &s);
};

#endif /* INTERFACE_H_ */
