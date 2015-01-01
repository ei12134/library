#ifndef REQUEST_H_
#define REQUEST_H_

#include "./Persons/Person.h"
#include "Book.h"
#include "Date.h"

/**
 * Request class
 * stores data concerning the request of a book unavailable at the library
 */
class Request {
private:
	Book* book; /// Book pointer to the book requested
	Person* reader; /// Person pointer to the reader who made the request
	Date request;

public:
	/**
	 *  Invalid request constructor
	 */
	Request();

	/**
	 *  Request constructor with a specific book, reader and date
	 */
	Request(Book* book, Person* reader, Date date);

	///@return Person pointer of the reader who made the request
	Person* getReader() const;

	///@return Book pointer of the book requested
	Book* getBook() const;

	///@return Date of the request
	Date getDate() const;

	/** Sets the date of the request
	 * @param Date of the request
	 */
	void setDate(Date d);

	/** Attempts to change the reader who made the request
	 * @param Person pointer of the new reader who made the request
	 * @return true if successful false otherwise
	 */
	bool changeReader(Person* reader);

	/** Attempts to change the book requested
	 * @param Book pointer of the new book requested
	 * @return true if successful false otherwise
	 */
	bool changeBook(Book* book);

	/** Compares equality between two requests
	 * @param Request reference of the other request to compare
	 * @return true if reader and the book requested are equal false otherwise
	 */
	bool operator==(const Request& r2) const;

	/** Compares size between two requests
	 * @param Request reference of the other request to compare
	 * @return true if less false otherwise
	 */
	bool operator<(const Request& r2) const;

	/** Formats information of the request
	 * @return string containing formatted output
	 */
	string print() const;

	/** saves reader data to output file stream buffer
	 */
	void saveData(ofstream &of);
};

#endif /* REQUEST_H_ */
