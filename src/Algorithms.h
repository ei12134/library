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
bool partialMatchQueryPermissive(const string & q, const string & n);
bool matchQuery(const string & q, const string & n);

template<class Comparable>
void insertionSort(vector<Comparable> &v) {
	for (unsigned int p = 1; p < v.size(); p++) {
		Comparable tmp = v[p];
		int j;
		for (j = p; j > 0 && tmp < v[j - 1]; j--)
			v[j] = v[j - 1];
		v[j] = tmp;
	}
}

template<class T>
int sequentialSearch(const vector<T> &v, T x) {
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i] == x)
			return i;
	return -1;
}

#endif /* _ALGORITHMS_H_ */
