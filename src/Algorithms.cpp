#include "Algorithms.h"

inline bool is_Number(const int & c) {
	return (c >= 48 && c <= 57);
}

inline bool is_Not_Number(const int & c) {
	return !(c >= 48 && c <= 57);
}

inline bool is_NON_ASCII_Letter(const int & c) {
	return (((c < 65) && c != 32) || (c > 122) || (c > 90 && c < 97));
}

bool is_All_ASCII_Letter(const string& s) {
	return find_if(s.begin(), s.end(), is_NON_ASCII_Letter) == s.end();
}

bool is_All_Number(const string& s) {
	return find_if(s.begin(), s.end(), is_Not_Number) == s.end();
}

bool partialMatchQuery(const string & q, const string & n) {
	if (q.size() == 0 || q.size() > n.size())
		return false;
	bool partialMatch = false;
	for (size_t i = 0; i < n.size(); i++) {
		if (tolower(q[0]) == tolower(n[i])) {
			partialMatch = true;
			for (size_t z = 1, y = i + 1; z < q.size(); z++, y++) {
				if (tolower(q[z]) != tolower(n[y])) {
					partialMatch = false;
					break;
				}
			}
			if (partialMatch)
				return true;
		}
	}
	return false;
}

bool matchQuery(const string & q, const string & n) {
	if (q.size() == 0 || q.size() > n.size())
		return false;
	for (size_t i = 0; i < q.size() && i < n.size(); i++) {
		if (tolower(q[i]) != tolower(n[i]))
			return false;
	}
	return true;
}
