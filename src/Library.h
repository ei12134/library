#ifndef LIBRARY_H_
#define LIBRARY_H_

#define BOOKS_FILE "books.csv"
#define BORROWS_FILE "borrows.csv"
#define READERS_FILE "readers.csv"
#define EMPLOYEES_FILE "employees.csv"
#define SUPERVISORS_FILE "supervisors.csv"
#define REQUESTS_FILE "requests.csv"

#include "./Persons/Person.h"
#include "./Persons/Employee.h"
#include "Algorithms.h"
#include "Book.h"
#include "Borrow.h"
#include <algorithm>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>
#include <set>
#include <tr1/unordered_set>

struct eqReadF {
	bool operator()(const Person* p1, const Person* p2) const {
		return p1->getCard() == p2->getCard();
	}
};

struct hReadF {
	int operator()(const Person* p1) const {
		return p1->getCard();
	}
};

typedef tr1::unordered_set<Person*, hReadF, eqReadF>::const_iterator cIteratorH;
typedef tr1::unordered_set<Person*, hReadF, eqReadF>::iterator iteratorH;
typedef tr1::unordered_set<Person*, hReadF, eqReadF> tabH;

/**
 * Library Class
 * stores containers used in the library management
 */
class Library {
private:
	set<Book*, bool (*)(const Book*, const Book*)> booksTree; /// red-black tree to Book pointer type objects
	vector<Book*> books; /// vector to Book pointer type objects
	vector<Borrow*> borrows; /// vector to Borrow pointer type objects
	vector<Person*> persons; /// vector to Borrow pointer type objects
	tabH inactiveReaders; /// hash table containing inactive readers
	priority_queue<Request> requestsQueue; /// priority queue containing books reservations

public:
	/** Library constructor reads *.csv files and stores
	 * pointers to each object in their dedicated container */
	Library();

	/** Library destructor saves in *.csv files and stores*/
	~Library();

	///@return comparison between two books
	static bool compareBooks(const Book* b1, const Book* b2) {
		return *b1 < *b2;
	}

	///@return all books
	vector<Book*> getBooks() const;

	///@return books tree
	set<Book*, bool (*)(const Book*, const Book*)> getBooksTree() const;

	///@return available books
	vector<Book*> getAvailableBooks() const;

	///@return borrowed books
	vector<Book*> getBorrowedBooks() const;

	///@return borrows from a given reader
	vector<Borrow*> getReaderBorrows(Person* p) const;

	///@return borrows
	vector<Borrow*> getBorrows() const;

	///@return persons
	vector<Person*> getPersons() const;

	///@return readers
	vector<Person*> getReaders() const;

	/** Gets employees of the library
	 * @param true if it also should include supervisors
	 * @return employees
	 */
	vector<Person*> getEmployees(bool supervisors) const;

	///@return readers
	vector<Person*> getSupervisors() const;

	///@return readers
	priority_queue<Request> getRequests() const;

	/** Gets all print output from T type objects
	 *@return string vector containing print output
	 */
	template<typename T>
	vector<string> getContainerPtrPrint(vector<T> &container) {
		vector<string> prints;
		for (size_t i = 0; i < container.size(); i++)
			prints.push_back(container[i]->print());
		return prints;
	}

	/** Gets all print output from T type objects
	 *@return string vector containing print output
	 */
	template<typename T>
	vector<string> getContainerPrint(vector<T> &container) {
		vector<string> prints;
		for (size_t i = 0; i < container.size(); i++)
			prints.push_back(container[i].print());
		return prints;
	}

	/** Gets all print output from tree containing Book type objects
	 *@return string vector containing books print output
	 */
	vector<string> getBooksTreePrint() const;

	/** Gets all print output from tree containing Book type objects
	 * @param year to search
	 *@return string vector containing books print output of a given year
	 */
	vector<string> getBooksTreePrintByYear(unsigned int year) const;

	/** Gets all print output from tree containing Book type objects
	 * @param title to search
	 *@return string vector containing books print output of a given title
	 */
	vector<string> getBooksTreePrintByTitle(string title) const;

	/** Gets all print output from tree containing Book type objects
	 * @param author to search
	 *@return string vector containing books print output of a given author
	 */
	vector<string> getBooksTreePrintByAuthor(string author) const;

	/** Gets all print output from hash table
	 *@return string vector containing all inactive readers
	 */
	vector<string> getHashTablePrint() const;

	/** Gets all print output from priority queue
	 *@return string vector containing all book reservations
	 */
	vector<string> getPriorityQueuePrint() const;

	/** Gets all print output from priority queue
	 *@return string vector containing all book reservations from a specific reader
	 */
	vector<string> getPriorityQueuePrintByReader(Person* reader) const;

	/** Sorts given container and generates string used to display its contents
	 *@return string vector containing persons print output
	 */
	vector<string> sortPersons(vector<Person*> vec, size_t compareType);

	/** Sorts given container and generates string used to display its contents
	 *@return string vector containing books print output
	 */
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

	/** Adds new book to the library booksTree
	 *@param book Book pointer
	 */
	void addTreeBook(Book* book);

	/** Adds new Borrow to the library
	 *@param borrow Borrow pointer
	 */
	void addBorrow(Borrow* borrow);

	/** Adds new person to the library
	 *@param person Person pointer
	 */
	void addPerson(Person* person);

	/** Adds new reader to the hash table
	 *@param reader Person pointer
	 *@return true if successful false otherwise
	 */
	bool addReaderToHashTable(Person* reader);

	/** Adds new request to the library queue
	 *@param request
	 */
	bool addRequest(Request request);

	/** Attempts to remove existing book from the library
	 *@param book Book pointer to remove
	 *@return true if successful false otherwise
	 */
	bool removeBook(Book* book);

	/** Attempts to remove existing book from the library booksTree
	 *@param book Book pointer to remove
	 *@return true if successful false otherwise
	 */
	bool removeTreeBook(Book* book);

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

	/** Attempts to remove existing reader from the hash table
	 *@param reader Person pointer to remove
	 *@return true if successful false otherwise
	 */
	bool removeReaderFromHashTable(Person* reader);

	/** Attempts to remove existing requests of given book from the requests queue
	 *@param Book pointer to check in requests queue
	 *@return true if successful false otherwise
	 */
	bool removeRequestByBook(Book* book);

	/** Attempts to remove existing request from the requests queue
	 *@param Person pointer to check in requests queue
	 *@return true if successful false otherwise
	 */
	bool removeRequestByReader(Person* reader);

	/** Attempts to remove existing request from the requests queue
	 *@param request reference to remove
	 *@return true if successful false otherwise
	 */
	bool removeRequest(const Request &request);

	/** Attempts to borrow a return book to a reader from the requests queue
	 *@param borrow Borrow pointer to the returned book
	 *@return string to the queued reader if successfully borrowed
	 */
	string borrowQueuedRequest(Borrow* b);

	/** Updates inactive readers hash table by checking each reader last activity date
	 */
	void updateInactiveReaders();

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

	/** Loads stored requests
	 * Loads requests.csv file to the requests queue
	 */
	void loadRequests();

	/** Builds inactive readers hash table
	 * builds inactive readers to hash table
	 */
	void buildHashTable();

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
	 * Saves requests in requests.csv file
	 */
	void saveRequests();

	/**
	 * Assigns employees to supervisors
	 */
	void assignEmployees();
};

#endif /* LIBRARY_H_ */
