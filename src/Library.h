#ifndef LIBRARY_H_
#define LIBRARY_H_

#define BOOKS_FILE "books.csv"
#define BORROWS_FILE "borrows.csv"
#define READERS_FILE "readers.csv"
#define EMPLOYEES_FILE "employees.csv"
#define SUPERVISORS_FILE "supervisors.csv"

#include <vector>
#include <fstream>
#include "./Persons/Person.h"
#include "./Persons/Employee.h"
#include "Book.h"
#include "Borrow.h"
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

	/** Loads stored books
	 * Loads *.csv files to the persons vector
	 */
	void loadBooks();

	/** Loads stored persons
	 * Loads *.csv files to the persons vector
	 */
	void loadPersons();

	/**
	 * Saves books in books.csv file
	 */
	void saveBooks();

	/**
	 * Saves persons in appropriate *.csv files
	 */
	void savePersons();

	void SaveBorrows();

	void loadBorrowBooks();

public:
	/// reader unique identifier(solution save in separate file this unique ids)
	static unsigned long int readerID;
	static unsigned long int borrowID;

	/** Library constructor reads *.csv files and stores
	 * pointers to each object in their dedicated container */
	Library();

	/** Library destructor saves in *.csv files and stores*/
	~Library();

	///@return books
	vector<Book*> getBooks() const;

	///@return borrows
	vector<Borrow*> getBorrows() const;

	///@return persons
	vector<Person*> getPersons() const;

	///@return readers
	vector<Person*> getReaders() const;

	///@return employees
	vector<Person*> getEmployees() const;

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

	/** removes a borrow from the library
	 *@param borrow Borrow pointer
	 */
	bool removeBorrow(Borrow* borrow);

	/** removes a person from the library
	 *@param person Person pointer
	 */
	bool removePerson(Person* person);
};

#endif /* LIBRARY_H_ */
