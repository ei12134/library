#ifndef LIBRARY_H_
#define LIBRARY_H_

#define PERSONS 0
#define READERS 1
#define EMPLOYEES 2
#define SUPERVISORS 3
#define BOOKS 4
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
#include <set>
using namespace std;

/**
 * Library Class
 * stores containers used in the library management
 */
class Library {
private:
	/// vector to Book pointer type objects
	vector<Book*> books;
	/// red-black tree to Book pointer type objects
	set<Book*, bool (*)(const Book*, const Book*)> booksTree;
	/// vector to Borrow pointer type objects
	vector<Borrow*> borrows;
	/// vector to Person pointer type objects
	vector<Person*> persons;

	static bool compareBooks(const Book* b1, const Book* b2) {
		return *b1 < *b2;
	}

public:
	/** Library constructor reads *.csv files and stores
	 * pointers to each object in their dedicated container */
	Library();

	/** Library destructor saves in *.csv files and stores*/
	~Library();

	///@return all books
	vector<Book*> getBooks() const;

	///@return books tree
	set<Book*, bool (*)(const Book*, const Book*)> getBooksTree() const;

	///@return available books
	vector<Book*> getAvailableBooks() const;

	vector<Borrow*> getReaderBorrows(Person* p) const;

	///@return borrows
	vector<Borrow*> getBorrows() const;

	///@return persons
	vector<Person*> getPersons() const;

	///@return readers
	vector<Person*> getReaders() const;

	/* Gets employees of the library
	 * @param true if should also include supervisors
	 * @return employees
	 */
	vector<Person*> getEmployees(bool supervisors) const;

	///@return readers
	vector<Person*> getSupervisors() const;

	/** Gets all print output from T type objects
	 *@return string vector containing print output
	 */
	template<typename T>
	vector<string> getContainerPrint(vector<T> &container) {
		vector<string> prints;
		for (size_t i = 0; i < container.size(); i++)
			prints.push_back(container[i]->print());
		return prints;
	}

	/** Gets all print output from tree containing Book type objects
	 *@return string vector containing books print output
	 */
	vector<string> getBooksTreePrint();

	vector<string> sortPersons(vector<Person*> vec, size_t compareType);

	vector<string> sortBooks(size_t compareType);

	/** Gets container print output after using selected sort function
	 * @param type container
	 * @param sortFunc sort function
	 *@return string vector containing container print output already sorted
	 */
	vector<string> getSortedPrint(int type, int sortFunc);

	/** Replaces existing books pointer vector
	 *@param books Book pointer vector
	 */
	void setBooks(vector<Book*> books);

	/** Replaces existing Borrow pointer vector
	 *@param borrows Borrow pointer vector
	 */
	void setBorrows(vector<Borrow*> borrows);

	/** Replaces existing Person pointer vector
	 *@param persons Person pointer vector
	 */
	void setPersons(vector<Person*> persons);

	/** Adds new book to the library
	 *@param book Book pointer
	 */
	void addBook(Book* book);

	/** Adds new Borrow to the library
	 *@param borrow Borrow pointer
	 */
	void addBorrow(Borrow* borrow);

	/** Adds new person to the library
	 *@param person Person pointer
	 */
	void addPerson(Person* person);

	/** Attempts to remove existing book from the library
	 *@param book Book pointer to remove
	 *@return true if successful false otherwise
	 */
	bool removeBook(Book* book);

	/** Attempts to remove existing borrow from the library
	 *@param borrow Borrow pointer to remove
	 *@return true if successful false otherwise
	 */
	bool removeBorrow(Borrow* borrow);

	/** Attempts to remove existing employee from the library
	 *@param person Person pointer referring to the supervisor authoring the action
	 *@param employee Person pointer of the employee to remove
	 *@return true if successful false otherwise
	 */
	bool removeEmployee(Person* person, Person* employee);

	/** Attempts to remove existing reader from the library
	 *@param reader Person pointer to remove
	 *@return true if successful false otherwise
	 */
	bool removeReader(Person* reader);

	/** Attempts to deallocate existing employee from a supervisor
	 *@param employee Person pointer to remove
	 *@return true if successful false otherwise
	 */
	bool removeEmployeeFromSupervisors(Employee* employee);

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
	void loadBorrows();

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
	 * Assigns employees to supervisors
	 */
	void assignEmployees();
};

#endif /* LIBRARY_H_ */
