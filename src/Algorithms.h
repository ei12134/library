#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include <algorithm>
#include <string>
using namespace std;

bool is_Number(const int & c);
bool is_Not_Number(const int & c);
bool is_NON_ASCII_Letter(const int & c);
bool is_All_ASCII_Letter(const string& s);
bool is_All_Number(const string& s);
bool matchQuery(const string & q, const string & n);

#endif /* _ALGORITHMS_H_ */
