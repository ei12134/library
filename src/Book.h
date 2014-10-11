/*
 * Book.h
 *
 *  Created on: Oct 10, 2014
 *      Author: potter
 */

#ifndef BOOK_H_
#define BOOK_H_

#include <string>
using namespace std;

class Book {
private:
	string author;
	bool borrowed;
	string cota;
	int npaginas;
	string isbn;
	string title;
public:
	Book(string author, bool borrowed, string cota, int npaginas, string isbn,
			string title);
	virtual ~Book();
};

#endif /* BOOK_H_ */
