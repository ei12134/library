#ifndef LIBRARY_H_
#define LIBRARY_H_

#define BOOKS_FILE "books.csv"
#define BORROWS_FILE "borrows.csv"
#define READERS_FILE "readers.csv"
#define EMPLOYEES_FILE "employees.csv"
#define SUPERVISORS_FILE "supervisors.csv"

#include "./Persons/Person.h"
#include "./Persons/Employee.h"
#include "Algorithms.h"
#include "Book.h"
#include "Borrow.h"
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

/**
 * Library Class
 * stores containers used in the library management
 */
class Library {
private:
	/// vector to Book pointer type objects
	vector<Book*> books;
	/// vector to Borrow pointer type objects
	vector<Borrow*> borrows;
	/// vector to Person pointer type objects
	vector<Person*> persons;
public:
	/** Library constructor reads *.csv files and stores
	 * pointers to each object in their dedicated container */
	Library();

	/** Library destructor saves in *.csv files and stores*/
	~Library();

	///@return all books
	vector<Book*> getBooks() const;

	///@return available books
	vector<Book*> getAvailableBooks() const;

	vector<Borrow*> getBorrowedBooksFromReader(Person* p) const;

	///@return borrows
	vector<Borrow*> getBorrows() const;

	///@return persons
	vector<Person*> getPersons() const;

	///@return readers
	vector<Person*> getReaders() const;

	///@return employees
	vector<Person*> getEmployees() const;

	///@return non supervisor employees
	vector<Person*> getEmployeesNoSupervisors() const;

	///@return readers
	vector<Person*> getSupervisors() const;


	/** replaces existing books pointer vector
	 *@param books Book pointer vector
	 */
	void setBooks(vector<Book*> books);

	/** replaces existing Borrow pointer vector
	 *@param borrows Borrow pointer vector
	 */
	void setBorrows(vector<Borrow*> borrows);

	/** replaces existing Person pointer vector
	 *@param persons Person pointer vector
	 */
	void setPersons(vector<Person*> persons);

	/** adds new book to the library
	 *@param book Book pointer
	 */
	void addBook(Book* book);

	/** adds new Borrow to the library
	 *@param borrow Borrow pointer
	 */
	void addBorrow(Borrow* borrow);

	/** adds new person to the library
	 *@param person Person pointer
	 */
	void addPerson(Person* person);

	/** removes a book from the library
	 *@param book Book pointer
	 */
	bool removeBook(Book* book);

	/** returns a borrow to the library
	 *@param borrow Borrow pointer
	 */
	bool removeBorrow(Borrow* borrow);

	/** removes an employee from the library
	 *@param supervisor Person pointer
	 *@param employee Person pointer
	 */
	bool removeEmployee(Person* person, Person* employee);

	/** removes a reader from the library
	 *@param reader Person pointer
	 */
	bool removeReader(Person* reader);

	/** Loads stored books
	 * Loads books.csv file to the books vector
	 */
	void loadBooks();

	/** Loads stored persons
	 * Loads readers.csv, employees.csv and supervisors.csv files to the persons vector
	 */
	void loadPersons();

	/** Loads stored borrows
	 * Loads borrows.csv file to the borrows vector
	 */
	void loadBorrowBooks();

	/**
	 * Saves books in books.csv file
	 */
	void saveBooks();

	/**
	 * Saves persons in corresponding readers.csv, employees.csv and supervisors.csv files
	 */
	void savePersons();

	/**
	 * Saves borrows in borrows.csv file
	 */
	void saveBorrows();

	/**
	 * Sorts persons by type
	 */

	void sortByType();
	/**
	 * Sorts persons by name
	 */

	void sortByName();

	/**
	 * Sorts persons by age
	 */
	void sortByAge();

	/**
	 * Sorts readers by borrow count
	 */
	void sortByBorrow();

	/**
	 * Sorts books by title
	 */
	void sortByTitle();

	/**
	 * Sorts books by ISBN
	 */
	void sortByISBN();

	void SupervisorEmployeeRandom();

};

#endif /* LIBRARY_H_ */
