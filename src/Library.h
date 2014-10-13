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
#include "./Persons/Person.h"
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
	/// pointer vector to person type objects
	vector<Person*> persons;

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

	///@return persons
	vector<Person*> getPersons() const;

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

	/** replaces existing Person pointer vector containing persons
	 *@param persons Person pointer vector
	 */
	void setPersons(vector<Person*> person);

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

	/** adds new person to the library
	 *@param person Person pointer
	 */
	void addPerson(Person* person);

	/** Loads stored persons
	 * Loads *.csv files to the persons vector
	 */
	void loadPersons();

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

	/** removes a person from the library
	 *@param person Person pointer
	 */
	bool removePerson(Person* person);
};

#endif /* SRC_LIBRARY_H_ */
