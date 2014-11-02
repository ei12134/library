#ifndef LIBRARY_H_
#define LIBRARY_H_

#define BOOKS_FILE "books.csv"
#define BORROWS_FILE "borrows.csv"
#define READERS_FILE "readers.csv"
#define EMPLOYEES_FILE "employees.csv"

#include <vector>
#include <fstream>
#include "./Persons/Person.h"
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

public:
	/// reader unique identifier
	static unsigned long int readerID;
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

	///@return employes
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

	/** Loads stored persons
	 * Loads *.csv files to the persons vector
	 */
	void loadPersons();
	/**
	 *Guarda o vetor Books no ficheiro books.csv
	 */
	void saveBooks();
	/**
	 *Guarda o vetor persons no ficheiro employees.csv
	 */
	void saveEmployees();
	/** Loads stored books
	 * Loads *.csv files to the persons vector
	 */
	void loadBooks();

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
