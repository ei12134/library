#include "Book.h"
using namespace std;

Book::Book(string author, bool borrowed, string quota, int pageNumber,
		string isbn, string title) :
		author(author), borrowed(borrowed), quota(quota), pageNumber(pageNumber), isbn(
				isbn), title(title) {
}

Book::~Book() {

}

