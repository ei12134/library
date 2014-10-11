#ifndef SRC_LIBRARY_H_
#define SRC_LIBRARY_H_

#define BOOKS_FILE "books.csv"
#define CURRENT_BORROWS_FILE "current.csv"
#define PREVIOUS_BORROWS_FILE "previous.csv"
#define READERS_FILE "readers.csv"
#define EMPLOYEES_FILE "employees.csv"
#define SUPERVISORS_FILE "supervisors.csv"

#include <vector>
#include <fstream>
#include "./Borrow/Current.h"
#include "./Borrow/Previous.h"
#include "./Persons/Reader.h"
#include "./Persons/Employee.h"
#include "./Persons/Supervisor.h"
#include "Book.h"
using namespace std;

/**
 * Library Class
 * stores containers used in the library management
 */
class Library {

private:
	/// pointer vector to book type objects
	vector<Book*> books;
	/// pointer vector to borrow type objects
	vector<Current*> currentBorrows;
	/// pointer vector to borrow type objects
	vector<Previous*> previousBorrows;
	/// pointer vector to person type objects readers
	vector<Reader*> readers;
	/// pointer vector to person type objects employees
	vector<Employee*> employees;
	/// pointer vector to person type objects supervisors
	vector<Supervisor*> supervisors;

public:
	/// reader unique identifier
	static unsigned long int readerID;
	/** Library constructor reads *.csv files and stores
	 * pointers to each object in their dedicated container */
	Library();
	virtual ~Library();

	///@return books
	vector<Book*> getBooks() const;

	///@return borrows
	vector<Current*> getCurrentBorrows() const;

	///@return borrows
	vector<Previous*> getPreviousBorrows() const;

	///@return readers
	vector<Reader*> getReaders() const;

	///@return employees
	vector<Employee*> getEmployees() const;

	///@return supervisors
	vector<Supervisor*> getSupervisors() const;

	/** replaces existing books pointer vector
	 *@param books Book pointer vector
	 */
	void setBooks(vector<Book*> books);

	/** replaces existing Borrow pointer vector
	 *@param currentBorrows Borrow pointer vector
	 */
	void setCurrentBorrows(vector<Current*> currentBorrows);

	/** replaces existing Borrow pointer vector
	 *@param previousBorrows Borrow pointer vector
	 */
	void setPreviousBorrows(vector<Previous*> previousBorrows);

	/** replaces existing Reader pointer vector containing readers
	 *@param readers Reader pointer vector
	 */
	void setReaders(vector<Reader*> readers);

	/** replaces existing Employees pointer vector containing employees
	 *@param employees Employees pointer vector
	 */
	void setEmployees(vector<Employee*> employees);

	/** replaces existing Supervisors pointer vector containing supervisors
	 *@param supervisors Supervisors pointer vector
	 */
	void setSupervisors(vector<Supervisor*> supervisors);

	/** adds new book to the library
	 *@param book Book pointer
	 */
	void addBook(Book* book);

	/** adds new current Borrow to the library
	 *@param currentBorrow Current borrow pointer
	 */
	void addCurrentBorrow(Current* currentBorrow);

	/** adds new previous borrow to the library
	 *@param previousBorrow Previous borrow pointer
	 */
	void addPreviousBorrow(Previous* previousBorrow);

	/** adds new reader to the library
	 *@param reader Reader pointer
	 */
	void addReader(Reader* reader);

	/** adds new employee to the library
	 *@param employee Employee pointer
	 */
	void addEmployee(Employee* employee);

	/** adds new supervisor to the library
	 *@param supervisor Supervisor pointer
	 */
	void addSupervisor(Supervisor* supervisor);

	/** Loads stored readers
	 * Loads readers.csv to the readers vector
	 */
	void loadReaders();

	/** Loads stored employees
	 * Loads employees.csv to the employees vector
	 */
	void loadEmployees();

	/** Loads stored supervisors
	 * Loads supervisors.csv to the supervisors vector
	 */
	void loadSupervisors();

	/** removes a book from the library
	 *@param book Book pointer
	 */
	bool removeBook(Book* book);

	/** removes a current borrow from the library
	 *@param currentBorrow Current pointer
	 */
	bool removeCurrentBorrow(Current* currentBorrow);

	/** removes a previous borrow from the library
	 *@param previousBorrow Previous pointer
	 */
	bool removePreviousBorrow(Previous* previousBorrow);

	/** removes a reader from the library
	 *@param reader Reader pointer
	 */
	bool removeReader(Reader* reader);

	/** removes a employee from the library
	 *@param employee Employee pointer
	 */
	bool removeEmployee(Employee* employee);

	/** removes a supervisor from the library
	 *@param supervisor Supervisor pointer
	 */
	bool removeSupervisor(Supervisor* supervisor);
};

#endif /* SRC_LIBRARY_H_ */
