#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

inline bool is_Number(const int & c);
inline bool is_Not_Number(const int & c);
inline bool is_NON_ASCII_Letter(const int & c);
bool is_All_ASCII_Letter(const string& s);
bool is_All_Number(const string& s);
bool partialMatchQuery(const string & q, const string & n);
bool matchQuery(const string & q, const string & n);

template<class Comparable>
void insertionSort(vector<Comparable> &v);


#endif /* _ALGORITHMS_H_ */
