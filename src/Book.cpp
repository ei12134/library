/*
 * Book.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: potter
 */

#include "Book.h"

Book::Book(std::string author, bool borrowed, std::string cota, int npaginas,
		std::string isbn, std::string title) :
		author(author), borrowed { borrowed }, cota(cota), npaginas { npaginas }, isbn(
				isbn), title(title) {
}

Book::~Book() {

}

